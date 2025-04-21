#include <Bootloader/Memory.h>
#include <stdint.h>

void Cobalt_ZeroMemory(void *buffer, size_t size)
{
    uint8_t *temporary = buffer;
    size_t sizeCount = size;
    while (--sizeCount) *temporary = 0;
}
