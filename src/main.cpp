#include <cstdint>
#include <fstream>
#include <iostream>
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

		// Enumerate every type in the image
		for (unsigned i = game_image->typeStart; i < game_image->typeStart + game_image->typeCount; i++)
		{
			auto type = &metadata.typeDefinitions[i];

			// Filter out non-protobuf namespaces
			if (STRING(metadata, type->namespaceIndex) != "Holoholo.Rpc") continue;

			// If our type is an enum
			if (type->enum_type)
			{
				cout << "enum " << STRING(metadata, type->nameIndex) << " {" << endl;
				// Skip the first field which will always be "__value"
				for (auto j = type->fieldStart + 1; j < type->fieldStart + type->field_count; j++)
				{
					auto field = metadata.fields[j];
					auto fieldName = STRING(metadata, field.nameIndex);
					//TODO get actual default value of field
					auto fieldDefaultValue = j - type->fieldStart - 1;

					cout << "\t" << fieldName << " = " << fieldDefaultValue << ";" << endl;
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
							cerr << "Field default value is not a byte (typeIndex=" << field_default_value->typeIndex << ")" << endl;
							return EXIT_FAILURE;
						}

						proto_field_number = metadata.fieldAndParameterDefaultValueData[field_default_value->dataIndex];
						break;
					}

					// Get the proto field type from the return type of the generated getter
					for (unsigned k = type->methodStart; k < type->methodStart + type->method_count; k++)
					{
						auto method = metadata.methods[k];
						if (STRING(metadata, method.nameIndex) != "get_" + proto_field_name) continue;

						//TODO get method return type name
						proto_type_name = to_string(method.returnType);
					}

					cout << "\t" << proto_field_name << " = " << proto_field_number << ";" << endl;
				}
				cout << "}" << endl << endl;
				continue;
			}
		}
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
		return EXIT_FAILURE;
	}
}
