/**
 * @file DOS.h
 * @authors Israfil Argos (israfiel-a)
 * @brief This file contains the DOS file header description, which
 * includes mostly useless information, still documented for your viewing
 * pleasure.
 * @since 0.1.0.0
 * @updated 0.1.0.1
 *
 * @copyright (c) 2025 Israfil Argos
 * This file is under the AGPLv3. For information on what that entails, see
 * the attached LICENSE.md file or
 * https://www.gnu.org/licenses/agpl-3.0.en.html.
 */
#ifndef COBALT_HEADERS_DOS_H
#define COBALT_HEADERS_DOS_H

#include <Types.h>

/**
 * @brief The MS-DOS header structure. This contains a lot of interesting
 * information, but not a ton that interesting to us, in the context of a
 * PE executable parser. The NT header offset is truly what we're after.
 * @since 0.1.0.0
 */
typedef struct
{
    /**
     * @brief The magic number beginning the file. This should always be
     * the characters 'M' and 'Z', for Mark Zbikowski, flipped for
     * endianness.
     * @since 0.1.0.0
     */
    cobalt_u16_t magicNumber;

    /**
     * @brief The number of bytes filled on the last page of the file. If
     * the count is 0, the page is full.
     * @since 0.1.0.0
     */
    cobalt_u16_t lastPageLength;

    /**
     * @brief This is the count of pages in the executable file, each page
     * consists of 512 bytes. This does NOT include the header.
     * @since 0.1.0.0
     */
    cobalt_u16_t pageCount;

    /**
     * @brief This is the count of relocations within the relocation table
     * object.
     * @since 0.1.0.0
     */
    cobalt_u16_t relocationCount;

    /**
     * @brief This is the size of the header piece of the file in
     * paragraphs, or 16 byte chunks.
     * @since 0.1.0.0
     */
    cobalt_u16_t headerSize;

    /**
     * @brief The minimum number of paragraphs required for the program to
     * start executing.
     * @since 0.1.0.0
     */
    cobalt_u16_t minimumParagraphs;

    /**
     * @brief The maximum number of paragraphs the program requests in
     * order to begin execution.
     * @since 0.1.0.0
     */
    cobalt_u16_t maximumParagraphs;

    /**
     * @brief The paragraph address of the stack memory segment, relative
     * to the beginning of the actual executable body.
     * @since 0.1.0.0
     */
    cobalt_u16_t stackSegment;

    /**
     * @brief The magic value that corresponds to the initial value the
     * stack pointer should be set to before the program is handed control.
     * @since 0.1.0.0
     */
    cobalt_u16_t initialStackValue;

    /**
     * @brief A checksum of the executable file's contents.
     * @since 0.1.0.0
     */
    cobalt_u16_t checksum;

    /**
     * @brief The magic value that corresponds to the instruction to begin
     * executing when the program is given control.
     * @since 0.1.0.0
     */
    cobalt_u16_t instructionPointer;

    /**
     * @brief The magic value that corresponds to the code segment needed
     * to be accessed in order to transfer control to the program.
     * @since 0.1.0.0
     */
    cobalt_u16_t codeSegmentInitializer;

    /**
     * @brief The offset from the beginning of the file to the relocation
     * pointer table.
     * @since 0.1.0.0
     */
    cobalt_u16_t relocationTableOffset;

    /**
     * @brief The number of overlays within the file. I was completely
     * unable to find a sensical description of what these "overlays" are.
     * @since 0.1.0.0
     */
    cobalt_u16_t overlayCount;

    PAD(8); // Reserved

    /**
     * @brief The unique identifier for the OEM. This is unique to the
     * Microsoft/EFI implementation of the PE format, which inserts this
     * into the DOS header.
     * @since 0.1.0.0
     */
    cobalt_u16_t oemID;

    /**
     * @brief A small bit of information the OEM has decided to include.
     * This is OEM-specific, and entirely useless for any purpose I've
     * thought of. Still kind of interesting to think about what might be
     * stored here. Like above, this is inserted by the PE format.
     * @since 0.1.0.0
     */
    cobalt_u16_t oemInfo;

    PAD(20); // Reserved

    /**
     * @brief The offset of the NT header relative to the beginning of this
     * file. This only exists in the PE format-specific kind of DOS header.
     * @since 0.1.0.0
     */
    cobalt_u32_t peHeaderOffset;
} cobalt_dos_header_t;

#endif // COBALT_HEADERS_DOS_H
