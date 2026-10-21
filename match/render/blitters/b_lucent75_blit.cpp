// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; the retained method bodies, complete spans and field accesses were checked against the frozen M2 evidence and pinned retail image.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /GX
// Paired compile with /O2 /DNDEBUG /Gy also reproduces all retained methods; project-default /GX selected because both object sets match.
// Explicit <unsigned short> member specializations emit only the 32 ordinary methods. This TU does not claim constructors, deleting destructors, or derived vtable emission.
#include "b_lucent75_blit.h"
#include "r_shared_zwrap.h"

// FUNCTION: GAMEMD 0x492740
// BlitTransLucent75<unsigned short>::BlitCopy
template <>
void BlitTransLucent75<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c) {
                unsigned short t = xlat[c];
                unsigned short m = mask;
                *d = ((t >> 2) & m) + 3 * ((*d >> 2) & m);
            }
            ++d;
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x4927A0
// BlitTransLucent75<unsigned short>::BlitMove
template <>
void BlitTransLucent75<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4927D0
// BlitTransLucent75<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x492800
// BlitTransLucent75<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x492E10
// BlitTransLucent75ZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent75ZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
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
                    unsigned short t = xlat[c];
                    unsigned short m = mask;
                    *d = ((*d >> 2) & m) * 3 + ((t >> 2) & m);
                }
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x492EA0
// BlitTransLucent75ZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent75ZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x492ED0
// BlitTransLucent75ZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75ZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x492F00
// BlitTransLucent75ZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75ZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493170
// BlitTransLucent75ZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent75ZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int warp)
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
                    unsigned short t = xlat[c];
                    unsigned short m = mask;
                    *d = ((d[warp] >> 2) & m) * 3 + ((t >> 2) & m);
                }
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x493210
// BlitTransLucent75ZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent75ZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493240
// BlitTransLucent75ZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75ZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493270
// BlitTransLucent75ZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75ZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493930
// BlitTransLucent75ZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent75ZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short t = xlat[c];
                    unsigned short m = mask;
                    *d = ((*d >> 2) & m) * 3 + ((t >> 2) & m);
                    *z = zval;
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z + 1);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x4939D0
// BlitTransLucent75ZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent75ZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493A00
// BlitTransLucent75ZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75ZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493A30
// BlitTransLucent75ZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75ZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494080
// BlitTransLucent75Alpha<unsigned short>::BlitCopy
template <>
void BlitTransLucent75Alpha<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int alvl, int)
{
    unsigned short* a = abuf;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) {
                unsigned short m = mask;
                unsigned short t = xlat[row[*a] | c];
                *d = ((*d >> 2) & m) * 3 + ((t >> 2) & m);
            }
            ++d;
            a = BLucent75AlphaWrapRow(a + 1);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x494150
// BlitTransLucent75Alpha<unsigned short>::BlitMove
template <>
void BlitTransLucent75Alpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494180
// BlitTransLucent75Alpha<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75Alpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4941B0
// BlitTransLucent75Alpha<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75Alpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494F20
// BlitTransLucent75AlphaZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent75AlphaZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    unsigned short* a = abuf;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short m = mask;
                    unsigned short t = xlat[row[*a] | c];
                    *d = ((*d >> 2) & m) * 3 + ((t >> 2) & m);
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            a = BLucent75AlphaWrapRow(a + 1);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x495030
// BlitTransLucent75AlphaZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent75AlphaZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495060
// BlitTransLucent75AlphaZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75AlphaZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495090
// BlitTransLucent75AlphaZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75AlphaZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4953F0
// BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int warp)
{
    unsigned short* z = zbuf;
    unsigned short* a = abuf;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short m = mask;
                    unsigned short t = xlat[row[*a] | c];
                    *d = ((d[warp] >> 2) & m) * 3 + ((t >> 2) & m);
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            a = BLucent75AlphaWrapRow(a + 1);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x495500
// BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495530
// BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495560
// BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495BC0
// BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    unsigned short* a = abuf;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        int n = len;
        do {
            if (zval < *z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short m = mask;
                    unsigned short t = xlat[row[*a] | c];
                    *(unsigned short*)dest = ((*(unsigned short*)dest >> 2) & m) * 3 + ((t >> 2) & m);
                    *z = zval;
                }
            }
            src = (const unsigned char*)src + 1;
            dest = (unsigned short*)dest + 1;
            z = RLEZWrapRow(z + 1);
            a = BLucent75AlphaWrapRow(a + 1);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x495CD0
// BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495D00
// BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495D30
// BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
