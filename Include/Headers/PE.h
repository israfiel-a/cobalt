/**
 * @file PE.h
 * @authors Israfil Argos (israfiel-a)
 * @brief This file contains the PE file header structure, which contains
 * data imperative to jumping into the executable portion of the PE
 * executable file.
 * @since 0.1.0.1
 * @updated 0.1.0.1
 *
 * @copyright (c) 2025 Israfil Argos
 * This file is under the AGPLv3. For information on what that entails, see
 * the attached LICENSE.md file or
 * https://www.gnu.org/licenses/agpl-3.0.en.html.
 */
#ifndef COBALT_HEADERS_PE_H
#define COBALT_HEADERS_PE_H

#include <Types.h>

/**
 * @brief A bitmask enumerator that describes the various machine types
 * that PE files can have been built for. This can help a more defined
 * environment optimize register and memory usage, but unfortunately we are
 * not a defined environment.
 * @since 0.1.0.1
 */
typedef enum : cobalt_u16_t
{
    /**
     * @brief The content of this field is assumed to be applicable to any
     * machine type.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_UNKNOWN = 0x0,
    /**
     * @brief Alpha AXP, 32-bit address space.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_ALPHA = 0x184,
    /**
     * @brief Alpha 64, 64-bit address space.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_ALPHA64 = 0x284,
    /**
     * @brief Matsushita AM33.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_AM33 = 0x1D3,
    /**
     * @brief x64.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_AMD64 = 0x8664,
    /**
     * @brief ARM little endian.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_ARM = 0x1C0,
    /**
     * @brief ARM64 little endian.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_ARM64 = 0xAA64,
    /**
     * @brief ARM Thumb-2 little endian.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_ARMNT = 0x1C4,
    /**
     * @brief AXP 64 (Same as Alpha 64).
     * @since 0.1.0.1
     */
    COBALT_MACHINE_AXP64 = 0x284,
    /**
     * @brief EFI byte code.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_EBC = 0xEBC,
    /**
     * @brief Intel 386 or later processors and compatible processors.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_I386 = 0x14C,
    /**
     * @brief Intel Itanium processor family.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_IA64 = 0x200,
    /**
     * @brief LoongArch 32-bit processor family.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_LOONGARCH32 = 0x6232,
    /**
     * @brief LoongArch 64-bit processor family.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_LOONGARCH64 = 0x6264,
    /**
     * @brief Mitsubishi M32R little endian.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_M32R = 0x9041,
    /**
     * @brief MIPS16.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_MIPS16 = 0x266,
    /**
     * @brief MIPS with FPU.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_MIPSFPU = 0x366,
    /**
     * @brief MIPS16 with FPU.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_MIPSFPU16 = 0x466,
    /**
     * @brief PowerPC little endian.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_POWERPC = 0x1F0,
    /**
     * @brief Power PC with floating point support.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_POWERPCFP = 0x1F1,
    /**
     * @brief MIPS little endian.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_R4000 = 0x166,
    /**
     * @brief RISC-V 32-bit address space.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_RISCV32 = 0x5032,
    /**
     * @brief RISC-V 64-bit address space.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_RISCV64 = 0x5064,
    /**
     * @brief RISC-V 128-bit address space.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_RISCV128 = 0x5128,
    /**
     * @brief Hitachi SH3.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_SH3 = 0x1A2,
    /**
     * @brief Hitachi SH3 DSP.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_SH3DSP = 0x1A3,
    /**
     * @brief Hitachi SH4.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_SH4 = 0x1A6,
    /**
     * @brief Hitachi SH5.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_SH5 = 0x1A8,
    /**
     * @brief ARM Thumb/Thumb-2 Little-Endian.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_THUMB = 0x1C2,
    /**
     * @brief MIPS little-endian WCE v2.
     * @since 0.1.0.1
     */
    COBALT_MACHINE_WCEMIPSV2 = 0x169
} cobalt_coff_machine_t;

/**
 * @brief A bitmask enumerator that describes the various characteristics
 * that PE files can have.
 * @since 0.1.0.1
 */
