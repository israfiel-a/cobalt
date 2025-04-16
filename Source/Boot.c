/**
 * @file Boot.c
 * @authors Israfil Argos (israfiel-a)
 * @brief The boot entrypoint of the operating system, in which we handle
 * tbe most basic of setup before exiting the UEFI environment and entering
 * kernelmode.
 * @since 0.1.0
 *
 * @copyright (c) 2024 Israfil Argos
 * This file is under the AGPLv3. For information on what that entails, see
 * the attached LICENSE.md file or
 * https://www.gnu.org/licenses/agpl-3.0.en.html.
 */

#include <EFI/Print.h>
#include <efi.h>
#include <stdarg.h>

#define OUTPUT(message)                                                   \
    returnStatus = cobalt_conOut->OutputString(cobalt_conOut, message);   \
    if (EFI_ERROR(returnStatus)) return returnStatus;

COBALT_OUTPUT_STREAM cobalt_conOut = nullptr;

/**
 * @brief The entrypoint of the kernel. EFI first hands off control at
 * this point, from which our OS sets up its environment.
 * @authors Israfil Argos
 * @since 0.1.0
 *
 * @param _ImageHandle The running EFI program image handle. We do not ever
 * use this.
 * @param SystemTable The EFI system environment table. This is where
 * we can access important things like the output console.
 * @return The status of the run.
 */
EFI_STATUS EFIAPI efi_main(EFI_HANDLE _ImageHandle,
                           EFI_SYSTEM_TABLE *SystemTable)
{
    (void)_ImageHandle;
    cobalt_conOut = SystemTable->ConOut;

    EFI_STATUS returnStatus = 0;

    // Clear the screen of any text the UEFI environment may have splurged
    // out, and replace it with a nice friendly greeting.
    (void)cobalt_conOut->ClearScreen(cobalt_conOut);
    OUTPUT(L"Hi! CobaltOS now booting. :)" NL);

    EFI_TIME time;
    EFI_TIME_CAPABILITIES timeCapabilities;
    SystemTable->RuntimeServices->GetTime(&time, &timeCapabilities);

    Cobalt_PrimitivePrintf(L"Boot time: %i/%i/%i @ %i:%i:%i" NL,
                           (INT64)time.Day, (INT64)time.Month,
                           (INT64)time.Year, (INT64)time.Hour,
                           (INT64)time.Minute, (INT64)time.Second);

    EFI_INPUT_KEY Key;
    EFI_STATUS Status =
        SystemTable->ConIn->Reset(SystemTable->ConIn, false);
    if (EFI_ERROR(Status)) return Status;

    while ((Status = SystemTable->ConIn->ReadKeyStroke(
                SystemTable->ConIn, &Key)) == EFI_NOT_READY);

    return Status;
}
