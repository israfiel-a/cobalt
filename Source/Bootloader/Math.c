#include <Bootloader/Math.h>

int itoa_wide(int64_t value, unsigned short *sp, int radix)
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
    *sp = 0;

    return len;
}

int uitoa_wide(uint64_t value, unsigned short *sp, int radix)
{
    unsigned short tmp[64]; // be careful with the length of the buffer
    unsigned short *tp = tmp;
    int i;

    while (value || tp == tmp)
    {
        i = value % radix;
        value /= radix;
        if (i < 10) *tp++ = i + L'0';
        else *tp++ = i + L'a' - 10;
    }

    int len = tp - tmp;

    while (tp > tmp) *sp++ = *--tp;
    *sp = 0;

    return len;
}
