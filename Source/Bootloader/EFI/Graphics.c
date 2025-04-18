#include <Bootloader/EFI/Graphics.h>
#include <Bootloader/EFI/Print.h>

EFI_STATUS
Cobalt_InitializeGraphics(EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *graphicsMode,
                          EFI_HANDLE *imageHandle,
                          EFI_BOOT_SERVICES *services)
{
    EFI_GUID graphicsGUID = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

    UINTN graphicsDeviceCount;
    EFI_HANDLE *graphicsDevices;
    services->LocateHandleBuffer(ByProtocol, &graphicsGUID, nullptr,
                                 &graphicsDeviceCount, &graphicsDevices);
    Cobalt_PrimitivePrintf(L"Found %U graphics device(s).",
                           graphicsDeviceCount);

    // We just configure the first graphics device. Cobalt has absolutely
    // no business running more than that T-T
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gopProtocol;
    services->OpenProtocol(graphicsDevices[0], &graphicsGUID,
                           (void **)&gopProtocol, imageHandle, nullptr,
                           EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    gopProtocol->SetMode(gopProtocol, 0);

    services->AllocatePool(EfiLoaderData, gopProtocol->Mode->SizeOfInfo,
                           (void **)&graphicsMode->Info);
    graphicsMode->MaxMode = gopProtocol->Mode->MaxMode;
    graphicsMode->Mode = gopProtocol->Mode->Mode;
    graphicsMode->SizeOfInfo = gopProtocol->Mode->SizeOfInfo;

    graphicsMode->FrameBufferBase = gopProtocol->Mode->FrameBufferBase;
    graphicsMode->FrameBufferSize = gopProtocol->Mode->FrameBufferSize;
    *(graphicsMode->Info) = *(gopProtocol->Mode->Info);

    services->FreePool(graphicsDevices);
    return 0;
}
