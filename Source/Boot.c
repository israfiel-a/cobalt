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

// should probably get rid of this to not waste memory when kernel invoked
// maybe flatten into kernel structure?
COBALT_OUTPUT_STREAM cobalt_conOut = nullptr;
COBALT_INPUT_STREAM cobalt_conIn = nullptr;

static EFI_STATUS waitKey(uint8_t timeOut, EFI_BOOT_SERVICES *services)
{
    EFI_STATUS resetStatus = cobalt_conIn->Reset(cobalt_conIn, false);
    if (EFI_ERROR(resetStatus)) return resetStatus;

    EFI_EVENT timerEvent;
    services->CreateEvent(EVT_TIMER, TPL_APPLICATION, nullptr, nullptr,
                          &timerEvent);
    services->SetTimer(timerEvent, 1, 10000000);

    EFI_INPUT_KEY key;
    EFI_STATUS keyGrabStatus;
    for (uint64_t timeOutSpent = 0; timeOutSpent < timeOut; timeOutSpent++)
    {
        UINTN index;
        services->WaitForEvent(1, &timerEvent, &index);

        keyGrabStatus = cobalt_conIn->ReadKeyStroke(cobalt_conIn, &key);
        if (keyGrabStatus == EFI_NOT_READY) continue;

        if (key.UnicodeChar == L'f')
        {
            services->SetTimer(timerEvent, 0, 0);
            return (EFI_STATUS)-8008;
        }
    }

    services->SetTimer(timerEvent, 0, 0);
    return keyGrabStatus;
}

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
    cobalt_conIn = SystemTable->ConIn;

    cobalt_efiInfo = (cobalt_efi_info_t){.runtimeServices =
                                             SystemTable->RuntimeServices};

    // Clear the screen of any text the UEFI environment may have splurged
    // out, and replace it with a nice friendly greeting.
    (void)Cobalt_PrimitiveClear();
    (void)Cobalt_PrimitivePuts(L"Hi! CobaltOS now booting. :) ");
    (void)Cobalt_PrimitiveTimestamp(L"Boot Time: ");

    uint8_t firmwareTimeout = 5;
    Cobalt_PrimitivePrintf(
        L"Exit into firmware with 'f'. Continuing in %U seconds.",
        firmwareTimeout);
    EFI_STATUS keyStatus =
        waitKey(firmwareTimeout, SystemTable->BootServices);
    if (keyStatus == (EFI_STATUS)-8008) return 0;

    return keyStatus;
}
