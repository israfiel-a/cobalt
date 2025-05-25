/**
 * @file Files.h
 * @authors Israfil Argos (israfiel-a)
 * @brief This file contains the Cobalt interface for opening files via the
 * UEFI framework's provided simple filesystem protocol.
 * @since 0.1.0.3
 * @updated 0.1.0.5
 *
 * @copyright (c) 2025 Israfil Argos
 * This file is under the AGPLv3. For information on what that entails, see
 * the attached LICENSE.md file or
 * https://www.gnu.org/licenses/agpl-3.0.en.html.
 */
#ifndef COBALT_BOOTLOADER_EFI_FILES_H
#define COBALT_BOOTLOADER_EFI_FILES_H

#include <efi.h>

#include <Headers/DOS.h>

typedef EFI_SIMPLE_FILE_SYSTEM_PROTOCOL cobalt_efi_filesystem_t;
typedef EFI_FILE cobalt_efi_root_volume_t;
typedef EFI_FILE cobalt_efi_file_t;

EFI_STATUS
Cobalt_OpenFilesystem(EFI_HANDLE *imageHandle, EFI_HANDLE *deviceHandle,
                      EFI_BOOT_SERVICES *bootServices,
                      cobalt_efi_filesystem_t **filesystem,
                      cobalt_efi_root_volume_t **root);

EFI_STATUS Cobalt_CloseFilesystem(EFI_HANDLE *imageHandle,
                                  EFI_BOOT_SERVICES *bootServices,
                                  cobalt_efi_filesystem_t *filesystem,
                                  cobalt_efi_root_volume_t *root);

EFI_STATUS Cobalt_OpenFile(cobalt_efi_root_volume_t *root,
                           unsigned short *path, cobalt_efi_file_t **file);

EFI_STATUS Cobalt_CloseFile(cobalt_efi_file_t *file);

EFI_STATUS Cobalt_ReadDOSHeader(cobalt_efi_file_t *file,
                                cobalt_dos_header_t *header);

#endif // COBALT_BOOTLOADER_EFI_FILES_H
