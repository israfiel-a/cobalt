#include <Bootloader/EFI/Files.h>
#include <Bootloader/EFI/Print.h>

EFI_STATUS
Cobalt_OpenFilesystem(EFI_HANDLE *imageHandle, EFI_HANDLE *deviceHandle,
                      EFI_BOOT_SERVICES *bootServices,
                      cobalt_efi_filesystem_t **filesystem,
                      cobalt_efi_root_volume_t **root)
{
    EFI_GUID simpleFilesystemGUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_STATUS status = bootServices->OpenProtocol(
        deviceHandle, &simpleFilesystemGUID, (void **)filesystem,
        imageHandle, nullptr, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(status))
    {
        (void)Cobalt_PrimitivePrintf(
            L"Failed to open filesystem protocol. Code: %U." NL, status);
        return status;
    }
    (void)Cobalt_PrimitivePuts(L"Opened filesystem protocol." NL);

    status = (*filesystem)->OpenVolume(*filesystem, root);
    if (EFI_ERROR(status))
    {
        (void)Cobalt_PrimitivePrintf(
            L"Failed to open root volume. Code: %U." NL, status);
        return status;
    }
    (void)Cobalt_PrimitivePuts(L"Opened root volume." NL);

    return status;
}

EFI_STATUS Cobalt_CloseFilesystem(EFI_HANDLE *imageHandle,
                                  EFI_BOOT_SERVICES *bootServices,
                                  cobalt_efi_filesystem_t *filesystem)
{
    EFI_GUID simpleFilesystemGUID = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_STATUS status = bootServices->CloseProtocol(
        filesystem, &simpleFilesystemGUID, imageHandle, nullptr);
    if (EFI_ERROR(status))
        Cobalt_PrimitivePrintf(
            L"Failed to close filesystem protocol. Code: %U." NL, status);
    else Cobalt_PrimitivePuts(L"Closed filesystem protocol." NL);

    return status;
}

EFI_STATUS Cobalt_OpenFile(cobalt_efi_root_volume_t *root,
                           unsigned short *path, cobalt_efi_file_t **file)
{
    EFI_STATUS status = root->Open(root, file, path, EFI_FILE_MODE_READ,
                                   EFI_FILE_READ_ONLY);
    if (EFI_ERROR(status))
        Cobalt_PrimitivePrintf(
            L"Failed to open file at path '%s'. Code: %U." NL, path,
            status);
    else Cobalt_PrimitivePrintf(L"Opened file at path '%s'." NL, path);
    return status;
}
