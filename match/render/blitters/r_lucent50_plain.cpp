// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M3 candidate; instructions revalidated against pinned retail gamemd.exe.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Cluster r-lucent50, families RLEBlitTransLucent50<us> and
// RLEBlitTransLucent50Alpha<us> (no depth test). No /GX, as the other blitter
// families. See r_lucent50.h for the layout.
//
// Spans (entry, length): Lucent50 RLEBlit 0x4963F0 (0x9A), Tint 0x496490 (0x3A);
// Alpha RLEBlit 0x497CF0 (0x12B), Tint 0x497E20 (0x3A).
// Results: Lucent50 RLEBlit and both Tint shims 100%.
// Alpha RLEBlit 0x497CF0 now 100% using the r_lucent25_alpha.cpp body structure.
#include "r_lucent50.h"


// TEMPLATE: GAMEMD 0x4963F0
// RLEBlitTransLucent50<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                      int, unsigned short*, unsigned short*, int, int,
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
            *d = ((table[c] >> 1) & mask) + ((*d >> 1) & mask);
            len--;
            d++;
        }
    }
}

// TEMPLATE: GAMEMD 0x496490
// RLEBlitTransLucent50<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                          int zval, unsigned short* zbuf,
                                          unsigned short* abuf, int alvl, int warp,
                                          const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x497CF0
// RLEBlitTransLucent50Alpha<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50Alpha<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                           int, unsigned short*, unsigned short* abuf,
                                           int alvl, int, const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha_handle) + (a << 9);

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
        ab = RLELucent50AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            ab += c;
        }
        else
        {
            unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
            *d = ((table[idx] >> 1) & mask) + ((*d >> 1) & mask);
            d++;
            len--;
            ab++;
        }
        ab = RLELucent50AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x497E20
// RLEBlitTransLucent50Alpha<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50Alpha<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                               int zval, unsigned short* zbuf,
                                               unsigned short* abuf, int alvl, int warp,
                                               const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}
