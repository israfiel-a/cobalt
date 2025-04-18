#ifndef COBALT_EFI_TYPES
#define COBALT_EFI_TYPES

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
} cobalt_efi_info_t;

#define NL L"\n\r"

extern cobalt_efi_info_t cobalt_efiInfo;

#endif // COBALT_EFI_TYPES
