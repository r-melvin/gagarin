// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Cluster r-xlat: RLE leaves RLEBlitTransXlat, RLEBlitTransXlatZRead and
// RLEBlitTransXlatZReadWrite, each for unsigned char and unsigned short.
#ifndef GG_MATCH_RENDER_BLITTERS_R_XLAT_H
#define GG_MATCH_RENDER_BLITTERS_R_XLAT_H

#include <stddef.h>
#include "rle_blitter.h"
#include "r_shared_zwrap.h"

// RLEBlitTransXlat<T>: derives from RLEBlitter alone. Member `table` at +4 is
// the translation table, indexed by the source byte (T entries).
// Retail RTTI-associated address point 0x7E5B00 (identity evidence only; no table body claimed).
// Retail RTTI-associated address point 0x7E55C0 (identity evidence only; no table body claimed).
template <class T>
class RLEBlitTransXlat : public RLEBlitter
{
public:
    explicit RLEBlitTransXlat(const T* t) : table(t) {}

    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const T* table;   // +0x04
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransXlat<unsigned char>) == 8);
GG_STATIC_ASSERT(sizeof(RLEBlitTransXlat<unsigned short>) == 8);

// RLEBlitTransXlatZRead<T>: as RLEBlitTransXlat, plus a depth test per drawn pixel.
// Retail RTTI-associated address point 0x7E5AC0 (identity evidence only; no table body claimed).
// Retail RTTI-associated address point 0x7E5560 (identity evidence only; no table body claimed).
template <class T>
class RLEBlitTransXlatZRead : public RLEBlitter
{
public:
    explicit RLEBlitTransXlatZRead(const T* t) : table(t) {}

    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const T* table;   // +0x04
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransXlatZRead<unsigned char>) == 8);
GG_STATIC_ASSERT(sizeof(RLEBlitTransXlatZRead<unsigned short>) == 8);

// RLEBlitTransXlatZReadWrite<T>: as ZRead, and a passing pixel also writes its
// depth (zval - zshape delta) into zbuf.
// Retail RTTI-associated address point 0x7E5A80 (identity evidence only; no table body claimed).
// Retail RTTI-associated address point 0x7E54D0 (identity evidence only; no table body claimed).
template <class T>
class RLEBlitTransXlatZReadWrite : public RLEBlitter
{
public:
    explicit RLEBlitTransXlatZReadWrite(const T* t) : table(t) {}

    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const T* table;   // +0x04
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransXlatZReadWrite<unsigned char>) == 8);
GG_STATIC_ASSERT(sizeof(RLEBlitTransXlatZReadWrite<unsigned short>) == 8);

#endif // GG_MATCH_RENDER_BLITTERS_R_XLAT_H
