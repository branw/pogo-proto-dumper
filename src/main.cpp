#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

typedef int32_t TypeIndex;
typedef int32_t TypeDefinitionIndex;
typedef int32_t FieldIndex;
typedef int32_t DefaultValueIndex;
typedef int32_t DefaultValueDataIndex;
typedef int32_t CustomAttributeIndex;
typedef int32_t ParameterIndex;
typedef int32_t MethodIndex;
typedef int32_t GenericMethodIndex;
typedef int32_t PropertyIndex;
typedef int32_t EventIndex;
typedef int32_t GenericContainerIndex;
typedef int32_t GenericParameterIndex;
typedef int16_t GenericParameterConstraintIndex;
typedef int32_t NestedTypeIndex;
typedef int32_t InterfacesIndex;
typedef int32_t VTableIndex;
typedef int32_t InterfaceOffsetIndex;
typedef int32_t RGCTXIndex;
typedef int32_t StringIndex;
typedef int32_t StringLiteralIndex;
typedef int32_t GenericInstIndex;
typedef int32_t ImageIndex;
typedef int32_t AssemblyIndex;
typedef uint32_t EncodedMethodIndex;
typedef int32_t GuidIndex;

enum Il2CppRGCTXDataType
{
	IL2CPP_RGCTX_DATA_INVALID,
	IL2CPP_RGCTX_DATA_TYPE,
	IL2CPP_RGCTX_DATA_CLASS,
	IL2CPP_RGCTX_DATA_METHOD
};

const int kPublicKeyByteLength = 8;

#pragma pack(4)
struct global_metadata_header {
	int32_t sanity;
	int32_t version;
	int32_t stringLiteralOffset;
	int32_t stringLiteralCount;
	int32_t stringLiteralDataOffset;
	int32_t stringLiteralDataCount;
	int32_t stringOffset;
	int32_t stringCount;
	int32_t eventsOffset;
	int32_t eventsCount;
	int32_t propertiesOffset;
	int32_t propertiesCount;
	int32_t methodsOffset;
	int32_t methodsCount;
	int32_t parameterDefaultValuesOffset;
	int32_t parameterDefaultValuesCount;
	int32_t fieldDefaultValuesOffset;
	int32_t fieldDefaultValuesCount;
	int32_t fieldAndParameterDefaultValueDataOffset;
	int32_t fieldAndParameterDefaultValueDataCount;
	int32_t fieldMarshaledSizesOffset;
	int32_t fieldMarshaledSizesCount;
	int32_t parametersOffset;
	int32_t parametersCount;
	int32_t fieldsOffset;
	int32_t fieldsCount;
	int32_t genericParametersOffset;
	int32_t genericParametersCount;
	int32_t genericParameterConstraintsOffset;
	int32_t genericParameterConstraintsCount;
	int32_t genericContainersOffset;
	int32_t genericContainersCount;
	int32_t nestedTypesOffset;
	int32_t nestedTypesCount;
	int32_t interfacesOffset;
	int32_t interfacesCount;
	int32_t vtableMethodsOffset;
	int32_t vtableMethodsCount;
	int32_t interfaceOffsetsOffset;
	int32_t interfaceOffsetsCount;
	int32_t typeDefinitionsOffset;
	int32_t typeDefinitionsCount;
	int32_t rgctxEntriesOffset;
	int32_t rgctxEntriesCount;
	int32_t imagesOffset;
	int32_t imagesCount;
	int32_t assembliesOffset;
	int32_t assembliesCount;
	int32_t metadataUsageListsOffset;
	int32_t metadataUsageListsCount;
	int32_t metadataUsagePairsOffset;
	int32_t metadataUsagePairsCount;
	int32_t fieldRefsOffset;
	int32_t fieldRefsCount;
	int32_t referencedAssembliesOffset;
	int32_t referencedAssembliesCount;
	int32_t attributesInfoOffset;
	int32_t attributesInfoCount;
	int32_t attributeTypesOffset;
	int32_t attributeTypesCount;
} header;

char *string;

struct Il2CppEventDefinition
{
	StringIndex nameIndex;
	TypeIndex typeIndex;
	MethodIndex add;
	MethodIndex remove;
	MethodIndex raise;
	CustomAttributeIndex customAttributeIndex;
	uint32_t token;
} *events;

struct Il2CppPropertyDefinition
{
	StringIndex nameIndex;
	MethodIndex get;
	MethodIndex set;
	uint32_t attrs;
	CustomAttributeIndex customAttributeIndex;
	uint32_t token;
} *properties;

struct method_definition
{
	StringIndex nameIndex;
	TypeDefinitionIndex declaringType;
	TypeIndex returnType;
	ParameterIndex parameterStart;
	CustomAttributeIndex customAttributeIndex;
	GenericContainerIndex genericContainerIndex;
	MethodIndex methodIndex;
	MethodIndex invokerIndex;
	MethodIndex delegateWrapperIndex;
	RGCTXIndex rgctxStartIndex;
	int32_t rgctxCount;
	uint32_t token;
	uint16_t flags;
	uint16_t iflags;
	uint16_t slot;
	uint16_t parameterCount;
} *methods;

