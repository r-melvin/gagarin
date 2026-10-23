// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M3 candidate; instructions revalidated against pinned retail gamemd.exe.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Cluster r-lucent50, families RLEBlitTransLucent50AlphaZRead / AlphaZReadWarp /
// AlphaZReadWrite <us>. No /GX. See r_lucent50.h for the layout.
//
// Spans: AlphaZRead 0x4986D0 (0x1AC), AlphaZReadWarp 0x498CD0 (0x1B1),
// AlphaZReadWrite 0x499860 (0x1E5); Tint shims 0x498880 / 0x498E90 / 0x499A50 (0x3A).
// Tint shims 100%. RLEBlit bodies:
//   AlphaZReadWrite 0x499860  MATCHED: the skip loop reads the RLE byte into a
//                   named local, the Z store is `*z++ = zval - *zs++`, and len-- comes
//                   before d++ in the drawn arm. The previous section was 5 bytes short.
//   AlphaZRead      0x4986D0  PARTIAL 22.8% (was 20.1%); multiset retail-only {lea},
//                   ours-only {add}.
//   AlphaZReadWarp  0x498CD0  PARTIAL 22.7% (was 12.7%). Correction: the translucent
//                   term is `t >> 1` (retail `SHR AX,1` at 0x498E1F), not `>> 2`.
// All three index the alpha row as `row[*ab]` (a `unsigned short*` into the table);
// an earlier byte-pointer form with a reinterpret_cast scored the same and is gone.
// Remaining delta in the two partials: retail keeps the RLE byte c and s in stack
// slots and re-reads this, zshape and len from the argument area under register
// pressure; no declaration order reached it (all 120 orders of z / zs / s / d /
// alpha-row block were tried earlier, plus the advance orders and wrap forms).
#include "r_lucent50.h"


// TEMPLATE: GAMEMD 0x4986D0
// RLEBlitTransLucent50AlphaZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50AlphaZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf, unsigned short* abuf,
                        int alvl, int, const signed char* zshape)
{
    const signed char* zs = zshape;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned short* row = (const unsigned short*)((char*)alpha_handle + (a << 9));

    if (skip > 0)
    {
        while (skip > 0)
        {
            unsigned char r = *s++;
            if (r == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLELucent50AlphaWrapRow(abuf + over);
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
                unsigned short t = table[row[*ab] | c];
                *d = ((t >> 1) & m) + ((*d >> 1) & m);
                len--;
                d++;
            }
            else
            {
                len--;
                d++;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent50AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x498880
// RLEBlitTransLucent50AlphaZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50AlphaZRead<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                            int zval, unsigned short* zbuf,
                            unsigned short* abuf, int alvl, int warp,
                            const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x498CD0
// RLEBlitTransLucent50AlphaZReadWarp<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50AlphaZReadWarp<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short* abuf, int alvl,
                       int warp, const signed char* zshape)
{
    const signed char* zs = zshape;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned short* row = (const unsigned short*)((char*)alpha_handle + (a << 9));

    if (skip > 0)
    {
        while (skip > 0)
        {
            unsigned char r = *s++;
            if (r == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLELucent50AlphaWrapRow(abuf + over);
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
                unsigned short t = table[row[*ab] | c];
                *d = ((t >> 1) & m) + ((d[warp] >> 1) & m);
                len--;
                d++;
            }
            else
            {
                len--;
                d++;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent50AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x498E90
// RLEBlitTransLucent50AlphaZReadWarp<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50AlphaZReadWarp<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                            int zval, unsigned short* zbuf,
                            unsigned short* abuf, int alvl, int warp,
                            const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x499860
// RLEBlitTransLucent50AlphaZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50AlphaZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short* abuf, int alvl,
                       int, const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    const signed char* zs = zshape;
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned short* row = (const unsigned short*)((char*)alpha_handle + (a << 9));

    if (skip > 0)
    {
        while (skip > 0)
        {
            unsigned char r = *s++;
            if (r == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
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
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                unsigned short m = mask;
                unsigned short t = table[row[*ab] | c];
                *d = ((t >> 1) & m) + ((*d >> 1) & m);
                *z++ = zval - *zs++;
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
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent50AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x499A50
// RLEBlitTransLucent50AlphaZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50AlphaZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                            int zval, unsigned short* zbuf,
                            unsigned short* abuf, int alvl, int warp,
                            const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}
