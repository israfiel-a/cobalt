/**
 * @file PE.h
 * @authors Israfil Argos (israfiel-a)
 * @brief This file contains the PE file header structure, which contains
 * data imperative to jumping into the executable portion of the PE
 * executable file.
 * @since 0.1.0.1
 * @updated 0.1.0.2
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
 * @brief A bitmask enumerator that describes the various subsystems a PE
 * file can be built to run within.
 * @since 0.1.0.2
 */
typedef enum : cobalt_u16_t
{
    /**
     * @brief An unknown subsystem. This is typically just bare metal.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_UNKNOWN = 0,
    /**
     * @brief Native Windows userspace subsystem.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_NATIVE = 1,
    /**
     * @brief The Windows graphical user interface (GUI) subsystem.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_WINDOWS_GUI = 2,
    /**
     * @brief The Windows character subsystem.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_WINDOWS_CUI = 3,
    /**
     * @brief The OS/2 character subsystem.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_OS2_CUI = 5,
    /**
     * @brief The Posix character subsystem.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_POSIX_CUI = 7,
    /**
     * @brief A native Win9x driver.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_NATIVE_WINDOWS = 8,
    /**
     * @brief Windows CE.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_WINDOWS_CE_GUI = 9,
    /**
     * @brief An Extensible Firmware Interface (EFI) application. This is
     * only subsystem the Cobalt boot system will accept as a kernel
     * executable.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_EFI_APPLICATION = 10,
    /**
     * @brief An EFI driver with boot services.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER = 11,
    /**
     * @brief An EFI driver with runtime services.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_EFI_RUNTIME_DRIVER = 11,
    /**
     * @brief An EFI ROM image.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_EFI_ROM = 12,
    /**
     * @brief XBOX.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_XBOX = 14,
    /**
     * @brief A Windows boot application.
     * @since 0.1.0.2
     */
    COBALT_SUBSYSTEM_WINDOWS_BOOT_APPLICATION = 16
} cobalt_subsystem_t;

/**
 * @brief The PE (portable executable) file header. This is the de jure
 * standard executable format in UEFI environments. It contains a lot of
 * information useless to the OS, but also mission-critical pieces.
 * @since 0.1.0.1
 */
