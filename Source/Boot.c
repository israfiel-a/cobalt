#include <efi.h>

#define COBALT_EFI_CALL(expr)                                             \
    {                                                                     \
        EFI_STATUS status = expr;                                         \
        if (EFI_ERROR(status)) return status;                             \
    }

static EFI_SYSTEM_TABLE *systemTable = nullptr;

static EFI_STATUS clearOutput()
{
    return systemTable->ConOut->ClearScreen(systemTable->ConOut);
}

static EFI_STATUS logString(unsigned short *string)
{
    return systemTable->ConOut->OutputString(systemTable->ConOut, string);
}

// https://stackoverflow.com/questions/3440726/what-is-the-proper-way-of-implementing-a-good-itoa-function
// static int itoa(uint64_t value, char *sp, int radix)
// {
//     char tmp[64]; // be careful with the length of the buffer
//     char *tp = tmp;
//     int i;
//     unsigned v = (unsigned)value;

//     while (v || tp == tmp)
//     {
//         i = v % radix;
//         v /= radix;
//         if (i < 10) *tp++ = i + '0';
//         else *tp++ = i + 'a' - 10;
//     }

//     int len = tp - tmp;

//     while (tp > tmp) *sp++ = *--tp;

//     return len;
// }

/**
 * @brief The entrypoint of the kernel. EFI first hands off control at
 * this point, from which our OS sets up its environment.
 * @author Israfil Argos
 * @since 0.1.0
 *
 * @param _ImageHandle Unused EFI image handle.
 * @param SystemTable The EFI system environment table. This is where
 * we can access important things like the output console.
 * @return The status of the run.
 */
EFI_STATUS
efi_main(EFI_HANDLE _ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    // We use the image handle for precisely nothing.
    (void)_ImageHandle;

    systemTable = SystemTable;
    COBALT_EFI_CALL(clearOutput());
    COBALT_EFI_CALL(logString(L"CobaltOS now booting... :)\n\r"));

    /* Empty the console input buffer to flush out any keystrokes
     * entered before this point. */
    EFI_STATUS Status =
        SystemTable->ConIn->Reset(SystemTable->ConIn, false);
    if (EFI_ERROR(Status)) return Status;

    /* Wait for keypress. */
    EFI_INPUT_KEY Key;
    while ((Status = SystemTable->ConIn->ReadKeyStroke(
                SystemTable->ConIn, &Key)) == EFI_NOT_READY);

    return Status;
}
