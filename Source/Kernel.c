#include <Bootloader/EFI/Print.h>
#include <Bootloader/Types.h>

void kernel_main(cobalt_efi_info_t *efiInfo)
{
    Cobalt_PrimitivePuts(L"Hi from kernel!");
    (void)efiInfo;
    return;
}
