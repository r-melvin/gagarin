// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Cluster r-alpha (all <unsigned short>): RLEBlitTransXlatAlpha, ...ZRead, ...ZReadWrite
// and RLEBlitTransZRemapXlatAlpha, ...ZRead, ...ZReadWrite. No /GX. Layouts in r_alpha.h.
// Explicit member specializations only; this TU does not emit leaf vtables or lifetime code.
//
// The alpha level is clamped to >= 0, scaled by 261/2048, capped at 0xFE and used as
// a 512-byte row offset into the alpha-buffer table (+8, or +0xC for the ZRemap leaves); a drawn
// pixel is table[row[*abuf] | src byte] (ZRemap: the source byte goes through *remap first).
//
// CFG-closed spans (entry, length):
//   XlatAlpha            RLEBlit 0x4978C0 (0x109) slot 2 0x4979D0 (0x3A)
//   ZRemapXlatAlpha      RLEBlit 0x497A10 (0x122) slot 2 0x497B40 (0x3A)
//   XlatAlphaZRead       RLEBlit 0x497FD0 (0x17D) slot 2 0x498150 (0x182)
//   ZRemapXlatAlphaZRead RLEBlit 0x4982E0 (0x1AA) slot 2 0x498490 (0x3A)
//   XlatAlphaZReadWrite  RLEBlit 0x4990E0 (0x19F) slot 2 0x499280 (0x1A4)
//   ZRemapXlatAlphaZReadWrite RLEBlit 0x499430 (0x1D4) slot 2 0x499610 (0x3A)
//
// Slot 2 is a forwarding shim (drops tint) except for the XlatAlphaZRead and
// XlatAlphaZReadWrite leaves, where it is a full body that ORs tint into the pixel.
//
// Recipe that matched (see r_lucent25_alpha.cpp for the same family shape): skip loop
// with no byte variable; locals copied from the parameters (z, ab, zs), declared in
// retail load order; `unsigned short idx = ... | c;` as a separate local in the Z leaves;
// the alpha-row pointer built in two steps (clamp first, scale and table pointer after
// d/z/ab/zs are loaded); abuf wrapped through RLEAlphaWrapRow after every iteration.
//
// CAP 0x497A10 RLEBlitTransZRemapXlatAlpha::RLEBlit 83.2%: multiset identical (107/107),
//   the only difference is the register holding `skip` (retail EDX, loaded after the
//   alpha-row store; ours ESI, loaded before it), 18 positional diffs. Tried: every
//   declaration order of {s,d,a,row/at,ab,rm}, with and without ab/sk/n copies, idx
//   inline vs local, six spellings of the row expression, clamp and scale split in two,
//   alvl modified in place instead of a local.
//
#include "r_alpha.h"

// TEMPLATE: GAMEMD 0x4978C0
// RLEBlitTransXlatAlpha<unsigned short>::RLEBlit
template <>
void RLEBlitTransXlatAlpha<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                       int, unsigned short*, unsigned short* abuf,
                                       int alvl, int, const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    int idx = (a * 261) >> 11;
    if (idx > 0xFE)
        idx = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (idx << 9));

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
        ab += over;
        ab = RLEAlphaWrapRow(ab);
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
            *d++ = table[row[*ab] | c];
            len--;
            ab++;
        }
        ab = RLEAlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x4979D0
// RLEBlitTransXlatAlpha<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransXlatAlpha<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf,
                        unsigned short* abuf, int alvl, int warp,
                        const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x497A10
// RLEBlitTransZRemapXlatAlpha<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlatAlpha<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    const unsigned char* rm = *remap;
    unsigned short* ab = abuf;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
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
        ab = RLEAlphaWrapRow(abuf + over);
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
            unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | rm[c];
            *d++ = table[idx];
            len--;
            ab++;
        }
        ab = RLEAlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x497B40
// RLEBlitTransZRemapXlatAlpha<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatAlpha<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf,
                        unsigned short* abuf, int alvl, int warp,
                        const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x497FD0
// RLEBlitTransXlatAlphaZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransXlatAlphaZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
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
        ab = RLEAlphaWrapRow(abuf + over);
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
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d++ = table[idx];
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
        ab = RLEAlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x498150
// RLEBlitTransXlatAlphaZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransXlatAlphaZRead<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape, unsigned short tint)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
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
        ab = RLEAlphaWrapRow(abuf + over);
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
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d++ = (unsigned short)(table[idx] | tint);
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
        ab = RLEAlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x4982E0
// RLEBlitTransZRemapXlatAlphaZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlatAlphaZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    const unsigned char* rm = *remap;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
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
        ab = RLEAlphaWrapRow(abuf + over);
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
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | rm[c];
                *d++ = table[idx];
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
        ab = RLEAlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x498490
// RLEBlitTransZRemapXlatAlphaZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatAlphaZRead<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf,
                        unsigned short* abuf, int alvl, int warp,
                        const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x4990E0
// RLEBlitTransXlatAlphaZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransXlatAlphaZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
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
        ab = RLEAlphaWrapRow(abuf + over);
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
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d = table[idx];
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
        ab = RLEAlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x499280
// RLEBlitTransXlatAlphaZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransXlatAlphaZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape, unsigned short tint)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
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
        ab = RLEAlphaWrapRow(abuf + over);
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
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d = (unsigned short)(table[idx] | tint);
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
        ab = RLEAlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x499430
// RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const unsigned char* rm = *remap;
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
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
        ab = RLEAlphaWrapRow(abuf + over);
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
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | rm[c];
                *d = table[idx];
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
        ab = RLEAlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x499610
// RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf,
                        unsigned short* abuf, int alvl, int warp,
                        const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}
