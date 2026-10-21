// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M3 candidate; instructions revalidated against pinned retail gamemd.exe.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Cluster r-lucent50, families RLEBlitTransLucent50AlphaZRead / AlphaZReadWarp /
// AlphaZReadWrite <us>. No /GX. See r_lucent50.h for the layout.
//
// Spans: AlphaZRead 0x4986D0 (0x1AC), AlphaZReadWarp 0x498CD0 (0x1B1),
// AlphaZReadWrite 0x499860 (0x1E5); Tint shims 0x498880 / 0x498E90 / 0x499A50 (0x3A).
// Tint shims 100%. RLEBlit bodies are CAPPED (retail spills this/zshape/len/row into
// the argument slots under heavy register pressure, which no declaration order reached):
//   AlphaZRead      20.1%  multiset retail-only {mov:1}, ours-only {jmp:1}
//   AlphaZReadWarp  12.7%  (r_lucent75_alpha.cpp structure, Lucent50 blend)
//   AlphaZReadWrite 20.6%  (r_lucent75_alpha.cpp structure, Lucent50 blend; same as before)
// Port of the r_lucent75 closed bodies (byte-pointer atab, locals z/s/zs/d/ab/a, ab++ after
// the Z if/else, len-- in both branches): AlphaZRead 5.3% (worse, original kept), Warp 12.7%
// (kept, was 12.0%), ReadWrite 20.6% (unchanged). Hoisting the mask load to function scope
// dropped Warp to 0.0% and ReadWrite to 1.8%; m/t locals in the original Read: 20.1% unchanged.
// Retail keeps the RLE byte c and s in stack slots (mov byte [esp+2c],al) and re-reads this,
// zshape, len from the argument area (165 vs 158 instructions in ReadWrite); that spill
// pattern is the remaining delta.
// AlphaZRead with the Lucent25 AlphaZRead structure scored 5.3%, with the Lucent25
// AlphaZReadWarp structure 12.1%; both worse than the kept body.
// Tried: all 120 declaration orders of z / zs / s / d / alpha-row block (best kept, per
// function), all 24 orders of the four pointer advances in the transparent run, abuf++
// inside vs after the if/else, increments in the condition vs in the bodies, wrap helpers
// vs inline, the (unsigned char)zval store. The non-alpha Z twins reached 100% with the
// same forms (see r_lucent50_zread.cpp).
#include "r_lucent50.h"


// TEMPLATE: GAMEMD 0x4986D0
// RLEBlitTransLucent50AlphaZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50AlphaZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf, unsigned short* abuf,
                        int alvl, int, const signed char* zshape)
{
    const signed char* zs = zshape;
    unsigned short* d = static_cast<unsigned short*>(dest);

    int a = alvl > 0 ? alvl : 0;
    int idx = (a * 261) >> 11;
    if (idx > 0xFE)
        idx = 0xFE;
    const unsigned short* row = (const unsigned short*)((char*)alpha_handle + (idx << 9));

    unsigned short* z = zbuf;
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
        z = RLEZWrapRow(z + over);
        abuf = RLELucent50AlphaWrapRow(abuf + over);
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
            abuf += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = ((table[row[*abuf] | c] >> 1) & mask) + ((*d >> 1) & mask);
                len--;
                d++;
            }
            else
            {
                len--;
                d++;
            }
            abuf++;
        }
        z = RLEZWrapRow(z);
        abuf = RLELucent50AlphaWrapRow(abuf);
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
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
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
                unsigned short t = table[*reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c];
                *d = ((t >> 2) & m) + ((d[warp] >> 1) & m);
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
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
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
                unsigned short t = table[*reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c];
                *d = ((t >> 1) & m) + ((*d >> 1) & m);
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
