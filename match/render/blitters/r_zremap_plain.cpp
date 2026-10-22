// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Paired /GX and no-/GX builds leave all twelve ordinary method spans identical;
// the exception-handling flag is not determined by these methods.
// Cluster r-zremap, family RLEBlitTransZRemapXlat<T> (no depth test). See r_zremap.h for the layout.
//
// Full entry-to-RET spans for the ordinary methods in this TU; current Ghidra
// extents and raw REA input lengths agree. Harness deleting wrappers are excluded.
//   0x4918E0 unsigned char RLEBlit (0x89)
//   0x491970 unsigned char RLEBlitTint (0x3A)
//   0x496170 unsigned short RLEBlit (0x91)
//   0x496210 unsigned short RLEBlitTint (0x3A)

#include "r_zremap.h"

// TEMPLATE: GAMEMD 0x4918E0
// RLEBlitTransZRemapXlat<unsigned char>::RLEBlit
template <>
void RLEBlitTransZRemapXlat<unsigned char>::RLEBlit(void* dest, const void* src, int len,
                                        int skip, int, unsigned short*,
                                        unsigned short*, int, int,
                                        const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    typedef unsigned char T;
    T* d = static_cast<T*>(dest);
    const unsigned char* rm = *remap;

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
            *d++ = table[rm[c]];
            len--;
        }
    }
}

// TEMPLATE: GAMEMD 0x491970
// RLEBlitTransZRemapXlat<unsigned char>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlat<unsigned char>::RLEBlitTint(void* dest, const void* src, int len,
                                            int skip, int zval,
                                            unsigned short* zbuf,
                                            unsigned short* abuf, int alvl,
                                            int warp, const signed char* zshape,
                                            unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x496170
// RLEBlitTransZRemapXlat<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlat<unsigned short>::RLEBlit(void* dest, const void* src, int len,
                                        int skip, int, unsigned short*,
                                        unsigned short*, int, int,
                                        const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    typedef unsigned short T;
    T* d = static_cast<T*>(dest);
    const unsigned char* rm = *remap;

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
            *d++ = table[rm[c]];
            len--;
        }
    }
}

// TEMPLATE: GAMEMD 0x496210
// RLEBlitTransZRemapXlat<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlat<unsigned short>::RLEBlitTint(void* dest, const void* src, int len,
                                            int skip, int zval,
                                            unsigned short* zbuf,
                                            unsigned short* abuf, int alvl,
                                            int warp, const signed char* zshape,
                                            unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}
