// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Cluster r-zremap: RLE leaves RLEBlitTransZRemapXlat, ...ZRead and
// ...ZReadWrite, each for unsigned char and unsigned short.
#ifndef GG_MATCH_RENDER_BLITTERS_R_ZREMAP_H
#define GG_MATCH_RENDER_BLITTERS_R_ZREMAP_H

#include <stddef.h>
#include "rle_blitter.h"
#include "r_shared_zwrap.h"

// Each leaf stores a pointer to a remap-table pointer at +4, then a pointer to
// the pixel table at +8. The ordinary methods touch both offsets directly; the
// declaring owner structure and its source-level field names are not asserted.
// Allocation: PUSH 0xC before operator new 0x7C8E17 at 0x48ED41 (<uc> plain),
// 0x48FB0F (<us> plain), 0x48EE4F / 0x48FC25 (ZRead), 0x48EF5D / 0x48FDD1
// (ZReadWrite); the inline constructor stores the vptr, remap (+4), table (+8),
// so sizeof is 12.

template <class T>
class RLEBlitTransZRemapXlat : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const unsigned char* const* remap;   // +0x04
    const T* table;                      // +0x08

    RLEBlitTransZRemapXlat(const unsigned char* const* r, const T* t)
        : remap(r), table(t) {}
};

typedef RLEBlitTransZRemapXlat<unsigned char> RLEBlitTransZRemapXlat_uc;
typedef RLEBlitTransZRemapXlat<unsigned short> RLEBlitTransZRemapXlat_us;
GG_STATIC_ASSERT(sizeof(RLEBlitTransZRemapXlat_uc) == 12);
GG_STATIC_ASSERT(sizeof(RLEBlitTransZRemapXlat_us) == 12);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlat_uc, remap) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlat_uc, table) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlat_us, remap) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlat_us, table) == 8);

template <class T>
class RLEBlitTransZRemapXlatZRead : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const unsigned char* const* remap;   // +0x04
    const T* table;                      // +0x08

    RLEBlitTransZRemapXlatZRead(const unsigned char* const* r, const T* t)
        : remap(r), table(t) {}
};

typedef RLEBlitTransZRemapXlatZRead<unsigned char> RLEBlitTransZRemapXlatZRead_uc;
typedef RLEBlitTransZRemapXlatZRead<unsigned short> RLEBlitTransZRemapXlatZRead_us;
GG_STATIC_ASSERT(sizeof(RLEBlitTransZRemapXlatZRead_uc) == 12);
GG_STATIC_ASSERT(sizeof(RLEBlitTransZRemapXlatZRead_us) == 12);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatZRead_uc, remap) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatZRead_uc, table) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatZRead_us, remap) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatZRead_us, table) == 8);

template <class T>
class RLEBlitTransZRemapXlatZReadWrite : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const unsigned char* const* remap;   // +0x04
    const T* table;                      // +0x08

    RLEBlitTransZRemapXlatZReadWrite(const unsigned char* const* r, const T* t)
        : remap(r), table(t) {}
};

typedef RLEBlitTransZRemapXlatZReadWrite<unsigned char> RLEBlitTransZRemapXlatZReadWrite_uc;
typedef RLEBlitTransZRemapXlatZReadWrite<unsigned short> RLEBlitTransZRemapXlatZReadWrite_us;
GG_STATIC_ASSERT(sizeof(RLEBlitTransZRemapXlatZReadWrite_uc) == 12);
GG_STATIC_ASSERT(sizeof(RLEBlitTransZRemapXlatZReadWrite_us) == 12);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatZReadWrite_uc, remap) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatZReadWrite_uc, table) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatZReadWrite_us, remap) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatZReadWrite_us, table) == 8);

#endif // GG_MATCH_RENDER_BLITTERS_R_ZREMAP_H
