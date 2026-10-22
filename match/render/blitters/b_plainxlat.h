// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// PlainXlat family leaves of Blitter: BlitPlainXlat<uc|us>, BlitPlainXlatAlpha<us>,
// BlitPlainXlatZRead<us>, BlitPlainXlatZReadWrite<us>. Every source byte is
// looked up in a T table at +4 (no transparency test). Cluster b-plainxlat.
#ifndef GG_MATCH_RENDER_BLITTERS_B_PLAINXLAT_H
#define GG_MATCH_RENDER_BLITTERS_B_PLAINXLAT_H

#include "blitter.h"
#include "r_shared_zwrap.h"

#include "b_shared_alpha.h"

// BlitPlainXlat<T>: src byte -> xlat[byte]. Construction sites pass 8 bytes to
// operator new; these methods read xlat at +4. Constructor implementation and
// complete object lifetime are outside this method-only candidate.
// VTABLE markers identify retail tables only. They are probe-only and do not
// claim production vtable or deleting-destructor emission.
// VTABLE: GAMEMD 0x7E5B70 (identity only; probe-only, no emission claim)
// VTABLE: GAMEMD 0x7E5A38 (identity only; probe-only, no emission claim)
template <class T>
class BlitPlainXlat : public Blitter
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

    BlitPlainXlat(const T* table) : xlat(table) {}
};

GG_STATIC_ASSERT(sizeof(BlitPlainXlat<unsigned char>) == 8);
GG_STATIC_ASSERT(sizeof(BlitPlainXlat<unsigned short>) == 8);

// BlitPlainXlatZRead<us>: pixel written only if zval < zbuf[i]. Construction
// sites pass 8 bytes to operator new; constructor implementation is outside
// this method-only candidate.
// VTABLE: GAMEMD 0x7E5990 (identity only; probe-only, no emission claim)
template <class T>
class BlitPlainXlatZRead : public Blitter
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

    BlitPlainXlatZRead(const T* table) : xlat(table) {}
};

GG_STATIC_ASSERT(sizeof(BlitPlainXlatZRead<unsigned short>) == 8);

// BlitPlainXlatZReadWrite<us>: as ZRead, and a passing pixel stores the low byte
// of zval into zbuf[i] (retail MOVZX r16,CL). Construction sites pass 8 bytes to
// operator new; constructor implementation is outside this method-only candidate.
// VTABLE: GAMEMD 0x7E58A0 (identity only; probe-only, no emission claim)
template <class T>
class BlitPlainXlatZReadWrite : public Blitter
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

    BlitPlainXlatZReadWrite(const T* table) : xlat(table) {}
};

GG_STATIC_ASSERT(sizeof(BlitPlainXlatZReadWrite<unsigned short>) == 8);

// BlitPlainXlatAlpha<us>: dest = xlat[ alphaRow[*abuf] | srcbyte ], alphaRow =
// alpha + (min(0xFE, (max(alvl,0)*261)>>11) << 9) bytes. Construction sites
// pass 0xC bytes to operator new; these methods read xlat at +4 and alpha at
// +8. Constructor/destructor implementations and pool ownership are outside
// this method-only candidate.
// VTABLE: GAMEMD 0x7E57F8 (identity only; probe-only, no emission claim)
template <class T>
class BlitPlainXlatAlpha : public Blitter
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

    const T* xlat;          // +0x04
    unsigned short* alpha;  // +0x08, read by the method bodies in this candidate

    // Declaration-only API shape. These lifetime entries are not implemented
    // or claimed by this method-only candidate.
    BlitPlainXlatAlpha(const T* table, void* poolArg);
    ~BlitPlainXlatAlpha();
};

// The method-only model has size 0xC, agreeing with PUSH 0xC at construction
// sites. This does not claim the complete original class lifetime or ownership.
GG_STATIC_ASSERT(sizeof(BlitPlainXlatAlpha<unsigned short>) == 12);

typedef BlitPlainXlat<unsigned char> BlitPlainXlatUC_;
typedef BlitPlainXlat<unsigned short> BlitPlainXlatUS_;
typedef BlitPlainXlatZRead<unsigned short> BlitPlainXlatZReadUS_;
typedef BlitPlainXlatZReadWrite<unsigned short> BlitPlainXlatZReadWriteUS_;
typedef BlitPlainXlatAlpha<unsigned short> BlitPlainXlatAlphaUS_;
GG_STATIC_ASSERT(offsetof(BlitPlainXlatUC_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitPlainXlatUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitPlainXlatZReadUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitPlainXlatZReadWriteUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitPlainXlatAlphaUS_, xlat) == 4);
GG_STATIC_ASSERT(offsetof(BlitPlainXlatAlphaUS_, alpha) == 8);

#endif // GG_MATCH_RENDER_BLITTERS_B_PLAINXLAT_H
