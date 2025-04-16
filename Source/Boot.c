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
#include <stdarg.h>

#define NL L"\n\r"

#define OUTPUT(message)                                                   \
    returnStatus = stdout->OutputString(stdout, message);                 \
    if (EFI_ERROR(returnStatus)) return returnStatus;

static SIMPLE_TEXT_OUTPUT_INTERFACE *stdout = nullptr;

int itoa_wide(int value, unsigned short *sp, int radix)
{
    unsigned short tmp[64]; // be careful with the length of the buffer
    unsigned short *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);
    if (sign) v = -value;
    else v = (unsigned)value;

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix;
        if (i < 10) *tp++ = i + L'0';
        else *tp++ = i + L'a' - 10;
    }

    int len = tp - tmp;

    if (sign)
    {
        *sp++ = L'-';
        len++;
    }

    while (tp > tmp) *sp++ = *--tp;

    return len;
}

EFI_STATUS primitive_printf(unsigned short *format, ...)
{
    va_list args;
    va_start(args, format);

    EFI_STATUS returnStatus = 0;

    size_t i = 0;
    unsigned short currentCharacter = format[i];
    while (currentCharacter != 0)
    {
        if (currentCharacter == L'%')
        {
            currentCharacter = format[++i];
            switch (currentCharacter)
            {
                case L's': OUTPUT(va_arg(args, unsigned short *)); break;
                case L'i':
                    unsigned short iString[64];
                    int length =
                        itoa_wide(va_arg(args, int64_t), iString, 10);
                    iString[length] = 0;
                    OUTPUT(iString);
                    break;
            }
        }
        else
        {
            unsigned short strprint[2] = {currentCharacter, 0};
            OUTPUT(strprint);
        }
        currentCharacter = format[++i];
    }

    va_end(args);
    return returnStatus;
}

/**
 * @brief The entrypoint of the kernel. EFI first hands off control at
 * this point, from which our OS sets up its environment.
 * @author Israfil Argos
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
    stdout = SystemTable->ConOut;

    EFI_STATUS returnStatus = 0;

    // Clear the screen of any text the UEFI environment may have splurged
    // out, and replace it with a nice friendly greeting.
    (void)stdout->ClearScreen(stdout);
    OUTPUT(L"Hi! CobaltOS now booting. :)" NL);

    EFI_TIME time;
    EFI_TIME_CAPABILITIES timeCapabilities;
    SystemTable->RuntimeServices->GetTime(&time, &timeCapabilities);

    primitive_printf(L"Boot time: %i/%i/%i @ %i:%i:%i" NL, (INT64)time.Day,
                     (INT64)time.Month, (INT64)time.Year, (INT64)time.Hour,
                     (INT64)time.Minute, (INT64)time.Second);

    EFI_INPUT_KEY Key;
    EFI_STATUS Status =
        SystemTable->ConIn->Reset(SystemTable->ConIn, false);
    if (EFI_ERROR(Status)) return Status;

    while ((Status = SystemTable->ConIn->ReadKeyStroke(
                SystemTable->ConIn, &Key)) == EFI_NOT_READY);

    return Status;
}