typedef enum : cobalt_u16_t
{
    /**
     * @brief Image only. This indicates that the file does not contain
     * base relocations and must therefore be loaded at its preferred base
     * address.
     * @since 0.1.0.1
     */
    COBALT_RELOCS_STRIPPED = 0x0001,
    /**
     * @brief Image only. This indicates that the image file is valid and
     * can be run.
     * @since 0.1.0.1
     */
    COBALT_EXECUTABLE_IMAGE = 0x0002,
    /**
     * @brief COFF line numbers have been removed.
     * @since 0.1.0.1
     * @deprecated
     */
    COBALT_LINE_NUMS_STRIPPED = 0x0004,
    /**
     * @brief COFF symbol table entries for local symbols have been
     * removed.
     * @since 0.1.0.1
     * @deprecated
     */
    COBALT_LOCAL_SYMS_STRIPPED = 0x0008,
    /**
     * @brief Aggressively trim working set.
     * @since 0.1.0.1
     * @deprecated
     */
    COBALT_AGGRESSIVE_WS_TRIM = 0x0010,
    /**
     * @brief Application can handle > 2GB addresses.
     * @since 0.1.0.1
     */
    COBALT_LARGE_ADDRESS_AWARE = 0x0020,
    /**
     * @brief Little endian: the least significant bit (LSB) precedes the
     * most significant bit (MSB) in memory.
     * @since 0.1.0.1
     * @deprecated
     */
    COBALT_BYTES_REVERSED_LO = 0x0080,
    /**
     * @brief Machine is based on a 32-bit-word architecture.
     * @since 0.1.0.1
     */
    COBALT_32BIT_MACHINE = 0x0100,
    /**
     * @brief Debugging information is removed from the image file.
     * @since 0.1.0.1
     */
    COBALT_DEBUG_STRIPPED = 0x0200,
    /**
     * @brief If the image is on removable media, fully load it and copy it
     * to the swap file.
     * @since 0.1.0.1
     */
    COBALT_REMOVABLE_RUN_FROM_SWAP = 0x0400,
    /**
     * @brief If the image is on network media, fully load it and copy it
     * to the swap file.
     * @since 0.1.0.1
     */
    COBALT_NET_RUN_FROM_SWAP = 0x0800,
    /**
     * @brief The image file is a system file, not a user program.
     * @since 0.1.0.1
     */
    COBALT_SYSTEM = 0x1000,
    /**
     * @brief The image file is a dynamic-link library (DLL). Such files
     * are considered executable files for almost all purposes, although
     * they cannot be directly run.
     * @since 0.1.0.1
     */
    COBALT_DLL = 0x2000,
    /**
     * @brief The file should be run only on a uniprocessor machine.
     * @since 0.1.0.1
     */
    COBALT_UP_SYSTEM_ONLY = 0x4000,
    /**
     * @brief Big endian: the MSB precedes the LSB in memory.
     * @since 0.1.0.1
     * @deprecated
     */
    COBALT_BYTES_REVERSED_HI = 0x8000
} cobalt_coff_characteristics_t;

/**
 * @brief The PE (portable executable) file header. This is the de jure
 * standard executable format in UEFI environments. It contains a lot of
 * information useless to the OS, but also mission-critical pieces.
 * @since 0.1.0.1
 */
typedef struct
{
    /**
     * @brief The COFF (common object file format) header. This contains
     * data about the object file itself.
     * @since 0.1.0.1
     */
    struct
    {
        /**
         * @brief The magic number identifier of the header. This is always
         * 0x50450000 in a standard-compliant PE file header.
         * @since 0.1.0.1
         */
        cobalt_u32_t magicNumber;
        /**
         * @brief A value describing the machine the executable was created
         * for. Pretty much useless in our case, but useful for memory and
         * register optimizations in a more defined environment.
         * @since 0.1.0.1
         */
        cobalt_coff_machine_t machine;
        /**
         * @brief The number of file sections. This is the best way to
         * identify the size of the section table, which comes directly
         * after this and the optional header.
         * @since 0.1.0.1
         */
        cobalt_u16_t sectionCount;
        /**
         * @brief The low 32 bits of the timestamp (time_t format) of
         * executable file creation.
         * @since 0.1.0.1
         */
        cobalt_u32_t timeStamp;
        /**
         * @brief The pointer to the file's symbol table.
         * @since 0.1.0.1
         * @deprecated COFF debugging information as a whole is deprecated,
         * and this is a part of that. This should be zero (NULL) because
         * of that.
         */
        cobalt_u32_t symbolTablePointer;
        /**
         * @brief The entry count within the symbol table.
         * @since 0.1.0.1
         * @deprecated COFF debugging information as a whole is deprecated,
         * and this is a part of that. This should be zero because of that.
         */
        cobalt_u32_t symbolCount;
        /**
         * @brief The size of the "optional" header, which IS required for
         * executables, but not object files. We will exclusively be
         * dealing with executables, so this header is always here.
         * @since 0.1.0.1
         */
        cobalt_u16_t optionalHeaderSize;
        /**
         * @brief A bitmask flag indicating attributes of the file.
         * @since 0.1.0.1
         */
        cobalt_coff_characteristics_t characteristics;
    } coffHeader;
    struct
    {
        // 0x10b for 32b, 0x20b for 64b
        cobalt_u16_t Magic; /* 0x20b */
        cobalt_u8_t MajorLinkerVersion;
        cobalt_u8_t MinorLinkerVersion;
        cobalt_u32_t SizeOfCode;
        cobalt_u32_t SizeOfInitializedData;
        cobalt_u32_t SizeOfUninitializedData;
        cobalt_u32_t AddressOfEntryPoint;
        cobalt_u32_t BaseOfCode;
        cobalt_u64_t ImageBase;
        cobalt_u32_t SectionAlignment;
        cobalt_u32_t FileAlignment;
        cobalt_u16_t MajorOperatingSystemVersion;
        cobalt_u16_t MinorOperatingSystemVersion;
        cobalt_u16_t MajorImageVersion;
        cobalt_u16_t MinorImageVersion;
        cobalt_u16_t MajorSubsystemVersion;
        cobalt_u16_t MinorSubsystemVersion;
        cobalt_u32_t Win32VersionValue;
        cobalt_u32_t SizeOfImage;
        cobalt_u32_t SizeOfHeaders;
        cobalt_u32_t CheckSum;
        cobalt_u16_t Subsystem;
        cobalt_u16_t DllCharacteristics;
        cobalt_u64_t SizeOfStackReserve;
        cobalt_u64_t SizeOfStackCommit;
        cobalt_u64_t SizeOfHeapReserve;
        cobalt_u64_t SizeOfHeapCommit;
        cobalt_u32_t LoaderFlags;
        cobalt_u32_t NumberOfRvaAndSizes;
        struct
        {
            cobalt_u32_t VirtualAddress;
            cobalt_u32_t Size;
        } DataDirectory[16];
    } OptionalHeader;
} cobalt_pe_header_t;

#endif // COBALT_HEADERS_PE_H
