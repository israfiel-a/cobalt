/**
 * @file Print.h
 * @authors Israfil Argos (israfiel-a)
 * @brief An incredibly primitive implementation of printf built
 * specifically for use within the EFI bootloader section of the operating
 * system. All functions within this file deal exclusively in UTF-16
 * strings.
 * @since 0.1.0
 *
 * @copyright (c) 2024 Israfil Argos
 * This file is under the AGPLv3. For information on what that entails, see
 * the attached LICENSE.md file or
 * https://www.gnu.org/licenses/agpl-3.0.en.html.
 */

#ifndef COBALT_EFI_PRINT
#define COBALT_EFI_PRINT

#include <EFI/Types.h>
#include <efi.h>

/**
 * @brief A simple output stream type as given to us by the EFI layer.
 * @authors Israfil Argos
 * @since 0.1.0
 */
typedef SIMPLE_TEXT_OUTPUT_INTERFACE *COBALT_OUTPUT_STREAM;

/**
 * @brief The EFI console output that Cobalt outputs all content to.
 * @authors Israfil Argos
 * @since 0.1.0
 */
extern COBALT_OUTPUT_STREAM cobalt_conOut;

/**
 * @brief An incredibly primitive formatted string printer using a
 * libc-style format string, with MUCH more simplified formatters. As
 * follows, the allowed formatters are: `s`: wide string, `L`: int64, `U`:
 * uint64, `I`: int32, `u` uint32, `i`: int16, `V`: uint16, `b`: int8, `v`:
 * uint8.
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
 * @see EFI_ERROR
 * @see Cobalt_PrimitivePuts
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

#endif // COBALT_EFI_PRINT
