#ifndef COBALT_TYPES_H
#define COBALT_TYPES_H

typedef unsigned char cobalt_u8_t;
typedef unsigned short cobalt_u16_t;
typedef unsigned int cobalt_u32_t;
typedef unsigned long cobalt_u64_t;

typedef signed char cobalt_i8_t;
typedef signed short cobalt_i16_t;
typedef signed int cobalt_i32_t;
typedef signed long cobalt_i64_t;

// defined in this weird way so as to be VERY unlikely to collide with
// structure members
#define PAD_IMPLICIT(bitLength, count)                                    \
    char padBit##bitLength##count[bitLength]
#define PAD_INTERNAL(bitLength, count) PAD_IMPLICIT(bitLength, count)
#define PAD(bitLength) PAD_INTERNAL(bitLength, __COUNTER__)

#endif // COBALT_TYPES_H
