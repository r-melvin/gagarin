// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Cluster r-darken-remap: RLE leaves RLEBlitTransDarken<unsigned short>,
// RLEBlitTransRemapDest<unsigned char> and RLEBlitTransRemapXlat<unsigned char>,
// each in plain / ZRead / ZReadWrite form. Retail RTTI names carry the pixel
// type, so each is a class template with a single instantiation.
//
// Sizes (allocation sites in FUN_0048ebf0, `PUSH N; CALL 0x7C8E17`, then the
// inline constructor stores):
//   Darken*      PUSH 8   vptr, 16-bit mask at +4 (from word [owner+0x180])
//   RemapDest*   PUSH 8   vptr, table pointer at +4 (from [owner+0x178])
//   RemapXlat*   PUSH 0xC vptr, +4 = [owner+0x178], +8 = [owner+0x174]
#ifndef GG_MATCH_RENDER_BLITTERS_R_DARKEN_REMAP_H
#define GG_MATCH_RENDER_BLITTERS_R_DARKEN_REMAP_H

#include <stddef.h>
#include "rle_blitter.h"
#include "r_shared_zwrap.h"

// Retail RTTI-associated address point: 0x7E55A0 (identity evidence only; no table body claimed here).
template <class T>
class RLEBlitTransDarken : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    unsigned short mask;   // +0x04

    explicit RLEBlitTransDarken(unsigned short m) : mask(m) {}
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransDarken<unsigned short>) == 8);

// Retail RTTI-associated address point: 0x7E5540 (identity evidence only; no table body claimed here).
template <class T>
class RLEBlitTransDarkenZRead : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    unsigned short mask;   // +0x04

    explicit RLEBlitTransDarkenZRead(unsigned short m) : mask(m) {}
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransDarkenZRead<unsigned short>) == 8);

// Retail RTTI-associated address point: 0x7E54B0 (identity evidence only; no table body claimed here).
template <class T>
class RLEBlitTransDarkenZReadWrite : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    unsigned short mask;   // +0x04

    explicit RLEBlitTransDarkenZReadWrite(unsigned short m) : mask(m) {}
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransDarkenZReadWrite<unsigned short>) == 8);

// Retail RTTI-associated address point: 0x7E5AE0 (identity evidence only; no table body claimed here).
template <class T>
class RLEBlitTransRemapDest : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const T* table;        // +0x04

    explicit RLEBlitTransRemapDest(const T* t) : table(t) {}
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransRemapDest<unsigned char>) == 8);

// Retail RTTI-associated address point: 0x7E5AA0 (identity evidence only; no table body claimed here).
template <class T>
class RLEBlitTransRemapDestZRead : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const T* table;        // +0x04

    explicit RLEBlitTransRemapDestZRead(const T* t) : table(t) {}
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransRemapDestZRead<unsigned char>) == 8);

// Retail RTTI-associated address point: 0x7E5A60 (identity evidence only; no table body claimed here).
template <class T>
class RLEBlitTransRemapDestZReadWrite : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const T* table;        // +0x04

    explicit RLEBlitTransRemapDestZReadWrite(const T* t) : table(t) {}
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransRemapDestZReadWrite<unsigned char>) == 8);

// Retail RTTI-associated address point: 0x7E5AD0 (identity evidence only; no table body claimed here).
template <class T>
class RLEBlitTransRemapXlat : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const T* table1;       // +0x04, indexed by the source byte
    const T* table2;       // +0x08, indexed by table1's result

    RLEBlitTransRemapXlat(const T* t1, const T* t2) : table1(t1), table2(t2) {}
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransRemapXlat<unsigned char>) == 12);

// Retail RTTI-associated address point: 0x7E5A90 (identity evidence only; no table body claimed here).
template <class T>
class RLEBlitTransRemapXlatZRead : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const T* table1;       // +0x04, indexed by the source byte
    const T* table2;       // +0x08, indexed by table1's result

    RLEBlitTransRemapXlatZRead(const T* t1, const T* t2) : table1(t1), table2(t2) {}
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransRemapXlatZRead<unsigned char>) == 12);

// Retail RTTI-associated address point: 0x7E5A50 (identity evidence only; no table body claimed here).
template <class T>
class RLEBlitTransRemapXlatZReadWrite : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);

    const T* table1;       // +0x04, indexed by the source byte
    const T* table2;       // +0x08, indexed by table1's result

    RLEBlitTransRemapXlatZReadWrite(const T* t1, const T* t2) : table1(t1), table2(t2) {}
};

GG_STATIC_ASSERT(sizeof(RLEBlitTransRemapXlatZReadWrite<unsigned char>) == 12);

// Member offsets (typedefs: VC6 rejects offsetof on a template-id inside the macro).
typedef RLEBlitTransDarken<unsigned short> RLEBlitTransDarken_Inst;
typedef RLEBlitTransDarkenZRead<unsigned short> RLEBlitTransDarkenZRead_Inst;
typedef RLEBlitTransDarkenZReadWrite<unsigned short> RLEBlitTransDarkenZReadWrite_Inst;
typedef RLEBlitTransRemapDest<unsigned char> RLEBlitTransRemapDest_Inst;
typedef RLEBlitTransRemapDestZRead<unsigned char> RLEBlitTransRemapDestZRead_Inst;
typedef RLEBlitTransRemapDestZReadWrite<unsigned char> RLEBlitTransRemapDestZReadWrite_Inst;
typedef RLEBlitTransRemapXlat<unsigned char> RLEBlitTransRemapXlat_Inst;
typedef RLEBlitTransRemapXlatZRead<unsigned char> RLEBlitTransRemapXlatZRead_Inst;
typedef RLEBlitTransRemapXlatZReadWrite<unsigned char> RLEBlitTransRemapXlatZReadWrite_Inst;
GG_STATIC_ASSERT(offsetof(RLEBlitTransDarken_Inst, mask) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransDarkenZRead_Inst, mask) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransDarkenZReadWrite_Inst, mask) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransRemapDest_Inst, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransRemapDestZRead_Inst, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransRemapDestZReadWrite_Inst, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransRemapXlat_Inst, table1) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransRemapXlat_Inst, table2) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransRemapXlatZRead_Inst, table1) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransRemapXlatZRead_Inst, table2) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransRemapXlatZReadWrite_Inst, table1) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransRemapXlatZReadWrite_Inst, table2) == 8);

#endif // GG_MATCH_RENDER_BLITTERS_R_DARKEN_REMAP_H
