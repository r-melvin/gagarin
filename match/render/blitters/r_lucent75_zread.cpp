// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M3 r-lucent75 method packet, SHA-verified; method spans
// are checked against pinned gamemd.exe v1.001. This TU contains only the
// explicit unsigned-short RLE leaf method specializations below. It does not
// claim constructors, deleting destructors, alpha-pool ownership or vtable emission.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
#include "r_lucent75.h"

// TEMPLATE: GAMEMD 0x496930
// RLEBlitTransLucent75ZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75ZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short*, int,
                       int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
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
            if (zval - *zs++ < *z++)
            {
                unsigned short t = table[c];
                unsigned short m = mask;
                *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TEMPLATE: GAMEMD 0x496A40
// RLEBlitTransLucent75ZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75ZRead<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                               int len, int skip, int zval,
                                               unsigned short* zbuf,
                                               unsigned short* abuf, int alvl,
                                               int warp,
                                               const signed char* zshape,
                                               unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x496D10
// RLEBlitTransLucent75ZReadWarp<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75ZReadWarp<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short*, int,
                       int warp, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
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
            if (zval - *zs++ < *z++)
            {
                unsigned short t = table[c];
                unsigned short m = mask;
                *d = ((t >> 2) & m) + ((d[warp] >> 2) & m) * 3;
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TEMPLATE: GAMEMD 0x496E20
// RLEBlitTransLucent75ZReadWarp<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75ZReadWarp<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                                   int len, int skip, int zval,
                                                   unsigned short* zbuf,
                                                   unsigned short* abuf,
                                                   int alvl, int warp,
                                                   const signed char* zshape,
                                                   unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x4974B0
// RLEBlitTransLucent75ZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75ZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short*, int,
                       int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    unsigned short* d = static_cast<unsigned short*>(dest);
    const signed char* zs = zshape;
    const unsigned char* s = static_cast<const unsigned char*>(src);

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
        }
        else
        {
            if (zval - *zs < *z)
            {
                unsigned short t = table[c];
                unsigned short m = mask;
                *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
                *z = zval - *zs;
                zs++;
                d++;
                z++;
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

// TEMPLATE: GAMEMD 0x4975D0
// RLEBlitTransLucent75ZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75ZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                                    int len, int skip, int zval,
                                                    unsigned short* zbuf,
                                                    unsigned short* abuf,
                                                    int alvl, int warp,
                                                    const signed char* zshape,
                                                    unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}
