// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; frozen milestone-2 b-plainxlat source.
#include <string.h>
#include "b_plainxlat.h"
#include "b_xlatalpha.h"   // BlitAlphaWrapRow

// LIBRARY: GAMEMD 0x7CA090 -- CRT memmove (__cdecl).

// TEMPLATE: GAMEMD 0x4913F0
// BlitPlainXlat<unsigned char>::BlitCopy
template <>
void BlitPlainXlat<unsigned char>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned char* d = (unsigned char*)dest;
        do {
            unsigned char c = *s++;
            *d++ = xlat[c];
        } while (--len);
    }
}

// TEMPLATE: GAMEMD 0x491430
// BlitPlainXlat<unsigned char>::BlitMove
template <>
void BlitPlainXlat<unsigned char>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x491460
// BlitPlainXlat<unsigned char>::BlitCopyTint
template <>
void BlitPlainXlat<unsigned char>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x491490
// BlitPlainXlat<unsigned char>::BlitMoveTint
template <>
void BlitPlainXlat<unsigned char>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x4924C0
// BlitPlainXlat<unsigned short>::BlitCopy
template <>
void BlitPlainXlat<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        do {
            unsigned char c = *s++;
            *d++ = xlat[c];
        } while (--len);
    }
}

// TEMPLATE: GAMEMD 0x492500
// BlitPlainXlat<unsigned short>::BlitMove
template <>
void BlitPlainXlat<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x492530
// BlitPlainXlat<unsigned short>::BlitCopyTint
template <>
void BlitPlainXlat<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x492560
// BlitPlainXlat<unsigned short>::BlitMoveTint
template <>
void BlitPlainXlat<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x492A10
// BlitPlainXlatZRead<unsigned short>::BlitCopy
template <>
void BlitPlainXlatZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        int n = len;
        do {
            if (zval < *z++) *(unsigned short*)dest = xlat[*(const unsigned char*)src];
            src = (const unsigned char*)src + 1;
            dest = (unsigned short*)dest + 1;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// TEMPLATE: GAMEMD 0x492A70
// BlitPlainXlatZRead<unsigned short>::BlitMove
template <>
void BlitPlainXlatZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x492AA0
// BlitPlainXlatZRead<unsigned short>::BlitCopyTint
template <>
void BlitPlainXlatZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x492AD0
// BlitPlainXlatZRead<unsigned short>::BlitMoveTint
template <>
void BlitPlainXlatZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x493500
// BlitPlainXlatZReadWrite<unsigned short>::BlitCopy
template <>
void BlitPlainXlatZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z) {
                *d = xlat[*s];
                *z = (unsigned char)zval;
            }
            ++s; ++d; ++z;
            if (z >= gg_rle_zwrap_global->wrap_end)
                z = (unsigned short*)((unsigned char*)z - gg_rle_zwrap_global->wrap_step);
        } while (--n);
    }
}

// TEMPLATE: GAMEMD 0x493570
// BlitPlainXlatZReadWrite<unsigned short>::BlitMove
template <>
void BlitPlainXlatZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x4935A0
// BlitPlainXlatZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitPlainXlatZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x4935D0
// BlitPlainXlatZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitPlainXlatZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x493CC0
// BlitPlainXlatAlpha<unsigned short>::BlitCopy
template <>
void BlitPlainXlatAlpha<unsigned short>::BlitCopy(void* dest, const void* src, int len,
                                                  int, unsigned short*, unsigned short* abuf,
                                                  int alvl, int)
{
    unsigned short* ab = abuf;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 254)
        level = 254;
    unsigned short* row = alpha + (level << 8);
    if (len > 0) {
        int n = len;
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        do {
            unsigned char c = *s;
            unsigned int a = *ab++;
            s++;
            *d++ = xlat[row[a] | c];
            ab = BlitAlphaWrapRow(ab);
        } while (--n);
    }
}

// TEMPLATE: GAMEMD 0x493D60
// BlitPlainXlatAlpha<unsigned short>::BlitMove
template <>
void BlitPlainXlatAlpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x493D90
// BlitPlainXlatAlpha<unsigned short>::BlitCopyTint
template <>
void BlitPlainXlatAlpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TEMPLATE: GAMEMD 0x493DC0
// BlitPlainXlatAlpha<unsigned short>::BlitMoveTint
template <>
void BlitPlainXlatAlpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
