// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Paired /GX and no-/GX builds leave all twelve ordinary method spans identical;
// the exception-handling flag is not determined by these methods.
// Cluster r-zremap, family RLEBlitTransZRemapXlatZReadWrite<T> (depth test and
// depth write). See r_zremap.h for the layout and r_shared_zwrap.h for
// the Z row wrap.
//
// Full entry-to-RET spans for the ordinary methods in this TU; current Ghidra
// extents and raw REA input lengths agree. Harness deleting wrappers are excluded.
//   0x492100 unsigned char RLEBlit (0x108)
//   0x492210 unsigned char RLEBlitTint (0x3A)
//   0x497230 unsigned short RLEBlit (0x111)
//   0x497350 unsigned short RLEBlitTint (0x3A)

#include "r_zremap.h"

// TEMPLATE: GAMEMD 0x492100
// RLEBlitTransZRemapXlatZReadWrite<unsigned char>::RLEBlit
template <>
void RLEBlitTransZRemapXlatZReadWrite<unsigned char>::RLEBlit(void* dest, const void* src,
                                             int len, int skip, int zval,
                                             unsigned short* zbuf,
                                             unsigned short*, int, int,
                                             const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    typedef unsigned char T;
    T* d = static_cast<T*>(dest);
    const unsigned char* rm = *remap;
    unsigned short* z = zbuf;

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
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z)
            {
                *d++ = table[rm[c]];
                *z++ = zval - *zs++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TEMPLATE: GAMEMD 0x492210
// RLEBlitTransZRemapXlatZReadWrite<unsigned char>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatZReadWrite<unsigned char>::RLEBlitTint(void* dest, const void* src,
                                                 int len, int skip, int zval,
                                                 unsigned short* zbuf,
                                                 unsigned short* abuf, int alvl,
                                                 int warp,
                                                 const signed char* zshape,
                                                 unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x497230
// RLEBlitTransZRemapXlatZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlatZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src,
                                             int len, int skip, int zval,
                                             unsigned short* zbuf,
                                             unsigned short*, int, int,
                                             const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    typedef unsigned short T;
    T* d = static_cast<T*>(dest);
    const unsigned char* rm = *remap;
    unsigned short* z = zbuf;

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
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z)
            {
                *d++ = table[rm[c]];
                *z++ = zval - *zs++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TEMPLATE: GAMEMD 0x497350
// RLEBlitTransZRemapXlatZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                                 int len, int skip, int zval,
                                                 unsigned short* zbuf,
                                                 unsigned short* abuf, int alvl,
                                                 int warp,
                                                 const signed char* zshape,
                                                 unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}
