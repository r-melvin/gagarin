// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; generic method bodies from the frozen
// b-trans reconstruction. Instantiated addresses are annotated in b_trans.cpp.
#ifndef GG_MATCH_RENDER_BLITTERS_B_TRANS_IMPL_H
#define GG_MATCH_RENDER_BLITTERS_B_TRANS_IMPL_H
#include "b_trans.h"

// BlitTrans<unsigned char>::BlitCopy
// BlitTrans<unsigned short>::BlitCopy
template <class T>
void BlitTrans<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    if (len > 0) {
        const T* s = (const T*)src;
        T* d = (T*)dest;
        int n = len;
        do {
            T c = *s++;
            if (c) *d = c;
            ++d;
        } while (--n);
    }
}

// BlitTransXlat<unsigned short>::BlitCopy
// BlitTransXlat<unsigned char>::BlitCopy
template <class T>
void BlitTransXlat<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    if (len > 0) {
        T* d = (T*)dest;
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c) *d = xlat[c];
            ++d;
        } while (--n);
    }
}

// BlitTransRemapDest<unsigned char>::BlitCopy
template <class T>
void BlitTransRemapDest<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    if (len > 0) {
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) *(T*)dest = remap[*(T*)dest];
            dest = (T*)dest + 1;
        } while (--n);
    }
}

// BlitTransRemapXlat<unsigned char>::BlitCopy
template <class T>
void BlitTransRemapXlat<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    if (len > 0) {
        T* d = (T*)dest;
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c) *d = remap[xlat[c]];
            ++d;
        } while (--n);
    }
}

// Slots 2-4: forwarding shims, one TEMPLATE group per class.


// BlitTrans<unsigned char>::BlitCopyTint
// BlitTrans<unsigned short>::BlitCopyTint
template <class T>
void BlitTrans<T>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTrans<unsigned char>::BlitMove
// BlitTrans<unsigned short>::BlitMove
template <class T>
void BlitTrans<T>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTrans<unsigned char>::BlitMoveTint
// BlitTrans<unsigned short>::BlitMoveTint
template <class T>
void BlitTrans<T>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTransXlat<unsigned short>::BlitCopyTint
// BlitTransXlat<unsigned char>::BlitCopyTint
template <class T>
void BlitTransXlat<T>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTransXlat<unsigned short>::BlitMove
// BlitTransXlat<unsigned char>::BlitMove
template <class T>
void BlitTransXlat<T>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTransXlat<unsigned short>::BlitMoveTint
// BlitTransXlat<unsigned char>::BlitMoveTint
template <class T>
void BlitTransXlat<T>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTransRemapDest<unsigned char>::BlitCopyTint
template <class T>
void BlitTransRemapDest<T>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTransRemapDest<unsigned char>::BlitMove
template <class T>
void BlitTransRemapDest<T>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTransRemapDest<unsigned char>::BlitMoveTint
template <class T>
void BlitTransRemapDest<T>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTransRemapXlat<unsigned char>::BlitCopyTint
template <class T>
void BlitTransRemapXlat<T>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTransRemapXlat<unsigned char>::BlitMove
template <class T>
void BlitTransRemapXlat<T>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// BlitTransRemapXlat<unsigned char>::BlitMoveTint
template <class T>
void BlitTransRemapXlat<T>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


#endif
