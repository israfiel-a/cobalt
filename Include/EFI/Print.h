/**
 * @file Print.h
 * @authors Israfil Argos (israfiel-a)
 * @brief An incredibly primitive implementation of printf and
 * printf-adjacent functions built specifically for use within the EFI
 * bootloader section of the operating system. All functions within this
 * file deal exclusively in UTF-16 strings.
 * @since 0.1.0
 *
 * @copyright (c) 2024 Israfil Argos
 * This file is under the AGPLv3. For information on what that entails, see
 * the attached LICENSE.md file or
 * https://www.gnu.org/licenses/agpl-3.0.en.html.
 */

#ifndef COBALT_EFI_PRINT_H
#define COBALT_EFI_PRINT_H

#include <EFI/Types.h>
#include <efi.h>
#include <efistdarg.h>

/**
 * @brief A simple output stream type as given to us by the EFI layer.
 * @authors Israfil Argos
 * @since 0.1.0
 */
typedef SIMPLE_TEXT_OUTPUT_INTERFACE *COBALT_OUTPUT_STREAM;

typedef SIMPLE_INPUT_INTERFACE *COBALT_INPUT_STREAM;

/**
 * @brief The EFI console output that Cobalt outputs all content to.
 * @authors Israfil Argos
 * @since 0.1.0
 */
extern COBALT_OUTPUT_STREAM cobalt_conOut;

extern COBALT_INPUT_STREAM cobalt_conIn;

/**
 * @brief Clear the screen. An incredibly simple function, this clears all
 * textual content from the console output.
 * @authors Israfil Argos
 * @since 0.1.0
 *
 * @return The success of the operation.
 */
EFI_STATUS Cobalt_PrimitiveClear(void);

/**
 * @brief An incredibly primitive formatted string printer using a
 * libc-style format string, with MUCH more simplified formatters. As
 * follows, the allowed formatters are: `s`: wide string, `L`: integer,
 * `U`: unsigned integer.
 * @authors Israfil Argos
 * @since 0.1.0
 *
 * @param format The format string to interleave with the supplied
 * arguments. If this is simply a string, it is far more advised to just
 * use the PrimitivePuts function.
 * @param ... The arguments to interleave with the format string.
 * @return The status code of the operation. Should a print fail, this will
 * be a failure as deigned by EFI_ERROR.
 *
 * @see Cobalt_PrimitivePuts
 * @see Cobalt_PrimitivePrintf
 */
EFI_STATUS Cobalt_PrimitivePrintfv(COBALT_WIDESTR format, va_list args);

/**
 * @brief An incredibly primitive formatted string printer using a
 * libc-style format string, with MUCH more simplified formatters. As
 * follows, the allowed formatters are: `s`: wide string, `L`: integer,
 * `U`: unsigned integer.
 * @authors Israfil Argos
 * @since 0.1.0
 *
 * @param format The format string to interleave with the supplied
 * arguments. If this is simply a string, it is far more advised to just
 * use the PrimitivePuts function.
 * @param ... The arguments to interleave with the format string.
 * @return The status code of the operation. Should a print fail, this will
 * be a failure as deigned by EFI_ERROR.
 *
 * @see Cobalt_PrimitivePuts
 * @see Cobalt_PrimitivePrintfv
 */
EFI_STATUS Cobalt_PrimitivePrintf(COBALT_WIDESTR format, ...);

/**
 * @brief A very, very simple function that pushes a string to the output
 * stream, without any sort of extra processing.
 * @authors Israfil Argos
 * @since 0.1.0
 *
 * @param string The string to output.
 * @return The status of the log operation.
 */
EFI_STATUS Cobalt_PrimitivePuts(COBALT_WIDESTR string);

EFI_STATUS Cobalt_PrimitiveTimestamp(COBALT_WIDESTR messageFormat, ...);

#endif // COBALT_EFI_PRINT_H