struct Il2CppParameterDefaultValue
{
	ParameterIndex parameterIndex;
	TypeIndex typeIndex;
	DefaultValueDataIndex dataIndex;
} *parameterDefaultValues;

struct Il2CppFieldDefaultValue
{
	FieldIndex fieldIndex;
	TypeIndex typeIndex;
	DefaultValueDataIndex dataIndex;
} *fieldDefaultValues;

uint8_t *fieldAndParameterDefaultValueData;

struct Il2CppFieldMarshaledSize
{
	FieldIndex fieldIndex;
	TypeIndex typeIndex;
	int32_t size;
} *fieldMarshaledSizes;

struct Il2CppParameterDefinition
{
	StringIndex nameIndex;
	uint32_t token;
	CustomAttributeIndex customAttributeIndex;
	TypeIndex typeIndex;
} *parameters;

struct Il2CppFieldDefinition
{
	StringIndex nameIndex;
	TypeIndex typeIndex;
	CustomAttributeIndex customAttributeIndex;
	uint32_t token;
} *fields;

struct Il2CppGenericParameter
{
	GenericContainerIndex ownerIndex;
	StringIndex nameIndex;
	GenericParameterConstraintIndex constraintsStart;
	int16_t constraintsCount;
	uint16_t num;
	uint16_t flags;
} *genericParameters;

TypeIndex *genericParameterConstraints;

struct Il2CppGenericContainer
{
	int32_t ownerIndex;
	int32_t type_argc;
	int32_t is_method;
	GenericParameterIndex genericParameterStart;
} *genericContainers;

TypeDefinitionIndex *nestedTypes;

TypeIndex *interfaces;

EncodedMethodIndex *vtableMethods;

struct Il2CppInterfaceOffsetPair
{
	TypeIndex interfaceTypeIndex;
	int32_t offset;
} *interfaceOffsets;

struct Il2CppTypeDefinition
{
	StringIndex nameIndex;
	StringIndex namespaceIndex;
	CustomAttributeIndex customAttributeIndex;
	TypeIndex byvalTypeIndex;
	TypeIndex byrefTypeIndex;

	TypeIndex declaringTypeIndex;
	TypeIndex parentIndex;
	TypeIndex elementTypeIndex;

	RGCTXIndex rgctxStartIndex;
	int32_t rgctxCount;

	GenericContainerIndex genericContainerIndex;

	MethodIndex delegateWrapperFromManagedToNativeIndex;
	int32_t marshalingFunctionsIndex;
	int32_t ccwFunctionIndex;
	GuidIndex guidIndex;

	uint32_t flags;

	FieldIndex fieldStart;
	MethodIndex methodStart;
	EventIndex eventStart;
	PropertyIndex propertyStart;
	NestedTypeIndex nestedTypesStart;
	InterfacesIndex interfacesStart;
	VTableIndex vtableStart;
	InterfacesIndex interfaceOffsetsStart;

	uint16_t method_count;
	uint16_t property_count;
	uint16_t field_count;
	uint16_t event_count;
	uint16_t nested_type_count;
	uint16_t vtable_count;
	uint16_t interfaces_count;
	uint16_t interface_offsets_count;

	uint32_t bitfield;
	uint32_t token;
} *typeDefinitions;

struct Il2CppRGCTXDefinition
{
	Il2CppRGCTXDataType type;
	int32_t rgctxDataDummy;
	MethodIndex methodIndex;
	TypeIndex typeIndex;
} *rgctxEntries;

struct Il2CppImageDefinition {
	StringIndex nameIndex;
	AssemblyIndex assemblyIndex;
	TypeDefinitionIndex typeStart;
	uint32_t typeCount;
	MethodIndex entryPointIndex;
	uint32_t token;
} *images;

struct Il2CppAssemblyName
{
	StringIndex nameIndex;
	StringIndex cultureIndex;
	StringIndex hashValueIndex;
	StringIndex publicKeyIndex;
	uint32_t hash_alg;
	int32_t hash_len;
	uint32_t flags;
	int32_t major;
	int32_t minor;
	int32_t build;
	int32_t revision;
	uint8_t publicKeyToken[kPublicKeyByteLength];
};

struct Il2CppAssemblyDefinition
{
	ImageIndex imageIndex;
	CustomAttributeIndex customAttributeIndex;
	int32_t referencedAssemblyStart;
	int32_t referencedAssemblyCount;
	Il2CppAssemblyName aname;
} *assemblies;

struct Il2CppMetadataUsageList
{
	uint32_t start;
	uint32_t count;
} *metadataUsageLists;

struct Il2CppMetadataUsagePair
{
	uint32_t destinationIndex;
	uint32_t encodedSourceIndex;
} *metadataUsagePairs;

struct Il2CppFieldRef
{
	TypeIndex typeIndex;
	FieldIndex fieldIndex; // local offset into type fields
} *fieldRefs;

int32_t *referencedAssemblies;

struct Il2CppCustomAttributeTypeRange
{
	int32_t start;
	int32_t count;
} *attributesInfo;

TypeIndex *attributeTypes;

