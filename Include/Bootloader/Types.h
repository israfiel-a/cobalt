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
{                   // DOS .EXE header
    UINT16 e_magic; // Magic number
    UINT16 e_cblp;  // Bytes on last page of file
    UINT16 e_cp;    // Pages in file
    UINT16 e_crlc;  // Relocations
    UINT16
    e_cparhdr; // Size of header in paragraphs (1 paragraph = 16 bytes)
    UINT16 e_minalloc; // Minimum extra paragraphs needed
    UINT16 e_maxalloc; // Maximum extra paragraphs needed
    UINT16 e_ss;       // Initial (relative) SS value
    UINT16 e_sp;       // Initial SP value
    UINT16 e_csum;     // Checksum
    UINT16 e_ip;       // Initial IP value
    UINT16 e_cs;       // Initial (relative) CS value
    UINT16 e_lfarlc;   // File address of relocation table
    UINT16 e_ovno;     // Overlay number
    UINT16 e_res[4];   // Reserved words
    UINT16 e_oemid;    // OEM identifier (for e_oeminfo)
    UINT16 e_oeminfo;  // OEM information; e_oemid specific
    UINT16 e_res2[10]; // Reserved words
    UINT32 e_lfanew;   // File address of new exe header
} cobalt_dos_header_t;

typedef struct
{
    UINT32 Signature;
    struct
    {
        UINT16 Machine;
        UINT16 NumberOfSections;
        UINT32 TimeDateStamp;
        UINT32 PointerToSymbolTable;
        UINT32 NumberOfSymbols;
        UINT16 SizeOfOptionalHeader;
        UINT16 Characteristics;
    } FileHeader;
    struct
    {
        UINT16 Magic; /* 0x20b */
        UINT8 MajorLinkerVersion;
        UINT8 MinorLinkerVersion;
        UINT32 SizeOfCode;
        UINT32 SizeOfInitializedData;
        UINT32 SizeOfUninitializedData;
        UINT32 AddressOfEntryPoint;
        UINT32 BaseOfCode;
        UINT64 ImageBase;
        UINT32 SectionAlignment;
        UINT32 FileAlignment;
        UINT16 MajorOperatingSystemVersion;
        UINT16 MinorOperatingSystemVersion;
        UINT16 MajorImageVersion;
        UINT16 MinorImageVersion;
        UINT16 MajorSubsystemVersion;
        UINT16 MinorSubsystemVersion;
        UINT32 Win32VersionValue;
        UINT32 SizeOfImage;
        UINT32 SizeOfHeaders;
        UINT32 CheckSum;
        UINT16 Subsystem;
        UINT16 DllCharacteristics;
        UINT64 SizeOfStackReserve;
        UINT64 SizeOfStackCommit;
        UINT64 SizeOfHeapReserve;
        UINT64 SizeOfHeapCommit;
        UINT32 LoaderFlags;
        UINT32 NumberOfRvaAndSizes;
        struct
        {
            UINT32 VirtualAddress;
            UINT32 Size;
        } DataDirectory[16];
    } OptionalHeader;
} cobalt_pe_header_t;

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