typedef struct
{
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
    }
    /**
     * @brief The COFF (common object file format) header. This contains
     * data about the object file itself.
     * @since 0.1.0.1
     */
    coffHeader;

    struct
    {
        /**
         * @brief The magic number specifying that this is, indeed, a PE
         * optional header. On 64-bit machines, this is always 0x20, but on
         * 32-bit machines it's 0x10.
         * @since 0.1.0.1
         */
        cobalt_u16_t magicNumber;

        /**
         * @brief The version of the linker in (major | minor format) that
         * linked this executable.
         * @since 0.1.0.1
         */
        cobalt_u16_t linkerVersion;

        /**
         * @brief A sum total of the size of all code/text sections.
         * @since 0.1.0.1
         */
        cobalt_u32_t codeSize;

        /**
         * @brief The sum total of the size of all initialized data
         * sections.
         * @since 0.1.0.1
         */
        cobalt_u32_t initializedDataSize;

        /**
         * @brief The sum total of the size of all uninitialized/BSS data
         * sections.
         * @since 0.1.0.1
         */
        cobalt_u32_t uninitializedDataSize;

        /**
         * @brief The address of the entrypoint relative to the image
         * base.
         * @since 0.1.0.1
         */
        cobalt_u32_t entrypointAddress;

        /**
         * @brief The address relative to the image base that will point to
         * the code section when loaded into memory.
         * @since 0.1.0.1
         */
        cobalt_u32_t codeBase;

        /**
         * @brief The preferred address for the image base when loaded into
         * memory. This must be a multiple of 64K. By default, this will be
         * 0x00400000. This is an EFI/Windows-specific field.
         * @since 0.1.0.1
         */
        cobalt_u64_t imageBase;

        /**
         * @brief The byte alignment sections must be on when loaded into
         * memory. This must be greater than or equal to the file
         * alignment. By default, this is the page size, or 4KB. This is an
         * EFI/Windows-specific field.
         * @since 0.1.0.1
         */
        cobalt_u32_t sectionAlignment;

        /**
         * @brief The byte alignment to align raw sections of the file.
         * This must be a power of 2 between 512 and 64K inclusive. By
         * default, this is 512. This is an EFI/Windows-specific field.
         * @since 0.1.0.1
         */
        cobalt_u32_t fileAlignment;

        /**
         * @brief The version (major | minor format) of the target
         * operating system this file requires. We do not give a single
         * damn about this--we're not running on an operating system this
         * system will recognize. This is an EFI/Windows-specific field.
         * @since 0.1.0.1
         */
        cobalt_u16_t operatingSystemVersion;

        /**
         * @brief The version (major | minor format) of the image. This is
         * an EFI/Windows-specific field.
         * @since 0.1.0.1
         */
        cobalt_u16_t imageVersion;

        /**
         * @brief The version (major | minor format) of the subsystem this
         * image requires. We do not care--we're running on hardware. This
         * is an EFI/Windows-specific field.
         * @since 0.1.0.1
         */
        cobalt_u16_t subsystemVersion;

        PAD(8); // Reserved. Technically must be zero--we don't care.

        /**
         * @brief The size of the image in bytes--including headers. This
         * must be a multiple of sectionAligment. This is an
         * EFI/Windows-specific field.
         * @since 0.1.0.1
         */
        cobalt_u32_t imageSize;

        /**
         * @brief The size in bytes of the DOS header, PE header, and
         * section headers rounded up to a multiple of the file alignment.
         * This is an EFI/Windows-specific field.
         * @since 0.1.0.1
         */
        cobalt_u32_t headerSize;

        /**
         * @brief The image file checksum. This is an EFI/Windows-specific
         * field.
         * @since 0.1.0.1
         */
        cobalt_u32_t checksum;

        /**
         * @brief The subsystem required to run this image. The only
         * accepted subsystem for kernel executable in the bootloader is
         * 10 (SUBSYSTEM_EFI_APPLICATION).
         * @since 0.1.0.1
         */
        cobalt_subsystem_t subsystem;

        /**
         * @brief The characteristics specific to DLLs that this image has.
         * Fortunately, we will never ever have DLLs, so I don't have to
         * waste time documenting the enum that describes this.
         * @since 0.1.0.1
         */
        cobalt_u16_t dllCharacteristics;

        struct
        {
            /**
             * @brief The size in bytes to reserve for the stack.
             * @since 0.1.0.2
             */
            cobalt_u64_t reserve;
            /**
             * @brief The size in bytes of PHYSICAL memory to allocate to
             * the image's stack.
             * @since 0.1.0.2
             */
            cobalt_u64_t commit;
        }
        /**
         * @brief Information about the stack requested for the image to be
         * run.
         * @since 0.1.0.2
         */
        stackInfo;

        struct
        {
            /**
             * @brief The size in bytes to reserve for the heap.
             * @since 0.1.0.2
             */
            cobalt_u64_t reserve;
            /**
             * @brief The size in bytes of PHYSICAL memory to allocate to
             * the image's heap.
             * @since 0.1.0.2
             */
            cobalt_u64_t commit;
        }
        /**
         * @brief Information about the heap requested for the image to be
         * run.
         * @since 0.1.0.2
         */
        heapInfo;

        PAD(4); // Reserved, technically must be zero but we don't care.

        /**
         * @brief The count of data directory entries in the rest of the
         * optional header.
         * @since 0.1.0.1
         */
        cobalt_u32_t dataDirectoryLength;

        struct
        {
            /**
             * @brief The relative virtual address of the table.
             * @since 0.1.0.1
             */
            cobalt_u32_t virtualAddress;
            /**
             * @brief The size of the table in bytes.
             * @since 0.1.0.1
             */
            cobalt_u32_t size;
        }
        /**
         * @brief An array containing 16 address and size pairs for the
         * various information tables contained in the file (i.e.
         * export/import tables, resource table, base relocation table,
         * etc.). For information about the tables, see the PE Format
         * reference in CREDITS and go to the "data directory reference"
         * subsection.
         * @since 0.1.0.1
         */
        dataDirectory[16];
    }
    /**
     * @brief The "optional" COFF extension header that contains data
     * required to execute the file. This, despite its name, is required in
     * executable PE files.
     * @since 0.1.0.1
     */
    optionalHeader;
} cobalt_pe_header_t;

#endif // COBALT_HEADERS_PE_H