// Calculate number of entries for a given struct
#define COUNT(container) (header.container##Count / sizeof(decltype(*container)))

// Return the string at a given StringIndex, or the index if it is invalid
#define STRING(index) (index >= 0 && index < header.stringCount ? string + index : std::to_string(index))

bool isLittleEndian()
{
	auto number = 0x1;
	auto ptr = reinterpret_cast<char *>(&number);
	return ptr[0] == 1;
}

int main(int argc, char *argv[]) {
	if (!isLittleEndian()) {
		std::cerr << "System must be little-endian" << std::endl;
		return 1;
	}

	if (argc != 2) {
		std::cerr << "Usage: umd path/to/global-metadata.dat" << std::endl;
		return 1;
	}

	std::ifstream f(argv[1], std::ios::binary);
	f.read(reinterpret_cast<char *>(&header), sizeof(global_metadata_header));

	if (header.sanity != 0xfab11baf) {
		std::cerr << "File does not have valid header" << std::endl;
		return 1;
	}

	if (header.version != 21) {
		std::cerr << "Metadata is described by unknown version" << std::endl;
		return 1;
	}

	// Read the file binary into corresponding arrays of structs
#define LOAD_DATA(type_name, container_name) \
	do { \
		container_name = new type_name[header.container_name##Count / sizeof(type_name)]; \
		f.seekg(header.container_name##Offset, std::ios::beg); \
        f.read(reinterpret_cast<char *>(container_name), header.container_name##Count); \
	} while (0)

	LOAD_DATA(char, string);
	LOAD_DATA(Il2CppEventDefinition, events);
	LOAD_DATA(Il2CppPropertyDefinition, properties);
	LOAD_DATA(method_definition, methods);
	LOAD_DATA(Il2CppParameterDefaultValue, parameterDefaultValues);
	LOAD_DATA(Il2CppFieldDefaultValue, fieldDefaultValues);
	LOAD_DATA(uint8_t, fieldAndParameterDefaultValueData);
	LOAD_DATA(Il2CppFieldMarshaledSize, fieldMarshaledSizes);
	LOAD_DATA(Il2CppParameterDefinition, parameters);
	LOAD_DATA(Il2CppFieldDefinition, fields);
	LOAD_DATA(Il2CppGenericParameter, genericParameters);
	LOAD_DATA(TypeIndex, genericParameterConstraints);
	LOAD_DATA(Il2CppGenericContainer, genericContainers);
	LOAD_DATA(TypeDefinitionIndex, nestedTypes);
	LOAD_DATA(TypeIndex, interfaces);
	LOAD_DATA(EncodedMethodIndex, vtableMethods);
	LOAD_DATA(Il2CppInterfaceOffsetPair, interfaceOffsets);
	LOAD_DATA(Il2CppTypeDefinition, typeDefinitions);
	LOAD_DATA(Il2CppRGCTXDefinition, rgctxEntries);
	LOAD_DATA(Il2CppImageDefinition, images);
	LOAD_DATA(Il2CppAssemblyDefinition, assemblies);
	LOAD_DATA(Il2CppMetadataUsageList, metadataUsageLists);
	LOAD_DATA(Il2CppMetadataUsagePair, metadataUsagePairs);
	LOAD_DATA(Il2CppFieldRef, fieldRefs);
	LOAD_DATA(int32_t, referencedAssemblies);
	LOAD_DATA(Il2CppCustomAttributeTypeRange, attributesInfo);
	LOAD_DATA(TypeIndex, attributeTypes);

#undef LOAD_DATA

	// Enumerate all assemblies
	std::cout << COUNT(assemblies) << " assemblies found for " << COUNT(images) << " images:" << std::endl;
	for (auto i = 0; i < COUNT(assemblies); i++) {
		auto assembly = assemblies[i];
		auto image = images[assembly.imageIndex];
		std::cout << i << ") " << STRING(assembly.aname.nameIndex) << " " << assembly.aname.major << "." << assembly.aname.minor << "." <<
			assembly.aname.build << "." << assembly.aname.revision << " (" << STRING(image.nameIndex) << ")" << std::endl;

		// List all referenced assemblies
		if (assembly.referencedAssemblyCount > 0) {
			std::cout << "\tReferences " << assembly.referencedAssemblyCount << " assemblies: ";
			for (auto j = assembly.referencedAssemblyStart; j < assembly.referencedAssemblyStart + assembly.referencedAssemblyCount; j++) {
				auto assemblyIndex = referencedAssemblies[j];
				std::cout << assemblyIndex << ") " << STRING(assemblies[assemblyIndex].aname.nameIndex) << ", ";
			}
			std::cout << std::endl;
		}

		// List all types
		std::cout << "\tContains " << image.typeCount << " types:" << std::endl;
		for (auto j = image.typeStart; j < image.typeStart + image.typeCount; j++) {
			auto type = typeDefinitions[j];
			auto ns = STRING(type.namespaceIndex);
			std::cout << "\t\t" << ns << (ns == "" ? "" : ".") << STRING(type.nameIndex) << std::endl;
		}
		std::cout << std::endl;
	}

	f.close();
	return 0;
}

