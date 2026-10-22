// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; M3 frozen source, full-entry spans and raw-byte verification records.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// No /GX; this is the locked M3 candidate flag set. Paired compile verification awaits root's compiler-free signal.
#include "r_xlat.h"

// TEMPLATE: GAMEMD 0x497100
// Span: 0xe8 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlatZReadWrite<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransXlatZReadWrite<T>::RLEBlit(void* dest, const void* src, int len,
                                       int skip, int zval, unsigned short* zbuf,
                                       unsigned short*, int, int,
                                       const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);

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
                *d++ = table[c];
                *z = zval - *zs;
                z++;
                zs++;
                len--;
            }
            else
            {
                d++;
                z++;
                zs++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TEMPLATE: GAMEMD 0x4971f0
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlatZReadWrite<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransXlatZReadWrite<T>::RLEBlitTint(void* dest, const void* src, int len,
                                           int skip, int zval,
                                           unsigned short* zbuf,
                                           unsigned short* abuf, int alvl,
                                           int warp, const signed char* zshape,
                                           unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

template class RLEBlitTransXlatZReadWrite<unsigned short>;
