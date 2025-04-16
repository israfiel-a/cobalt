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

#include <EFI/Print.h>
#include <Math.h>
#include <stdarg.h>

EFI_STATUS Cobalt_PrimitivePrintf(unsigned short *format, ...)
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
                case L's':
                    Cobalt_PrimitivePuts(va_arg(args, unsigned short *));
                    break;
                case L'i':
                    unsigned short iString[64];
                    int length =
                        itoa_wide(va_arg(args, int64_t), iString, 10);
                    iString[length] = 0;
                    Cobalt_PrimitivePuts(iString);
                    break;
            }
        }
        else
        {
            unsigned short strprint[2] = {currentCharacter, 0};
            Cobalt_PrimitivePuts(strprint);
        }
        currentCharacter = format[++i];
    }

    va_end(args);
    return returnStatus;
}

EFI_STATUS Cobalt_PrimitivePuts(COBALT_WIDESTR string)
{
    return cobalt_conOut->OutputString(cobalt_conOut, string);
}
