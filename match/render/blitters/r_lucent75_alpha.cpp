// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M3 r-lucent75 method packet, SHA-verified; method spans
// are checked against pinned gamemd.exe v1.001. This TU contains only the
// explicit unsigned-short RLE leaf method specializations below. It does not
// claim constructors, deleting destructors, alpha-pool ownership or vtable emission.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
#include "r_lucent75.h"

// TEMPLATE: GAMEMD 0x497B80
// RLEBlitTransLucent75Alpha<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75Alpha<unsigned short>::RLEBlit(void* dest, const void* src, int len,
                                           int skip, int, unsigned short*,
                                           unsigned short* abuf, int alvl, int,
                                           const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* ap = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    unsigned short* ar = (unsigned short*)((unsigned char*)rows + (a << 9));

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
        ap = RLELucent75AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            ap += c;
        }
        else
        {
            unsigned short m = mask;
            unsigned short t = table[ar[*ap] | c];
            *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
            d++;
            len--;
            ap++;
        }
        ap = RLELucent75AlphaWrapRow(ap);
    }
}

// TEMPLATE: GAMEMD 0x497CB0
// RLEBlitTransLucent75Alpha<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75Alpha<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                               int len, int skip, int zval,
                                               unsigned short* zbuf,
                                               unsigned short* abuf, int alvl,
                                               int warp,
                                               const signed char* zshape,
                                               unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x4984D0
// RLEBlitTransLucent75AlphaZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75AlphaZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short* abuf, int alvl,
                       int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(rows) + (a << 9);

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
        ab = RLELucent75AlphaWrapRow(abuf + over);
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
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short m = mask;
                unsigned short t = table[*reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c];
                *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent75AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x498690
// RLEBlitTransLucent75AlphaZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75AlphaZRead<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                           int zval, unsigned short* zbuf, unsigned short* abuf,
                           int alvl, int warp, const signed char* zshape,
                           unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x498AC0
// RLEBlitTransLucent75AlphaZReadWarp<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75AlphaZReadWarp<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short* abuf, int alvl,
                       int warp, const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(rows) + (a << 9);

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
        ab = RLELucent75AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            zs += c;
            z += c;
            d += c;
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short m = mask;
                unsigned short t = table[*reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c];
                *d = ((t >> 2) & m) + ((d[warp] >> 2) & m) * 3;
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent75AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x498C90
// RLEBlitTransLucent75AlphaZReadWarp<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75AlphaZReadWarp<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                           int zval, unsigned short* zbuf, unsigned short* abuf,
                           int alvl, int warp, const signed char* zshape,
                           unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x499650
// RLEBlitTransLucent75AlphaZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75AlphaZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short* abuf, int alvl,
                       int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(rows) + (a << 9);

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
        ab = RLELucent75AlphaWrapRow(abuf + over);
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
            ab += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                unsigned short m = mask;
                unsigned short t = table[*reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c];
                *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
                *z = zval - *zs;
                d++;
                zs++;
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
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent75AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x499820
// RLEBlitTransLucent75AlphaZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75AlphaZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                           int zval, unsigned short* zbuf, unsigned short* abuf,
                           int alvl, int warp, const signed char* zshape,
                           unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}
