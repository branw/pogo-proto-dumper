#include <exception>
#include <fstream>

// Calculate number of entries for a given struct
#define COUNT(metadata, section) (metadata.header.section##Count / sizeof(decltype(*metadata.section)))

// Return the string at a given StringIndex, or the index if it is invalid
#define STRING(metadata, index) (index >= 0 && index < metadata.header.stringCount ? metadata.string + index : std::to_string(index))

namespace il2cpp
{
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

#pragma pack(push, 4)
	struct Il2CppGlobalMetadataHeader
	{
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
	};

	struct Il2CppEventDefinition
	{
		StringIndex nameIndex;
		TypeIndex typeIndex;
		MethodIndex add;
		MethodIndex remove;
		MethodIndex raise;
		CustomAttributeIndex customAttributeIndex;
		uint32_t token;
	};

	struct Il2CppPropertyDefinition
	{
		StringIndex nameIndex;
		MethodIndex get;
		MethodIndex set;
		uint32_t attrs;
		CustomAttributeIndex customAttributeIndex;
		uint32_t token;
	};

	struct Il2CppMethodDefinition
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
	};

	struct Il2CppParameterDefaultValue
	{
		ParameterIndex parameterIndex;
		TypeIndex typeIndex;
		DefaultValueDataIndex dataIndex;
	};

	struct Il2CppFieldDefaultValue
	{
		FieldIndex fieldIndex;
		TypeIndex typeIndex;
		DefaultValueDataIndex dataIndex;
	};

	struct Il2CppFieldMarshaledSize
	{
		FieldIndex fieldIndex;
		TypeIndex typeIndex;
		int32_t size;
	};

	struct Il2CppParameterDefinition
	{
		StringIndex nameIndex;
		uint32_t token;
		CustomAttributeIndex customAttributeIndex;
		TypeIndex typeIndex;
	};

	struct Il2CppFieldDefinition
	{
		StringIndex nameIndex;
		TypeIndex typeIndex;
		CustomAttributeIndex customAttributeIndex;
		uint32_t token;
	};

	struct Il2CppGenericParameter
	{
		GenericContainerIndex ownerIndex;
		StringIndex nameIndex;
		GenericParameterConstraintIndex constraintsStart;
		int16_t constraintsCount;
		uint16_t num;
		uint16_t flags;
	};

	struct Il2CppGenericContainer
	{
		int32_t ownerIndex;
		int32_t type_argc;
		int32_t is_method;
		GenericParameterIndex genericParameterStart;
	};

	struct Il2CppInterfaceOffsetPair
	{
		TypeIndex interfaceTypeIndex;
		int32_t offset;
	};

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

		uint32_t value_type : 1;
		uint32_t enum_type : 1;
		uint32_t has_finalize : 1;
		uint32_t has_cctor : 1;
		uint32_t is_blittable : 1;
		uint32_t is_import : 1;
		uint32_t packing_size : 4;
		uint32_t _reserved : 22;
		uint32_t token;
	};

	struct Il2CppRGCTXDefinition
	{
		Il2CppRGCTXDataType type;
		int32_t rgctxDataDummy;
		MethodIndex methodIndex;
		TypeIndex typeIndex;
	};

	struct Il2CppImageDefinition
	{
		StringIndex nameIndex;
		AssemblyIndex assemblyIndex;
		TypeDefinitionIndex typeStart;
		uint32_t typeCount;
		MethodIndex entryPointIndex;
		uint32_t token;
	};

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
		uint8_t publicKeytoken[kPublicKeyByteLength];
	};

	struct Il2CppAssemblyDefinition
	{
		ImageIndex imageIndex;
		CustomAttributeIndex customAttributeIndex;
		int32_t referencedAssemblyStart;
		int32_t referencedAssemblyCount;
		Il2CppAssemblyName aname;
	};

	struct Il2CppMetadataUsageList
	{
		uint32_t start;
		uint32_t count;
	};

	struct Il2CppMetadataUsagePair
	{
		uint32_t destinationIndex;
		uint32_t encodedSourceIndex;
	};

	struct Il2CppFieldRef
	{
		TypeIndex typeIndex;
		FieldIndex fieldIndex;
	};

	struct Il2CppCustomAttributeTypeRange
	{
		int32_t start;
		int32_t count;
	};
#pragma pack(pop)

	class metadata
	{
	public:
		Il2CppGlobalMetadataHeader header;
		char* stringLiteral;
		char* stringLiteralData;
		char* string;
		Il2CppEventDefinition* events;
		Il2CppPropertyDefinition* properties;
		Il2CppMethodDefinition* methods;
		Il2CppParameterDefaultValue* parameterDefaultValues;
		Il2CppFieldDefaultValue* fieldDefaultValues;
		uint8_t* fieldAndParameterDefaultValueData;
		Il2CppFieldMarshaledSize* fieldMarshaledSizes;
		Il2CppParameterDefinition* parameters;
		Il2CppFieldDefinition* fields;
		Il2CppGenericParameter* genericParameters;
		TypeIndex* genericParameterConstraints;
		Il2CppGenericContainer* genericContainers;
		TypeDefinitionIndex* nestedTypes;
		TypeIndex* interfaces;
		EncodedMethodIndex* vtableMethods;
		Il2CppInterfaceOffsetPair* interfaceOffsets;
		Il2CppTypeDefinition* typeDefinitions;
		Il2CppRGCTXDefinition* rgctxEntries;
		Il2CppImageDefinition* images;
		Il2CppAssemblyDefinition* assemblies;
		Il2CppMetadataUsageList* metadataUsageLists;
		Il2CppMetadataUsagePair* metadataUsagePairs;
		Il2CppFieldRef* fieldRefs;
		int32_t* referencedAssemblies;
		Il2CppCustomAttributeTypeRange* attributesInfo;
		TypeIndex* attributeTypes;

		metadata(std::ifstream& global_metdata)
		{
			global_metdata.read(reinterpret_cast<char *>(&header), sizeof(Il2CppGlobalMetadataHeader));

			if (header.sanity != 0xfab11baf)
			{
				throw std::exception("File does not have valid header");
			}

			if (header.version != 21)
			{
				throw std::exception("Metadata is described by unsupported version");
			}

			// Read the file binary into corresponding arrays of structs
#define LOAD_DATA(type_name, container_name) \
	do { \
		container_name = new type_name[header.container_name##Count / sizeof(type_name)]; \
		global_metdata.seekg(header.container_name##Offset, std::ios::beg); \
        global_metdata.read(reinterpret_cast<char *>(container_name), header.container_name##Count); \
	} while (0)

			LOAD_DATA(char, stringLiteral);
			LOAD_DATA(char, stringLiteralData);
			LOAD_DATA(char, string);
			LOAD_DATA(Il2CppEventDefinition, events);
			LOAD_DATA(Il2CppPropertyDefinition, properties);
			LOAD_DATA(Il2CppMethodDefinition, methods);
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
		}
	};
}
