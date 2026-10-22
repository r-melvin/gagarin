// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Trans family leaves of Blitter: BlitTrans<T>, BlitTransXlat<T>,
// BlitTransRemapDest<uc>, BlitTransRemapXlat<uc>. Zero source byte (or word,
// for BlitTrans<us>) is transparent. Cluster b-trans.
#ifndef GG_MATCH_RENDER_BLITTERS_B_TRANS_H
#define GG_MATCH_RENDER_BLITTERS_B_TRANS_H

#include "blitter.h"

// VTABLE markers below record retail table identities. The subset with
// conditional production slot checks is documented in b_trans.cpp; the markers
// do not imply full six-table closure or guarantee production emission.

// BlitTrans<unsigned char>  RTTI .?AV?$BlitTrans@E@@, BlitTrans<unsigned short> .?AV?$BlitTrans@G@@
// No data fields are modeled. Retail stack construction in 0x7BBB90 and
// 0x7BBCF0 writes a vptr; complete object extent is not established here.
// VTABLE: GAMEMD 0x7F7C0C
// VTABLE: GAMEMD 0x7F7BF4
template <class T>
class BlitTrans : public Blitter
{
public:
    BlitTrans() {}
    virtual void BlitCopy(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl, int warp);
    virtual void BlitCopyTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, int warp, unsigned short tint);
    virtual void BlitMove(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl);
    virtual void BlitMoveTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, unsigned short tint);
};

// Assert the modeled empty interface size, not a complete retail-size claim.
GG_STATIC_ASSERT(sizeof(BlitTrans<unsigned char>) == 4);
GG_STATIC_ASSERT(sizeof(BlitTrans<unsigned short>) == 4);

// BlitTransXlat<T>: src byte indexed through a T table at +4.
// Allocation: PUSH 8 before operator new 0x7C8E17 (0x48EC21 <uc>, 0x48F075 <us>);
// the inline constructor stores vptr and the table pointer (loaded from
// [owner+0x174]) at +4.
// VTABLE: GAMEMD 0x7E5B58
// VTABLE: GAMEMD 0x7E5A20
template <class T>
class BlitTransXlat : public Blitter
{
public:
    virtual void BlitCopy(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl, int warp);
    virtual void BlitCopyTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, int warp, unsigned short tint);
    virtual void BlitMove(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl);
    virtual void BlitMoveTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, unsigned short tint);

    const T* xlat; // +0x04

    BlitTransXlat(const T* table) : xlat(table) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransXlat<unsigned char>) == 8);
GG_STATIC_ASSERT(sizeof(BlitTransXlat<unsigned short>) == 8);

// BlitTransRemapDest<unsigned char>: dest pixel replaced by table[dest] where
// the source byte is nonzero. Allocation PUSH 8 (0x48EC72), constructor 0x48EC89.
// VTABLE: GAMEMD 0x7E5B28
template <class T>
class BlitTransRemapDest : public Blitter
{
public:
    virtual void BlitCopy(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl, int warp);
    virtual void BlitCopyTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, int warp, unsigned short tint);
    virtual void BlitMove(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl);
    virtual void BlitMoveTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, unsigned short tint);

    const T* remap; // +0x04

    BlitTransRemapDest(const T* table) : remap(table) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransRemapDest<unsigned char>) == 8);

// BlitTransRemapXlat<unsigned char>: dest = remap[xlat[src]].
// Allocation PUSH 0xC; constructor stores [+4] xlat, [+8] remap
// (0x48ECB3 / 0x48ECB6: +4 from [owner+0x178], +8 from [owner+0x174]).
// VTABLE: GAMEMD 0x7E5B10
template <class T>
class BlitTransRemapXlat : public Blitter
{
public:
    virtual void BlitCopy(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl, int warp);
    virtual void BlitCopyTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, int warp, unsigned short tint);
    virtual void BlitMove(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl);
    virtual void BlitMoveTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, unsigned short tint);

    const T* xlat;  // +0x04
    const T* remap; // +0x08

    BlitTransRemapXlat(const T* xlat_, const T* remap_)
        : xlat(xlat_), remap(remap_) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransRemapXlat<unsigned char>) == 12);

// Member offsets (typedefs: VC6 rejects offsetof on a template-id inside the macro).
typedef BlitTransXlat<unsigned char> BlitTransXlatUC_;
typedef BlitTransXlat<unsigned short> BlitTransXlatUS_;
typedef BlitTransRemapDest<unsigned char> BlitTransRemapDestUC_;
typedef BlitTransRemapXlat<unsigned char> BlitTransRemapXlatUC_;
GG_STATIC_ASSERT(offsetof(BlitTransXlatUC_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransXlatUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransRemapDestUC_, remap) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransRemapXlatUC_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitTransRemapXlatUC_, remap) == 8);

#endif // GG_MATCH_RENDER_BLITTERS_B_TRANS_H
