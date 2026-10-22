// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Production-only ordinary method subset from the frozen M3 r-darken-remap
// evidence. The nine harness deleting-destructor bodies and nine harness
// vtable bodies are deliberately excluded. Three capped RLE bodies are kept
// byte-for-byte source-identical to the frozen candidate and remain partial.
#include "r_darken_remap.h"

// TEMPLATE: GAMEMD 0x4919B0
// Span: 0x74 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDest<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapDest<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int, unsigned short*, unsigned short*, int, int,
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
            *d = table[*d];
            len--;
            d++;
        }
    }
}

// TEMPLATE: GAMEMD 0x491A30
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDest<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapDest<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x491A70
// Span: 0x88 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlat<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapXlat<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int, unsigned short*, unsigned short*, int, int,
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
            *d = table2[table1[c]];
            d++;
            len--;
        }
    }
}

// TEMPLATE: GAMEMD 0x491B00
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlat<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapXlat<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x491D90
// Span: 0xCA bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDestZRead<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapDestZRead<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
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
                *d = table[*d];
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

// TEMPLATE: GAMEMD 0x491E60
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDestZRead<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapDestZRead<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x491EA0
// Span: 0xE9 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlatZRead<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapXlatZRead<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
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
                *d = table2[table1[c]];
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

// TEMPLATE: GAMEMD 0x491F90
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlatZRead<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapXlatZRead<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x492250
// Span: 0xDD bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDestZReadWrite<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapDestZReadWrite<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
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
                *d = table[*d];
                *z = zval - *zs++;
                z++;
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

// TEMPLATE: GAMEMD 0x492330
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDestZReadWrite<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapDestZReadWrite<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x492370
// Span: 0x109 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlatZReadWrite<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapXlatZReadWrite<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
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
            if (zval - *zs < *z)
            {
                *d++ = table2[table1[c]];
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

// TEMPLATE: GAMEMD 0x492480
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlatZReadWrite<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapXlatZReadWrite<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x496250
// Span: 0x79 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarken<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransDarken<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int, unsigned short*, unsigned short*, int, int,
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
            *d = (*d >> 1) & mask;
            len--;
            d++;
        }
    }
}

// TEMPLATE: GAMEMD 0x4962D0
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarken<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransDarken<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x496820
// Span: 0xCB bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarkenZRead<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransDarkenZRead<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
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
            zs += c;
            d += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z)
                *d = (*d >> 1) & mask;
            len--;
            z++;
            d++;
        }
        z = RLEZWrapRow(z);
    }
}

// TEMPLATE: GAMEMD 0x4968F0
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarkenZRead<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransDarkenZRead<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TEMPLATE: GAMEMD 0x497390
// Span: 0xDD bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarkenZReadWrite<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransDarkenZReadWrite<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
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
            if (zval - *zs < *z)
            {
                *d = (*d >> 1) & mask;
                *z = zval - *zs++;
                z++;
                len--;
                d++;
            }
            else
            {
                zs++;
                len--;
                z++;
                d++;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TEMPLATE: GAMEMD 0x497470
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarkenZReadWrite<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransDarkenZReadWrite<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}
// Explicit instantiation emits the methods from these nine specializations.
// The production candidate rows cover only the 18 ordinary methods. VC6 also
// emits constructor/destructor and vtable symbols for these class instantiations;
// this package makes no claims for those artifacts or the harness-only rows.
template class RLEBlitTransDarken<unsigned short>;
template class RLEBlitTransDarkenZRead<unsigned short>;
template class RLEBlitTransDarkenZReadWrite<unsigned short>;
template class RLEBlitTransRemapDest<unsigned char>;
template class RLEBlitTransRemapDestZRead<unsigned char>;
template class RLEBlitTransRemapDestZReadWrite<unsigned char>;
template class RLEBlitTransRemapXlat<unsigned char>;
template class RLEBlitTransRemapXlatZRead<unsigned char>;
template class RLEBlitTransRemapXlatZReadWrite<unsigned char>;
// SYNTHETIC: GAMEMD 0x499DA0
// RLEBlitter scalar deleting destructor
// SYNTHETIC: GAMEMD 0x499DE0
// RLEBlitTransRemapDest<unsigned char> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x499E00
// RLEBlitTransRemapXlat<unsigned char> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x499E60
// RLEBlitTransRemapDestZRead<unsigned char> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x499E80
// RLEBlitTransRemapXlatZRead<unsigned char> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x499EE0
// RLEBlitTransRemapDestZReadWrite<unsigned char> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x499F00
// RLEBlitTransRemapXlatZReadWrite<unsigned char> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x49A7A0
// RLEBlitTransDarken<unsigned short> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x49A860
// RLEBlitTransDarkenZRead<unsigned short> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x49A980
// RLEBlitTransDarkenZReadWrite<unsigned short> scalar deleting destructor
