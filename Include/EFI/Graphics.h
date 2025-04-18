#ifndef COBALT_EFI_GRAPHICS_H
#define COBALT_EFI_GRAPHICS_H

#include <efi.h>

typedef struct
{
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *framebufferArray;
    uint64_t framebufferCount;
} cobalt_efi_framebuffers_t;

EFI_STATUS
Cobalt_InitializeGraphics(cobalt_efi_framebuffers_t *framebuffers);

#endif // COBALT_EFI_GRAPHICS_H
