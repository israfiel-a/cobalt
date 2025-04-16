#include <Math.h>

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
