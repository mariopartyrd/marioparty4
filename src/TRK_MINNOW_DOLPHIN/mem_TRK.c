#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/mem_TRK.h"
#include "dolphin/types.h"

void TRK_fill_mem(void *dest, int value, unsigned long length)
{
#define cDest ((unsigned char *)dest)
#define lDest ((unsigned long *)dest)
    unsigned long val = (unsigned char)value;
    unsigned long i;
    lDest = (unsigned long *)dest;
    cDest = (unsigned char *)dest;

    cDest--;

    if (length >= 32) {
        i = ~(unsigned long)dest & 3;

        if (i) {
            length -= i;
            do {
                *++cDest = val;
            } while (--i);
        }

        if (val) {
            val |= val << 24 | val << 16 | val << 8;
        }

        lDest = (unsigned long *)(cDest + 1) - 1;

        i = length >> 5;
        if (i) {
            do {
                *++lDest = val;
                *++lDest = val;
                *++lDest = val;
                *++lDest = val;
                *++lDest = val;
                *++lDest = val;
                *++lDest = val;
                *++lDest = val;
            } while (--i);
        }

        i = (length & 31) >> 2;

        if (i) {
            do {
                *++lDest = val;
            } while (--i);
        }

        cDest = (unsigned char *)(lDest + 1) - 1;

        length &= 3;
    }

    if (length) {
        do {
            *++cDest = val;
        } while (--length);
    }

#undef cDest
#undef lDest
}

__declspec(section ".init") void *TRK_memcpy(void *dst, const void *src, size_t n)
{
    const char *p;
    char *q;

    for (p = (const char *)src - 1, q = (char *)dst - 1, n++; --n;)
        *++q = *++p;

    return dst;
}

__declspec(section ".init") void *TRK_memset(void *dst, int val, size_t n)
{
    TRK_fill_mem(dst, val, n);
    return dst;
}
