// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M3 candidate; instructions revalidated against pinned retail gamemd.exe.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Cluster r-lucent50, families RLEBlitTransLucent50ZRead / ZReadWarp /
// ZReadWrite <us>. No /GX. See r_lucent50.h for the layout and
// r_shared_zwrap.h for the Z row wrap.
//
// Spans: ZRead 0x496A80 (0xFF), ZReadWarp 0x496E60 (0x104), ZReadWrite 0x497610 (0x10F);
// Tint shims 0x496B80 / 0x496F70 / 0x497720 (0x3A). All 100%.
// Levers that mattered: z / zs locals declared before s / d; the transparent run
// advances d, zs, z in that order; both branches of the depth test repeat their own
// len / d (and ReadWrite zs / z) steps instead of sharing a tail; ReadWrite re-reads
// *zs for the depth store.
#include "r_lucent50.h"

// TEMPLATE: GAMEMD 0x496A80
// RLEBlitTransLucent50ZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50ZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf, unsigned short*,
                                  int, int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
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
        z = RLEZWrapRow(z + over);
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
                *d = ((table[c] >> 1) & mask) + ((*d >> 1) & mask);
                len--;
                d++;
            }
            else
            {
                len--;
                d++;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TEMPLATE: GAMEMD 0x496B80
// RLEBlitTransLucent50ZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50ZRead<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf,
                                  unsigned short* abuf, int alvl, int warp,
                                  const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x496E60
// RLEBlitTransLucent50ZReadWarp<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50ZReadWarp<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf, unsigned short*,
                                  int, int warp, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
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
        z = RLEZWrapRow(z + over);
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
                *d = ((table[c] >> 1) & mask) + ((d[warp] >> 1) & mask);
                len--;
                d++;
            }
            else
            {
                len--;
                d++;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TEMPLATE: GAMEMD 0x496F70
// RLEBlitTransLucent50ZReadWarp<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50ZReadWarp<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf,
                                  unsigned short* abuf, int alvl, int warp,
                                  const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x497610
// RLEBlitTransLucent50ZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50ZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf, unsigned short*,
                                  int, int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
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
        z = RLEZWrapRow(z + over);
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
            if (zval - *zs < *z)
            {
                *d = ((table[c] >> 1) & mask) + ((*d >> 1) & mask);
                *z = zval - *zs;
                z++;
                zs++;
                len--;
                d++;
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

// TEMPLATE: GAMEMD 0x497720
// RLEBlitTransLucent50ZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50ZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf,
                                  unsigned short* abuf, int alvl, int warp,
                                  const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}
