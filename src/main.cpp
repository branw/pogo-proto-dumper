#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include "il2cpp.hpp"

using namespace std;
using namespace il2cpp;

bool is_little_endian()
{
	auto number = 0x1;
	auto ptr = reinterpret_cast<char *>(&number);
	return ptr[0] == 1;
}

bool str_ends_with(string const& fullString, string const& ending)
{
	if (fullString.length() >= ending.length())
	{
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else
	{
		return false;
	}
}

int main(int argc, char* argv[])
{
	try
	{
		if (!is_little_endian())
		{
			throw exception("System must be little-endian");
		}

		if (argc != 2)
		{
			throw exception("Usage: umd path/to/global-metadata.dat");
		}

		ifstream global_metdata(argv[1], ios::binary);
		metadata metadata(global_metdata);

		// All of the game's data can be found in the "Assembly-CSharp.dll" image
		Il2CppImageDefinition* game_image = nullptr;
		for (unsigned i = 0; i < COUNT(metadata, images); i++)
		{
			if (STRING(metadata, metadata.images[i].nameIndex) == "Assembly-CSharp.dll")
			{
				game_image = &metadata.images[i];
				break;
			}
		}
		if (game_image == nullptr)
		{
			throw exception("Unable to find \"Assembly-CSharp.dll\" image");
		}

		// Keep track of all dumped types and the types used in fields
		set<TypeDefinitionIndex> dumped_types;
		set<TypeDefinitionIndex> referenced_types;

		// Create a mapping of TypeIndexes to TypeDefinitionIndexes in order to
		// get the type of Il2CppMethodDefinition::returnType
		map<TypeIndex, TypeDefinitionIndex> type_index_mapping;
		for (unsigned i = 0; i < COUNT(metadata, images); i++) {
			auto image = &metadata.images[i];
			for (unsigned j = image->typeStart; j < image->typeStart + image->typeCount; j++)
			{
				auto type = &metadata.typeDefinitions[j];
				type_index_mapping.insert_or_assign(type->byvalTypeIndex, j);
			}
		}

		// Enumerate every type in the image
		for (unsigned i = game_image->typeStart; i < game_image->typeStart + game_image->typeCount; i++)
		{
			auto type = &metadata.typeDefinitions[i];

			// Filter out non-protobuf namespaces
			if (STRING(metadata, type->namespaceIndex) != "Holoholo.Rpc") continue;

			// If our type is an enum
			if (type->enum_type)
			{
				dumped_types.insert(i);

				cout << "enum " << STRING(metadata, type->nameIndex) << " {" << endl;
				// Skip the first field which will always be "__value"
				for (auto j = type->fieldStart + 1; j < type->fieldStart + type->field_count; j++)
				{
					auto field = metadata.fields[j];
					auto field_name = STRING(metadata, field.nameIndex);
					auto field_default_value = 0;

					for (unsigned k = 0; k < COUNT(metadata, fieldDefaultValues); k++)
					{
						auto default_value = &metadata.fieldDefaultValues[k];
						if (default_value->fieldIndex != j) continue;

						if (STRING(metadata, metadata.typeDefinitions[default_value->typeIndex].nameIndex) != "Byte")
						{
							throw exception(("Field default value is not a byte (typeIndex=" + to_string(default_value->typeIndex) + ")").c_str());
						}

						field_default_value = metadata.fieldAndParameterDefaultValueData[default_value->dataIndex];
						break;
					}

					cout << "\t" << field_name << " = " << field_default_value << ";" << endl;
				}
				cout << "}" << endl << endl;
				continue;
			}

			// If our type is a protobuf message
			auto has_parser_field = false;
			for (unsigned j = type->fieldStart; j < type->fieldStart + type->field_count; j++)
			{
				if (STRING(metadata, metadata.fields[j].nameIndex) == "_parser")
				{
					has_parser_field = true;
					break;
				}
			}
			if (has_parser_field)
			{
				dumped_types.insert(i);

				cout << "message " << STRING(metadata, type->nameIndex) << " { " << endl;
				for (unsigned j = type->fieldStart; j < type->fieldStart + type->field_count; j++)
				{
					auto field = metadata.fields[j];
					auto field_name = STRING(metadata, field.nameIndex);
					if (!str_ends_with(field_name, "FieldNumber")) continue;

					string proto_type_name = "";
					auto proto_field_name = field_name.substr(0, field_name.length() - 11);
					auto proto_field_number = 0;

					// Get protobuf field number from the default value of the field
					for (unsigned k = 0; k < COUNT(metadata, fieldDefaultValues); k++)
					{
						auto field_default_value = &metadata.fieldDefaultValues[k];
						if (field_default_value->fieldIndex != j) continue;

						if (STRING(metadata, metadata.typeDefinitions[field_default_value->typeIndex].nameIndex) != "Byte")
						{
							throw exception(("Field default value is not a byte (typeIndex=" + to_string(field_default_value->typeIndex) + ")").c_str());
						}

						proto_field_number = metadata.fieldAndParameterDefaultValueData[field_default_value->dataIndex];
						break;
					}

					// Get the proto field type from the return type of the generated getter
					for (unsigned k = type->methodStart; k < type->methodStart + type->method_count; k++)
					{
						auto method = &metadata.methods[k];
						if (STRING(metadata, method->nameIndex) != "get_" + proto_field_name) continue;

						// Identify the return type from the mapping of byval type indexes
						if (type_index_mapping.find(method->returnType) != type_index_mapping.end())
						{
							auto definition_index = type_index_mapping.at(method->returnType);
							proto_type_name = STRING(metadata, metadata.typeDefinitions[definition_index].nameIndex);

							// Map C# types to Protobuf types for conversion
							const map<string, string> csharp_to_protobuf_types = {
								{ "UInt64", "fixed64" },
								{ "UInt32", "fixed32" },
								{ "Double", "double" },
								{ "String", "string" },
								{ "Int32", "int32" },
								{ "Int64", "int64" },
								{ "Single", "float" },
								{ "Boolean", "bool" }
							};
							if (csharp_to_protobuf_types.find(proto_type_name) != csharp_to_protobuf_types.end())
							{
								proto_type_name = csharp_to_protobuf_types.at(proto_type_name);
							}

							referenced_types.insert(definition_index);
						}
						// If it's not there, it's a generic type, e.g. a RepeatedField<T> or List<T>
						else
						{	
							//TODO resolve generic types
							proto_type_name = "Generic" + to_string(method->returnType);
						}
					}

					cout << "\t" << proto_type_name << " " << proto_field_name << " = " << proto_field_number << ";" << endl;
				}
				cout << "}" << endl << endl;
				continue;
			}
		}

		//TODO make sure all referenced_types are in dumped_types
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
		return EXIT_FAILURE;
	}
}
