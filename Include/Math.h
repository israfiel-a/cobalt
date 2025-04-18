#ifndef COBALT_MATH_H
#define COBALT_MATH_H

#include <stdint.h>

int itoa_wide(int64_t value, unsigned short *sp, int radix);
int uitoa_wide(uint64_t value, unsigned short *sp, int radix);

#endif // COBALT_MATH_H
