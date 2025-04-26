#ifndef COBALT_EFI_TYPES_H
#define COBALT_EFI_TYPES_H

#include <efi.h>
#include <stdint.h>

typedef unsigned short COBALT_WIDECHAR;
typedef COBALT_WIDECHAR *COBALT_WIDESTR;

typedef struct
{
    uint64_t descriptorSize;
    uint64_t size;
    EFI_MEMORY_DESCRIPTOR *map;
} cobalt_memory_map_t;

typedef struct
{
    uint64_t count;
    EFI_CONFIGURATION_TABLE *tables;
} cobalt_efi_tables_t;

typedef struct
{
    cobalt_memory_map_t memoryMap;
    cobalt_efi_tables_t configurationTables;
    EFI_RUNTIME_SERVICES *runtimeServices;
    uint64_t kernelBase;
    uint64_t kernelPageCount;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE graphicsMode;
} cobalt_efi_info_t;

typedef struct
{
    UINT8 Name[8];
    union
    {
        UINT32 PhysicalAddress;
        UINT32 VirtualSize;
    } Misc;
    UINT32 VirtualAddress;
    UINT32 SizeOfRawData;
    UINT32 PointerToRawData;
    UINT32 PointerToRelocations;
    UINT32 PointerToLinenumbers;
    UINT16 NumberOfRelocations;
    UINT16 NumberOfLinenumbers;
    UINT32 Characteristics;
} cobalt_image_section_header_t;

typedef struct
{
    UINT32 VirtualAddress;
    UINT32 SizeOfBlock;
} cobalt_image_base_relocation_t;

#define NL L"\n\r"

extern cobalt_efi_info_t cobalt_efiInfo;

#endif // COBALT_EFI_TYPES_H
