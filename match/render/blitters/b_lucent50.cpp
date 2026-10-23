// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; frozen milestone-2 b-lucent50 method bodies.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Method-only source subset for the eight BlitTransLucent50 leaves, unsigned short only.
// The 32 methods are in ascending retail-address order. This source does not claim
// constructors, deleting destructors, vtables, or alpha-pool ownership.
// PARTIAL: 0x492830 remains the frozen readable body; it is not rewritten here.
// Its frozen check reports 0.0% by diff_retail instruction count (32 emitted vs 40 retail).
#include "b_lucent50.h"
#include "r_shared_zwrap.h"

// Alpha row wrap: same shape as the Z row wrap, against the block at 0x87E8A4
// (b_shared_alpha.h).
static inline unsigned short* AlphaWrapRow(unsigned short* row)
{
    if (row >= gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}

// Alpha level -> row index: clamp > 0, (a * 261) >> 11, cap at 0xFE.
static inline int AlphaRowIndex(int alvl)
{
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    return a;
}


// TEMPLATE: GAMEMD 0x492830
// BlitTransLucent50<unsigned short>::BlitCopy
template <>
void BlitTransLucent50<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    const unsigned short* table = xlat;
    unsigned m = mask;
    const unsigned char* s = (const unsigned char*)src;
    unsigned short* d = (unsigned short*)dest;
    do {
        unsigned c = *s;
        if (c) {
            unsigned a = table[c] >> 1;
            unsigned b = *d >> 1;
            *d = (unsigned short)((a & m) + (b & m));
        }
        ++s;
        ++d;
    } while (--len > 0);
}
// TEMPLATE: GAMEMD 0x492890
// BlitTransLucent50<unsigned short>::BlitMove
template <>
void BlitTransLucent50<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4928C0
// BlitTransLucent50<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4928F0
// BlitTransLucent50<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x492F30
// BlitTransLucent50ZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent50ZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *s;
                if (c) {
                    unsigned short a = xlat[c] >> 1;
                    unsigned short b = *d >> 1;
                    *d = (a & mask) + (b & mask);
                }
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x492FC0
// BlitTransLucent50ZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent50ZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x492FF0
// BlitTransLucent50ZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50ZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x493020
// BlitTransLucent50ZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50ZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4932A0
// BlitTransLucent50ZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent50ZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int warp)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *s;
                if (c) {
                    unsigned short a = xlat[c] >> 1;
                    unsigned short b = d[warp] >> 1;
                    *d = (a & mask) + (b & mask);
                }
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x493340
// BlitTransLucent50ZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent50ZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x493370
// BlitTransLucent50ZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50ZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4933A0
// BlitTransLucent50ZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50ZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x493A60
// BlitTransLucent50ZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent50ZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z) {
                unsigned char c = *s;
                if (c) {
                    unsigned short a = xlat[c] >> 1;
                    unsigned short b = *d >> 1;
                    *d = (a & mask) + (b & mask);
                    *z = (unsigned short)zval;
                }
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x493B00
// BlitTransLucent50ZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent50ZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x493B30
// BlitTransLucent50ZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50ZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x493B60
// BlitTransLucent50ZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50ZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4941E0
// BlitTransLucent50Alpha<unsigned short>::BlitCopy
template <>
void BlitTransLucent50Alpha<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int alvl, int)
{
    unsigned short* ap = abuf;
    const BlitAlphaRow256* row = alpha + AlphaRowIndex(alvl);
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) {
                unsigned short a = xlat[row->v[*ap] | c] >> 1;
                unsigned short b = *d >> 1;
                *d = (a & mask) + (b & mask);
            }
            ++d;
            ap = AlphaWrapRow(ap + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x4942A0
// BlitTransLucent50Alpha<unsigned short>::BlitMove
template <>
void BlitTransLucent50Alpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4942D0
// BlitTransLucent50Alpha<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50Alpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x494300
// BlitTransLucent50Alpha<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50Alpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4950C0
// BlitTransLucent50AlphaZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent50AlphaZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    unsigned short* ap = abuf;
    const BlitAlphaRow256* row = alpha + AlphaRowIndex(alvl);
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short a = xlat[row->v[*ap] | c] >> 1;
                    unsigned short b = *d >> 1;
                    *d = (a & mask) + (b & mask);
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            ap = AlphaWrapRow(ap + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x4951C0
// BlitTransLucent50AlphaZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent50AlphaZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4951F0
// BlitTransLucent50AlphaZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50AlphaZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x495220
// BlitTransLucent50AlphaZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50AlphaZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x495590
// BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int warp)
{
    unsigned short* z = zbuf;
    unsigned short* ap = abuf;
    const BlitAlphaRow256* row = alpha + AlphaRowIndex(alvl);
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short a = xlat[row->v[*ap] | c] >> 1;
                    unsigned short b = d[warp] >> 1;
                    *d = (a & mask) + (b & mask);
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            ap = AlphaWrapRow(ap + 1);
        } while (--n);
    }
}
// TEMPLATE: GAMEMD 0x4956A0
// BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x4956D0
// BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x495700
// BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x495D60
// BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    unsigned short* ap = abuf;
    const BlitAlphaRow256* row = alpha + AlphaRowIndex(alvl);
    if (len > 0) {
        int n = len;
        do {
            if (zval < *z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short a = xlat[row->v[*ap] | c] >> 1;
                    unsigned short b = *(unsigned short*)dest >> 1;
                    *(unsigned short*)dest = (a & mask) + (b & mask);
                    *z = (unsigned short)zval;
                }
            }
            src = (const unsigned char*)src + 1;
            dest = (unsigned short*)dest + 1;
            z = RLEZWrapRow(z + 1);
            ap = AlphaWrapRow(ap + 1);
        } while (--n);
    }
}


// Slots 2-4: forwarding shims (call slot 1 with warp = 0), one group per class.
// TEMPLATE: GAMEMD 0x495E70
// BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x495EA0
// BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
// TEMPLATE: GAMEMD 0x495ED0
// BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
