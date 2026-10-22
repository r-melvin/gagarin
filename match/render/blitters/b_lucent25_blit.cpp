// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; function extents and touched fields confirmed from entry-origin disassembly.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// The same 32 methods were also exact under /O2 /DNDEBUG /Gy without /GX; use
// the project default after the flag bisection. Definitions are explicit
// <unsigned short> member specializations, sorted by retail address. No whole
// class instantiations, deleting destructors or derived vtables are emitted.
#include "b_lucent25_blit.h"
#include "r_shared_zwrap.h"

// Alpha row wrapping uses the observed pointer/byte-step fields in the global at 0x87E8A4.
inline unsigned short* BlitAlphaWrapRow(unsigned short* row)
{
    if (row >= gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}

// Blend: 3/4 of the source pixel plus 1/4 of the destination, per channel mask.
inline unsigned short Lucent25Mix(unsigned short p, unsigned short b, unsigned short m)
{
    return (unsigned short)((((p >> 2) & m) * 3) + ((b >> 2) & m));
}

// FUNCTION: GAMEMD 0x492920
// BlitTransLucent25<unsigned short>::BlitCopy
template <>
void BlitTransLucent25<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c) *d = Lucent25Mix(xlat[c], *d, mask);
            ++d;
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x492980
// BlitTransLucent25<unsigned short>::BlitMove
template <>
void BlitTransLucent25<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4929B0
// BlitTransLucent25<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4929E0
// BlitTransLucent25<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493050
// BlitTransLucent25ZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent25ZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* zp = zbuf;
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            int z = *zp++;
            if (zval < z) {
                unsigned char c = *s;
                if (c) *d = Lucent25Mix(xlat[c], *d, mask);
            }
            ++s;
            ++d;
            zp = RLEZWrapRow(zp);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x4930E0
// BlitTransLucent25ZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent25ZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493110
// BlitTransLucent25ZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25ZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493140
// BlitTransLucent25ZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25ZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4933D0
// BlitTransLucent25ZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent25ZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int warp)
{
    unsigned short* zp = zbuf;
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            int z = *zp++;
            if (zval < z) {
                unsigned char c = *s;
                if (c) *d = Lucent25Mix(xlat[c], d[warp], mask);
            }
            ++s;
            ++d;
            zp = RLEZWrapRow(zp);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x493470
// BlitTransLucent25ZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent25ZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4934A0
// BlitTransLucent25ZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25ZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4934D0
// BlitTransLucent25ZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25ZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493B90
// BlitTransLucent25ZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent25ZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* zp = zbuf;
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            int z = *zp;
            if (zval < z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    *d = Lucent25Mix(xlat[c], *d, mask);
                    *zp = (unsigned short)zval;
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            zp = RLEZWrapRow(zp + 1);
        } while (--n);
    }
}

// Alpha table row for this level: (alvl clamped to >= 0) * 261 >> 11, capped at 0xFE, 512 bytes per row.
inline int Lucent25AlphaRow(int alvl)
{
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE) a = 0xFE;
    return a << 9;
}

// FUNCTION: GAMEMD 0x493C30
// BlitTransLucent25ZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent25ZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493C60
// BlitTransLucent25ZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25ZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493C90
// BlitTransLucent25ZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25ZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494330
// BlitTransLucent25Alpha<unsigned short>::BlitCopy
template <>
void BlitTransLucent25Alpha<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int alvl, int)
{
    unsigned short* ap = abuf;
    const unsigned short* tab = (const unsigned short*)((const unsigned char*)alpha + Lucent25AlphaRow(alvl));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            const unsigned char* s = (const unsigned char*)src;
            unsigned char c = *s++;
            src = s;
            if (c) *d = Lucent25Mix(xlat[tab[*ap] | c], *d, mask);
            ++d;
            ap = BlitAlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x494400
// BlitTransLucent25Alpha<unsigned short>::BlitMove
template <>
void BlitTransLucent25Alpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494430
// BlitTransLucent25Alpha<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25Alpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494460
// BlitTransLucent25Alpha<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25Alpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495250
// BlitTransLucent25AlphaZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent25AlphaZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* zp = zbuf;
    unsigned short* ap = abuf;
    const unsigned short* tab = (const unsigned short*)((const unsigned char*)alpha + Lucent25AlphaRow(alvl));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            int z = *zp++;
            if (zval < z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) *d = Lucent25Mix(xlat[tab[*ap] | c], *d, mask);
            }
            ++d;
            src = (const unsigned char*)src + 1;
            zp = RLEZWrapRow(zp);
            ap = BlitAlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x495360
// BlitTransLucent25AlphaZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent25AlphaZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495390
// BlitTransLucent25AlphaZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25AlphaZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4953C0
// BlitTransLucent25AlphaZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25AlphaZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495730
// BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int warp)
{
    unsigned short* zp = zbuf;
    unsigned short* ap = abuf;
    const unsigned short* tab = (const unsigned short*)((const unsigned char*)alpha + Lucent25AlphaRow(alvl));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            int z = *zp++;
            if (zval < z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) *d = Lucent25Mix(xlat[tab[*ap] | c], d[warp], mask);
            }
            ++d;
            src = (const unsigned char*)src + 1;
            zp = RLEZWrapRow(zp);
            ap = BlitAlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x495840
// BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495870
// BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4958A0
// BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495F00
// BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* zp = zbuf;
    unsigned short* ap = abuf;
    const unsigned short* tab = (const unsigned short*)((const unsigned char*)alpha + Lucent25AlphaRow(alvl));
    if (len > 0) {
        int n = len;
        do {
            int z = *zp;
            if (zval < z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    *(unsigned short*)dest = Lucent25Mix(xlat[tab[*ap] | c], *(unsigned short*)dest, mask);
                    *zp = (unsigned short)zval;
                }
            }
            dest = (unsigned short*)dest + 1;
            src = (const unsigned char*)src + 1;
            zp = RLEZWrapRow(zp + 1);
            ap = BlitAlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// Slots 2-4: forwarding shims (call slot 1 with warp = 0).

// FUNCTION: GAMEMD 0x496010
// BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x496040
// BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x496070
// BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
