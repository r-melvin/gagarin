// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; M3 frozen source, full-entry spans and raw-byte verification records.
// No /GX; this is the locked M3 candidate flag set. Paired compile verification awaits root's compiler-free signal.
#include "r_xlat.h"

// TEMPLATE: GAMEMD 0x4965b0
// Span: 0xd5 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlatZRead<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransXlatZRead<T>::RLEBlit(void* dest, const void* src, int len,
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
            z += c;
            zs += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = table[c];
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

// TEMPLATE: GAMEMD 0x496690
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlatZRead<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransXlatZRead<T>::RLEBlitTint(void* dest, const void* src, int len,
                                           int skip, int zval,
                                           unsigned short* zbuf,
                                           unsigned short* abuf, int alvl,
                                           int warp, const signed char* zshape,
                                           unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

template class RLEBlitTransXlatZRead<unsigned short>;
// SYNTHETIC: GAMEMD 0x49A820
// RLEBlitTransXlatZRead<unsigned short> scalar deleting destructor
