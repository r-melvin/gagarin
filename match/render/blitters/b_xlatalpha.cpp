// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M2 retail-binary candidate; method spans from the pinned
// gamemd.exe v1.001 row packet. This production-only subset covers the five
// unsigned-short TransXlat alpha method families.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Twenty ordinary method specializations are ordered by retail address.
// Constructors, destructors, deleting wrappers, vtable emission and alpha-pool
// ownership are deliberately outside this method subset.
#include "b_xlatalpha.h"
#include "r_shared_zwrap.h"

// Alpha level -> row index: clamp > 0, (a * 261) >> 11, cap at 0xFE.
inline int AlphaRowIndex(int alvl)
{
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    return a;
}

// TEMPLATE: GAMEMD 0x493DF0
// BlitTransXlatAlpha<unsigned short>::BlitCopy
template <>
void BlitTransXlatAlpha<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int alvl, int)
{
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    int level = (a * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        do {
            unsigned char c = *s++;
            if (c)
                *d = xlat[row[*ab] | c];
            ++d;
            ab = BlitAlphaWrapRow(ab + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x493EA0
// BlitTransXlatAlpha<unsigned short>::BlitMove
template <>
void BlitTransXlatAlpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x493ED0
// BlitTransXlatAlpha<unsigned short>::BlitCopyTint
template <>
void BlitTransXlatAlpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x493F00
// BlitTransXlatAlpha<unsigned short>::BlitMoveTint
template <>
void BlitTransXlatAlpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494490
// BlitTransXlatWriteAlpha<unsigned short>::BlitCopy
template <>
void BlitTransXlatWriteAlpha<unsigned short>::BlitCopy(void*, const void* src, int len, int zval, unsigned short*, unsigned short* abuf, int alvl, int)
{
    unsigned short* ab = abuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c)
                *ab = (unsigned short)(zval + c < 0xFF ? zval + c : 0xFF);
            ab = BlitAlphaWrapRow(ab + 1);
        } while (--n);
    }
}

// Slots 2-4: forwarding shims (call slot 1 with warp = 0; BlitMoveTint of
// AlphaZRead calls slot 2 with tint instead).
// TEMPLATE: GAMEMD 0x494500
// BlitTransXlatWriteAlpha<unsigned short>::BlitMove
template <>
void BlitTransXlatWriteAlpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494530
// BlitTransXlatWriteAlpha<unsigned short>::BlitCopyTint
template <>
void BlitTransXlatWriteAlpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494560
// BlitTransXlatWriteAlpha<unsigned short>::BlitMoveTint
template <>
void BlitTransXlatWriteAlpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494590
// BlitTransXlatMultWriteAlpha<unsigned short>::BlitCopy
template <>
void BlitTransXlatMultWriteAlpha<unsigned short>::BlitCopy(void*, const void* src, int len, int zval, unsigned short*, unsigned short* abuf, int alvl, int)
{
    unsigned short* ab = abuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c)
                *ab = (unsigned short)(c * alvl + zval < 0xFF ? c * alvl + zval : 0xFF);
            ab = BlitAlphaWrapRow(ab + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x494600
// BlitTransXlatMultWriteAlpha<unsigned short>::BlitMove
template <>
void BlitTransXlatMultWriteAlpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494630
// BlitTransXlatMultWriteAlpha<unsigned short>::BlitCopyTint
template <>
void BlitTransXlatMultWriteAlpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494660
// BlitTransXlatMultWriteAlpha<unsigned short>::BlitMoveTint
template <>
void BlitTransXlatMultWriteAlpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494B60
// BlitTransXlatAlphaZRead<unsigned short>::BlitCopy
template <>
void BlitTransXlatAlphaZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    int level = (a * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        do {
            if (zval < *z) {
                unsigned char c = *(const unsigned char*)src;
                if (c)
                    *d = xlat[row[*ab] | c];
            }
            ++z;
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            ab = BlitAlphaWrapRow(ab + 1);
        } while (--n);
    }
}
// Tint variant is 100% (z advanced inside the compare, `*z++`, which is where retail
// bumps it). The same spelling in the plain BlitCopy at 0x494B60 keeps the instruction
// multiset identical but drops it to 57.3% by position (retail hoists the Z-wrap global
// into EBP there; the `*z++` spelling loses that hoist), so BlitCopy keeps its original form.
// TEMPLATE: GAMEMD 0x494C40
// BlitTransXlatAlphaZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransXlatAlphaZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short tint)
{
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    int level = (a * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c)
                    *d = xlat[row[*ab] | c] | tint;
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            ab = BlitAlphaWrapRow(ab + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x494D20
// BlitTransXlatAlphaZRead<unsigned short>::BlitMove
template <>
void BlitTransXlatAlphaZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494D50
// BlitTransXlatAlphaZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransXlatAlphaZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short tint)
{
    BlitCopyTint(dest, src, len, zval, zbuf, abuf, alvl, 0, tint);
}
// TEMPLATE: GAMEMD 0x4958D0
// BlitTransXlatAlphaZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransXlatAlphaZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    int level = (a * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        do {
            if (zval < *z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    *d = xlat[row[*ab] | c];
                    *z = (unsigned short)zval;
                }
            }
            ++z;
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            ab = BlitAlphaWrapRow(ab + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x4959C0
// BlitTransXlatAlphaZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransXlatAlphaZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4959F0
// BlitTransXlatAlphaZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransXlatAlphaZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x495A20
// BlitTransXlatAlphaZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransXlatAlphaZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
