// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Source facts: frozen milestone 3 production-only r-lucent25 reconstruction;
// every body below is tied to its retail entry and full CFG-closed span by the
// corresponding TEMPLATE marker. No pool ownership, constructor/destructor,
// deleting-destructor, or leaf-vtable body is emitted by this translation unit.
#include "r_lucent25.h"

// TEMPLATE: GAMEMD 0x4964D0
// Span: 0x9F bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25<T>::RLEBlit(void* dest, const void* src, int len,
                                      int skip, int, unsigned short*,
                                      unsigned short*, int, int,
                                      const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
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
            *d = 3 * ((palette[c] >> 2) & mask) + ((*d >> 2) & mask);
            d++;
            len--;
        }
    }
}

// TEMPLATE: GAMEMD 0x496570
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25<T>::RLEBlitTint(void* dest, const void* src, int len,
                                          int skip, int zval,
                                          unsigned short* zbuf,
                                          unsigned short* abuf, int alvl,
                                          int warp, const signed char* zshape,
                                          unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x496BC0
// Span: 0x106 bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZRead<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25ZRead<T>::RLEBlit(void* dest, const void* src, int len,
                                           int skip, int zval,
                                           unsigned short* zbuf,
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
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = 3 * ((palette[c] >> 2) & mask) + ((*d >> 2) & mask);
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

// TEMPLATE: GAMEMD 0x496CD0
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZRead<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25ZRead<T>::RLEBlitTint(void* dest, const void* src,
                                               int len, int skip, int zval,
                                               unsigned short* zbuf,
                                               unsigned short* abuf, int alvl,
                                               int warp,
                                               const signed char* zshape,
                                               unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x496FB0
// Span: 0x10B bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZReadWarp<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25ZReadWarp<T>::RLEBlit(void* dest, const void* src,
                                               int len, int skip, int zval,
                                               unsigned short* zbuf,
                                               unsigned short*, int, int warp,
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
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = 3 * ((palette[c] >> 2) & mask) + ((d[warp] >> 2) & mask);
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

// TEMPLATE: GAMEMD 0x4970C0
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZReadWarp<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25ZReadWarp<T>::RLEBlitTint(void* dest, const void* src,
                                                   int len, int skip, int zval,
                                                   unsigned short* zbuf,
                                                   unsigned short* abuf,
                                                   int alvl, int warp,
                                                   const signed char* zshape,
                                                   unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x497760
// Span: 0x116 bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZReadWrite<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25ZReadWrite<T>::RLEBlit(void* dest, const void* src,
                                                int len, int skip, int zval,
                                                unsigned short* zbuf,
                                                unsigned short*, int, int,
                                                const signed char* zshape)
{
    unsigned short* z = zbuf;
    T* d = static_cast<T*>(dest);
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
                *d = 3 * ((palette[c] >> 2) & mask) + ((*d >> 2) & mask);
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

// TEMPLATE: GAMEMD 0x497880
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZReadWrite<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25ZReadWrite<T>::RLEBlitTint(void* dest, const void* src,
                                                    int len, int skip, int zval,
                                                    unsigned short* zbuf,
                                                    unsigned short* abuf,
                                                    int alvl, int warp,
                                                    const signed char* zshape,
                                                    unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// RLEBlitTransLucent25Alpha<unsigned short>::`scalar deleting destructor'
// RLEBlitTransLucent25AlphaZRead<unsigned short>::`scalar deleting destructor'
// RLEBlitTransLucent25AlphaZReadWarp<unsigned short>::`scalar deleting destructor'
// RLEBlitTransLucent25AlphaZReadWrite<unsigned short>::`scalar deleting destructor'

// TEMPLATE: GAMEMD 0x497E60
// Span: 0x12D bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25Alpha<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25Alpha<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                                      int, unsigned short*, unsigned short* abuf, int alvl, int,
                                      const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha_tab) + (a << 9);

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
        ab = RLEL25AlphaWrapRow(abuf + over);
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
            unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
            *d = 3 * ((palette[idx] >> 2) & mask) + ((*d >> 2) & mask);
            d++;
            len--;
            ab++;
        }
        ab = RLEL25AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x497F90
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25Alpha<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25Alpha<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf,
                                      unsigned short* abuf, int alvl, int warp,
                                      const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x4988C0
// Span: 0x1BB bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZRead<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25AlphaZRead<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf, unsigned short* abuf,
                                      int alvl, int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha_tab) + (a << 9);

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
        ab = RLEL25AlphaWrapRow(abuf + over);
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
                *d = 3 * ((palette[idx] >> 2) & mask) + ((*d >> 2) & mask);
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
        ab = RLEL25AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x498A80
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZRead<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25AlphaZRead<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf,
                                      unsigned short* abuf, int alvl, int warp,
                                      const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x498ED0
// Span: 0x1C6 bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZReadWarp<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25AlphaZReadWarp<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf, unsigned short* abuf,
                                      int alvl, int warp, const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha_tab) + (a << 9);

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
        ab = RLEL25AlphaWrapRow(abuf + over);
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
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d = 3 * ((palette[idx] >> 2) & mask) + ((d[warp] >> 2) & mask);
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
        ab = RLEL25AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x4990A0
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZReadWarp<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25AlphaZReadWarp<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf,
                                      unsigned short* abuf, int alvl, int warp,
                                      const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x499A90
// Span: 0x1C9 bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZReadWrite<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25AlphaZReadWrite<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf, unsigned short* abuf,
                                      int alvl, int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha_tab) + (a << 9);

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
        ab = RLEL25AlphaWrapRow(abuf + over);
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
                *d = 3 * ((palette[idx] >> 2) & mask) + ((*d >> 2) & mask);
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
        ab = RLEL25AlphaWrapRow(ab);
    }
}

// TEMPLATE: GAMEMD 0x499C60
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZReadWrite<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25AlphaZReadWrite<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf,
                                      unsigned short* abuf, int alvl, int warp,
                                      const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// Explicitly instantiate the eight leaf specializations. VC6 emits their
// ordinary virtual methods from these declarations.
template class RLEBlitTransLucent25<unsigned short>;
template class RLEBlitTransLucent25ZRead<unsigned short>;
template class RLEBlitTransLucent25ZReadWarp<unsigned short>;
template class RLEBlitTransLucent25ZReadWrite<unsigned short>;
template class RLEBlitTransLucent25Alpha<unsigned short>;
template class RLEBlitTransLucent25AlphaZRead<unsigned short>;
template class RLEBlitTransLucent25AlphaZReadWarp<unsigned short>;
template class RLEBlitTransLucent25AlphaZReadWrite<unsigned short>;
