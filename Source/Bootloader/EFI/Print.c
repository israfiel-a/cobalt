/**
 * @file Print.c
 * @authors Israfil Argos (israfiel-a)
 * @brief The implementation of the primitive EFI printing routines
 * outlined in the EFI/Print.h file.
 *
 * @copyright (c) 2024 Israfil Argos
 * This file is under the AGPLv3. For information on what that entails, see
 * the attached LICENSE.md file or
 * https://www.gnu.org/licenses/agpl-3.0.en.html.
 */

#include <Bootloader/EFI/Print.h>
#include <Bootloader/Math.h>

EFI_STATUS Cobalt_PrimitiveClear(void)
{
    return cobalt_conOut->ClearScreen(cobalt_conOut);
}

EFI_STATUS Cobalt_PrimitivePrintfv(COBALT_WIDESTR format, va_list args)
{
    EFI_STATUS returnStatus = 0;

    int64_t i = -1;
    unsigned short currentCharacter = 1;
    while (currentCharacter != 0)
    {
        currentCharacter = format[++i];
        if (currentCharacter == L'%')
        {
            unsigned short iString[64];
            switch (format[i + 1])
            {
                case L's':
                    returnStatus = Cobalt_PrimitivePuts(
                        va_arg(args, unsigned short *));
                    i++;
                    continue;
                case L'L':
                    itoa_wide(va_arg(args, int64_t), iString, 10);
                    returnStatus = Cobalt_PrimitivePuts(iString);
                    i++;
                    continue;
                case L'U':
                    uitoa_wide(va_arg(args, uint64_t), iString, 10);
                    returnStatus = Cobalt_PrimitivePuts(iString);
                    i++;
                    continue;
            }
        }

        unsigned short strprint[2] = {currentCharacter, 0};
        Cobalt_PrimitivePuts(strprint);
    }

    return returnStatus;
}

EFI_STATUS Cobalt_PrimitivePrintf(unsigned short *format, ...)
{
    va_list args;
    va_start(args, format);

    EFI_STATUS status = Cobalt_PrimitivePrintfv(format, args);

    va_end(args);
    return status;
}

EFI_STATUS Cobalt_PrimitivePuts(COBALT_WIDESTR string)
{
    return cobalt_conOut->OutputString(cobalt_conOut, string);
}

EFI_STATUS Cobalt_PrimitiveTimestamp(COBALT_WIDESTR messageFormat, ...)
{
    va_list args;
    va_start(args, messageFormat);

    EFI_STATUS status = Cobalt_PrimitivePrintfv(messageFormat, args);
    if (EFI_ERROR(status)) return status;

    va_end(args);

    EFI_TIME time;
    cobalt_efiInfo.runtimeServices->GetTime(&time, nullptr);

    return Cobalt_PrimitivePrintf(
        L"%U/%U/%U @ %U:%U:%U" NL, (uint64_t)time.Day,
        (uint64_t)time.Month, (uint64_t)time.Year, (uint64_t)time.Hour,
        (uint64_t)time.Minute, (uint64_t)time.Second);
}
