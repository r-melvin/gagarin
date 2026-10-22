// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001, SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// Production-only explicit member-function specializations. Constructor,
// destructor, derived vtable, harness table, and alpha-pool bodies are excluded.
#include "b_zremap.h"
#include "b_xlatalpha.h"   // BlitAlphaWrapRow
#include "r_shared_zwrap.h"

// FUNCTION: GAMEMD 0x491590
// Provenance: retail entry 0x491590, full span 0x47 bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlat<unsigned char>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    const unsigned char* table = *xlat;
    if (len > 0) {
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) *(unsigned char*)dest = remap[table[c]];
            dest = (unsigned char*)dest + 1;
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x4915E0
// Provenance: retail entry 0x4915E0, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlat<unsigned char>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x491610
// Provenance: retail entry 0x491610, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlat<unsigned char>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x491640
// Provenance: retail entry 0x491640, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlat<unsigned char>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x492590
// Provenance: retail entry 0x492590, full span 0x4B bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlat<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    const unsigned char* table = *xlat;
    if (len > 0) {
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) *(unsigned short*)dest = remap[table[c]];
            dest = (unsigned short*)dest + 1;
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x4925E0
// Provenance: retail entry 0x4925E0, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlat<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x492610
// Provenance: retail entry 0x492610, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlat<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x492640
// Provenance: retail entry 0x492640, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlat<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x492C00
// Provenance: retail entry 0x492C00, full span 0x8C bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    const unsigned char* table = *xlat;
    if (len > 0) {
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) *(unsigned short*)dest = remap[table[c]];
            }
            src = (const unsigned char*)src + 1;
            dest = (unsigned short*)dest + 1;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x492C90
// Provenance: retail entry 0x492C90, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x492CC0
// Provenance: retail entry 0x492CC0, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x492CF0
// Provenance: retail entry 0x492CF0, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493710
// Provenance: retail entry 0x493710, full span 0x8D bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    const unsigned char* table = *xlat;
    if (len > 0) {
        int n = len;
        do {
            if (zval < *z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    *(unsigned short*)dest = remap[table[c]];
                    *z = (unsigned short)zval;
                }
            }
            ++z;
            src = (const unsigned char*)src + 1;
            dest = (unsigned short*)dest + 1;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x4937A0
// Provenance: retail entry 0x4937A0, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x4937D0
// Provenance: retail entry 0x4937D0, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493800
// Provenance: retail entry 0x493800, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x493F30
// Provenance: retail entry 0x493F30, full span 0xBA bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlpha<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    const unsigned char* table = *xlat;
    unsigned short* ab = abuf;
    alvl = alvl > 0 ? alvl : 0;
    alvl = (alvl * 261) >> 11;
    if (alvl > 0xFE) alvl = 0xFE;
    const unsigned short* row = alpha + (alvl << 8);
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) *d = remap[row[*ab] | table[c]];
            ++d;
            ++ab;
            if (ab >= gg_blit_alpha_wrap_global->wrap_end)
                ab = (unsigned short*)((unsigned char*)ab - gg_blit_alpha_wrap_global->wrap_step);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x493FF0
// Provenance: retail entry 0x493FF0, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494020
// Provenance: retail entry 0x494020, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494050
// Provenance: retail entry 0x494050, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494D90
// Provenance: retail entry 0x494D90, full span 0xF8 bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlphaZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len,
                                                             int zval, unsigned short* zbuf,
                                                             unsigned short* abuf, int alvl, int)
{
    unsigned short* zb = zbuf;
    unsigned short* ab = abuf;
    const unsigned char* table = *xlat;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 254)
        level = 254;
    unsigned short* row = alpha + (level << 8);
    if (len > 0) {
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        do {
            if (zval < *zb++) {
                unsigned char c = *(const unsigned char*)src;
                if (c != 0) {
                    unsigned int a = *ab;
                    *d = remap[row[a] | table[c]];
                }
            }
            src = (const unsigned char*)src + 1;
            d++;
            zb = RLEZWrapRow(zb);
            ab++;
            ab = BlitAlphaWrapRow(ab);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x494E90
// Provenance: retail entry 0x494E90, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlphaZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494EC0
// Provenance: retail entry 0x494EC0, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlphaZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x494EF0
// Provenance: retail entry 0x494EF0, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlphaZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495A50
// Provenance: retail entry 0x495A50, full span 0xDA bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlphaZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    alvl = alvl > 0 ? alvl : 0;
    alvl = (alvl * 261) >> 11;
    if (alvl > 0xFE) alvl = 0xFE;
    const unsigned short* row = alpha + (alvl << 8);
    const unsigned char* table = *xlat;
    if (len > 0) {
        int n = len;
        do {
            if (zval < *z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    *(unsigned short*)dest = remap[row[*abuf] | table[c]];
                    *z = (unsigned short)zval;
                }
            }
            ++z;
            src = (const unsigned char*)src + 1;
            dest = (unsigned short*)dest + 1;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// FUNCTION: GAMEMD 0x495B30
// Provenance: retail entry 0x495B30, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlphaZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495B60
// Provenance: retail entry 0x495B60, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlphaZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// FUNCTION: GAMEMD 0x495B90
// Provenance: retail entry 0x495B90, full span 0x2d bytes; reviewed frozen M2 body against pinned v1.001 PE.
template <>
void BlitTransZRemapXlatAlphaZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}
