// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M3 r-lucent75 method packet, SHA-verified; method spans
// are checked against pinned gamemd.exe v1.001. This TU contains only the
// explicit unsigned-short RLE leaf method specializations below. It does not
// claim constructors, deleting destructors, alpha-pool ownership or vtable emission.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
#include "r_lucent75.h"

// TEMPLATE: GAMEMD 0x496310
// RLEBlitTransLucent75<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75<unsigned short>::RLEBlit(void* dest, const void* src, int len,
                                      int skip, int, unsigned short*,
                                      unsigned short*, int, int,
                                      const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            unsigned short t = table[c];
            unsigned short m = mask;
            *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
            d++;
            len--;
        }
    }
}

// TEMPLATE: GAMEMD 0x4963B0
// RLEBlitTransLucent75<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75<unsigned short>::RLEBlitTint(void* dest, const void* src, int len,
                                          int skip, int zval,
                                          unsigned short* zbuf,
                                          unsigned short* abuf, int alvl,
                                          int warp, const signed char* zshape,
                                          unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}
