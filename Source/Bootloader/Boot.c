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

#include <Bootloader/EFI/Graphics.h>
#include <Bootloader/EFI/Print.h>
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
            services->CloseEvent(timerEvent);
            return (EFI_STATUS)-8008;
        }
        if (key.UnicodeChar == L'c') break;
    }

    services->SetTimer(timerEvent, 0, 0);
    services->CloseEvent(timerEvent);
    return keyGrabStatus;
}

/**
 * @brief The entrypoint of the kernel loader. EFI first hands off control
 * at this point, from which our loader sets up its environment and loads
 * the kernel.
 * @authors Israfil Argos
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
    cobalt_conOut = SystemTable->ConOut;
    cobalt_conIn = SystemTable->ConIn;

    cobalt_efiInfo = (cobalt_efi_info_t){0};
    cobalt_efiInfo.runtimeServices = SystemTable->RuntimeServices;

    // Clear the screen of any text the UEFI environment may have splurged
    // out, and replace it with a nice friendly greeting.
    (void)Cobalt_PrimitiveClear();
    (void)Cobalt_PrimitivePuts(L"Hi! CobaltOS now booting. :) ");
    (void)Cobalt_PrimitiveTimestamp(L"Boot Time: ");

    const uint8_t firmwareTimeout = 5;
    Cobalt_PrimitivePrintf(L"Exit into firmware with 'f', continue with "
                           L"'c'. Continuing in %U seconds." NL,
                           firmwareTimeout);
    EFI_STATUS keyStatus =
        waitKey(firmwareTimeout, SystemTable->BootServices);
    if (keyStatus == (EFI_STATUS)-8008) return 0;
    Cobalt_PrimitivePuts(L"Continuing kernel load." NL NL);

    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE graphicsMode = {0};
    EFI_STATUS graphicsStatus = Cobalt_InitializeGraphics(
        &graphicsMode, ImageHandle, SystemTable->BootServices);
    if (EFI_ERROR(graphicsStatus)) return graphicsStatus;
    SystemTable->ConOut->SetCursorPosition(cobalt_conOut, 0, 0);
    Cobalt_PrimitivePuts(L"Setup graphics mode." NL);

    EFI_LOADED_IMAGE_PROTOCOL *kernelImage;
    EFI_GUID loadedImageProtocol = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_STATUS openProtocolStatus =
        SystemTable->BootServices->OpenProtocol(
            ImageHandle, &loadedImageProtocol, (void **)&kernelImage,
            ImageHandle, nullptr, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(openProtocolStatus))
    {
        Cobalt_PrimitivePuts(L"Failed to open image load protocol." NL);
        return openProtocolStatus;
    }
    Cobalt_PrimitivePuts(L"Opened image load protocol." NL);

    EFI_GUID simpleFilesystem = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *filesystem;
    openProtocolStatus = SystemTable->BootServices->OpenProtocol(
        kernelImage->DeviceHandle, &simpleFilesystem, (void **)&filesystem,
        ImageHandle, nullptr, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(openProtocolStatus))
    {
        Cobalt_PrimitivePrintf(
            L"Failed to open filesystem protocol. Code: %U." NL,
            (uint64_t)openProtocolStatus);
        waitKey(10, SystemTable->BootServices);
        return openProtocolStatus;
    }
    Cobalt_PrimitivePuts(L"Opened filesystem protocol." NL);

    EFI_FILE *root;
    EFI_STATUS rootOpenStatus = filesystem->OpenVolume(filesystem, &root);
    if (EFI_ERROR(rootOpenStatus))
    {
        Cobalt_PrimitivePrintf(L"Failed to open root volume. Code: %U." NL,
                               (uint64_t)rootOpenStatus);
        waitKey(10, SystemTable->BootServices);
        return rootOpenStatus;
    }

    EFI_FILE *kernelFile;
    EFI_STATUS kernelOpenStatus =
        root->Open(root, &kernelFile, L"\\KERNEL.efi", EFI_FILE_MODE_READ,
                   EFI_FILE_READ_ONLY);
    if (EFI_ERROR(kernelOpenStatus))
    {
        Cobalt_PrimitivePrintf(L"Failed to open kernel file. Code: %U." NL,
                               (uint64_t)kernelOpenStatus);
        waitKey(255, SystemTable->BootServices);
        return kernelOpenStatus;
    }
    Cobalt_PrimitivePuts(L"Opened kernel file." NL);

    return keyStatus;
}
