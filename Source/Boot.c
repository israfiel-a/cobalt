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

#include <efi.h>

/**
 * @brief The entrypoint of the kernel. EFI first hands off control at
 * this point, from which our OS sets up its environment.
 * @author Israfil Argos
 * @since 0.1.0
 *
 * @param ImageHandle The running EFI program image handle.
 * @param SystemTable The EFI system environment table. This is where
 * we can access important things like the output console.
 * @return The status of the run.
 */
EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle,
                           EFI_SYSTEM_TABLE *SystemTable)
{
    (void)ImageHandle;

    EFI_INPUT_KEY Key;
    EFI_STATUS Status =
        SystemTable->ConIn->Reset(SystemTable->ConIn, false);
    if (EFI_ERROR(Status)) return Status;

    while ((Status = SystemTable->ConIn->ReadKeyStroke(
                SystemTable->ConIn, &Key)) == EFI_NOT_READY);

    return Status;
}
