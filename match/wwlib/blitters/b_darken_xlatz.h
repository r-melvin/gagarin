// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256 | YRpp-cross-check
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c. RTTI,
// constructor stores and allocation sizes confirmed from the pinned PE.
// Cluster b-darken-xlatz: these five layouts are used only as unsigned-short
// specializations in b_darken_xlatz.cpp. Retail allocation paths pass 8 bytes
// to operator new; the constructors store the mask/xlat pointer at +4. The
// derived table addresses below identify retail address points; this header
// does not cause this TU to emit or claim matched derived vtables.
#ifndef GG_MATCH_RENDER_BLITTERS_B_DARKEN_XLATZ_H
#define GG_MATCH_RENDER_BLITTERS_B_DARKEN_XLATZ_H

#include <stddef.h>
#include "blitter.h"

// BlitTransDarken<unsigned short>. Allocation PUSH 8 at 0x48F0C6 / vptr 0x48F0DE; the inline
// constructor loads [owner+0x180] and stores it at +4.
// VTABLE: GAMEMD 0x7E59F0 -- retail identity only; not emitted by this TU.
template <class T>
class BlitTransDarken : public Blitter
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

    T mask; // +0x04

    BlitTransDarken(T value) : mask(value) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransDarken<unsigned short>) == 8);

// BlitTransDarkenZRead<unsigned short>. Allocation PUSH 8 at 0x48F1EE / vptr 0x48F206; the inline
// constructor loads [owner+0x180] and stores it at +4.
// VTABLE: GAMEMD 0x7E5948 -- retail identity only; not emitted by this TU.
template <class T>
class BlitTransDarkenZRead : public Blitter
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

    T mask; // +0x04

    BlitTransDarkenZRead(T value) : mask(value) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransDarkenZRead<unsigned short>) == 8);

// BlitTransDarkenZReadWrite<unsigned short>. Allocation PUSH 8 at 0x48F3A3 / vptr 0x48F3BB; the inline
// constructor loads [owner+0x180] and stores it at +4.
// VTABLE: GAMEMD 0x7E5858 -- retail identity only; not emitted by this TU.
template <class T>
class BlitTransDarkenZReadWrite : public Blitter
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

    T mask; // +0x04

    BlitTransDarkenZReadWrite(T value) : mask(value) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransDarkenZReadWrite<unsigned short>) == 8);

// BlitTransXlatZRead<unsigned short>. Allocation PUSH 8 at 0x48F19D / vptr 0x48F1B4; the inline
// constructor loads [owner+0x174] and stores it at +4.
// VTABLE: GAMEMD 0x7E5978 -- retail identity only; not emitted by this TU.
template <class T>
class BlitTransXlatZRead : public Blitter
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

    BlitTransXlatZRead(const T* table) : xlat(table) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransXlatZRead<unsigned short>) == 8);

// BlitTransXlatZReadWrite<unsigned short>. Allocation PUSH 8 at 0x48F352 / vptr 0x48F369; the inline
// constructor loads [owner+0x174] and stores it at +4.
// VTABLE: GAMEMD 0x7E5888 -- retail identity only; not emitted by this TU.
template <class T>
class BlitTransXlatZReadWrite : public Blitter
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

    BlitTransXlatZReadWrite(const T* table) : xlat(table) {}
};

GG_STATIC_ASSERT(sizeof(BlitTransXlatZReadWrite<unsigned short>) == 8);

// Member offsets (typedefs: VC6 rejects offsetof on a template-id inside the macro).
typedef BlitTransDarken<unsigned short> BlitTransDarkenUS_;
GG_STATIC_ASSERT(offsetof(BlitTransDarkenUS_, mask) == 4);
typedef BlitTransDarkenZRead<unsigned short> BlitTransDarkenZReadUS_;
GG_STATIC_ASSERT(offsetof(BlitTransDarkenZReadUS_, mask) == 4);
typedef BlitTransDarkenZReadWrite<unsigned short> BlitTransDarkenZReadWriteUS_;
GG_STATIC_ASSERT(offsetof(BlitTransDarkenZReadWriteUS_, mask) == 4);
typedef BlitTransXlatZRead<unsigned short> BlitTransXlatZReadUS_;
GG_STATIC_ASSERT(offsetof(BlitTransXlatZReadUS_, xlat) == 4);
typedef BlitTransXlatZReadWrite<unsigned short> BlitTransXlatZReadWriteUS_;
GG_STATIC_ASSERT(offsetof(BlitTransXlatZReadWriteUS_, xlat) == 4);

#endif // GG_MATCH_RENDER_BLITTERS_B_DARKEN_XLATZ_H
