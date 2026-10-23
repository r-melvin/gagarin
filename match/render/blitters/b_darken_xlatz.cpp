// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// The 20 method bodies below are entry-origin, raw-byte verified. They touch
// the documented mask/xlat fields and, for Z variants, the shared row-wrap
// global. Explicit specializations keep this TU from emitting unverified
// deleting-destructor wrappers or derived vtables.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Paired /GX and no-/GX production compiles produced identical bytes for all
// 20 functions; use the project default set.
#include "b_darken_xlatz.h"
#include "r_shared_zwrap.h"
// FUNCTION: GAMEMD 0x492670
// BlitTransDarken<unsigned short>::BlitCopy
template <>
void BlitTransDarken<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    if (len > 0) {
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) *(unsigned short*)dest = (*(unsigned short*)dest >> 1) & mask;
            dest = (unsigned short*)dest + 1;
        } while (--n);
    }
}


// FUNCTION: GAMEMD 0x4926B0
// BlitTransDarken<unsigned short>::BlitMove
template <>
void BlitTransDarken<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x4926E0
// BlitTransDarken<unsigned short>::BlitCopyTint
template <>
void BlitTransDarken<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x492710
// BlitTransDarken<unsigned short>::BlitMoveTint
template <>
void BlitTransDarken<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x492B00
// BlitTransXlatZRead<unsigned short>::BlitCopy
template <>
void BlitTransXlatZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) *(unsigned short*)dest = xlat[c];
            }
            src = (const unsigned char*)src + 1;
            dest = (unsigned short*)dest + 1;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}


// FUNCTION: GAMEMD 0x492B70
// BlitTransXlatZRead<unsigned short>::BlitMove
template <>
void BlitTransXlatZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x492BA0
// BlitTransXlatZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransXlatZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x492BD0
// BlitTransXlatZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransXlatZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x492D20
// BlitTransDarkenZRead<unsigned short>::BlitCopy
template <>
void BlitTransDarkenZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        do {
            if (zval < *z++) {
                if (*s) *d = (*d >> 1) & mask;
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}


// FUNCTION: GAMEMD 0x492D80
// BlitTransDarkenZRead<unsigned short>::BlitMove
template <>
void BlitTransDarkenZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x492DB0
// BlitTransDarkenZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransDarkenZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x492DE0
// BlitTransDarkenZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransDarkenZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x493600
// BlitTransXlatZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransXlatZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        do {
            if (zval < *z) {
                unsigned char c = *s;
                if (c) {
                    *d = xlat[c];
                    *z = zval;
                }
            }
            ++z;
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}


// FUNCTION: GAMEMD 0x493680
// BlitTransXlatZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransXlatZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x4936B0
// BlitTransXlatZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransXlatZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x4936E0
// BlitTransXlatZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransXlatZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x493830
// BlitTransDarkenZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransDarkenZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        do {
            if (zval < *z) {
                if (*s) {
                    *d = (*d >> 1) & mask;
                    *z = zval;
                }
            }
            ++z;
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}


// FUNCTION: GAMEMD 0x4938A0
// BlitTransDarkenZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransDarkenZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x4938D0
// BlitTransDarkenZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransDarkenZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}


// FUNCTION: GAMEMD 0x493900
// BlitTransDarkenZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransDarkenZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
