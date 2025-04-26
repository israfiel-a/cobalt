#ifndef COBALT_BOOTLOADER_EFI_GRAPHICS_H
#define COBALT_BOOTLOADER_EFI_GRAPHICS_H

#include <efi.h>

EFI_STATUS
Cobalt_InitializeGraphics(EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *graphicsMode,
                          EFI_HANDLE *imageHandle,
                          EFI_BOOT_SERVICES *services);

#endif // COBALT_BOOTLOADER_EFI_GRAPHICS_H
