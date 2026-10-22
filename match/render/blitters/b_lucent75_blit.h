// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; method accesses and allocation-site member bounds recorded in the M2 evidence package. | YRpp-cross-check
// This header models the members touched by the retained BlitCopy bodies.
// The two-argument constructors are the owner 0x48EBF0's inline construction: after
// `push 0xC; call 0x7C8E17` each site stores the pointer at +4, the second value at +8
// and the vptr, nothing else. blitter_ddtors_lucent_methods.cpp instantiates them to
// emit the vtables and scalar deleting destructors.
#ifndef GG_MATCH_RENDER_BLITTERS_B_LUCENT75_BLIT_H
#define GG_MATCH_RENDER_BLITTERS_B_LUCENT75_BLIT_H

#include <stddef.h>
#include "blitter.h"
#include "b_shared_alpha.h"

// Retail setup allocates 0x0C bytes and stores the derived vptr at 0x48F0FD (inline initialization begins at 0x48F0FD; allocation call site 0x48F0EE).
template <class T> class BlitTransLucent75 : public Blitter {
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;       // +0x04, 4-byte pointer
    unsigned short mask; // +0x08, 16-bit mask
    BlitTransLucent75(const T* t, unsigned short m) : xlat(t), mask(m) {}
};
typedef BlitTransLucent75<unsigned short> BlitTransLucent75US_;
GG_STATIC_ASSERT(sizeof(BlitTransLucent75US_) == 0x0C);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75US_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75US_, mask) == 0x08);

// Retail setup allocates 0x0C bytes; inline initialization at 0x48F225 stores the derived vptr.
template <class T> class BlitTransLucent75ZRead : public Blitter {
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;       // +0x04, 4-byte pointer
    unsigned short mask; // +0x08, 16-bit mask
    BlitTransLucent75ZRead(const T* t, unsigned short m) : xlat(t), mask(m) {}
};
typedef BlitTransLucent75ZRead<unsigned short> BlitTransLucent75ZReadUS_;
GG_STATIC_ASSERT(sizeof(BlitTransLucent75ZReadUS_) == 0x0C);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75ZReadUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75ZReadUS_, mask) == 0x08);

// Retail setup allocates 0x0C bytes; inline initialization at 0x48F2B2 stores the derived vptr.
template <class T> class BlitTransLucent75ZReadWarp : public Blitter {
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;       // +0x04, 4-byte pointer
    unsigned short mask; // +0x08, 16-bit mask
    BlitTransLucent75ZReadWarp(const T* t, unsigned short m) : xlat(t), mask(m) {}
};
typedef BlitTransLucent75ZReadWarp<unsigned short> BlitTransLucent75ZReadWarpUS_;
GG_STATIC_ASSERT(sizeof(BlitTransLucent75ZReadWarpUS_) == 0x0C);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75ZReadWarpUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75ZReadWarpUS_, mask) == 0x08);

// Retail setup allocates 0x0C bytes; inline initialization at 0x48F3DA stores the derived vptr.
template <class T> class BlitTransLucent75ZReadWrite : public Blitter {
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;       // +0x04, 4-byte pointer
    unsigned short mask; // +0x08, 16-bit mask
    BlitTransLucent75ZReadWrite(const T* t, unsigned short m) : xlat(t), mask(m) {}
};
typedef BlitTransLucent75ZReadWrite<unsigned short> BlitTransLucent75ZReadWriteUS_;
GG_STATIC_ASSERT(sizeof(BlitTransLucent75ZReadWriteUS_) == 0x0C);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75ZReadWriteUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75ZReadWriteUS_, mask) == 0x08);

// Retail setup allocates 0x10 bytes in 0x48EBF0; inline initialization at 0x48F54D stores the derived vptr.
template <class T> class BlitTransLucent75Alpha : public Blitter {
public:
    virtual ~BlitTransLucent75Alpha();
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;         // +0x04, 4-byte pointer
    unsigned short* alpha; // +0x08, 4-byte pointer
    unsigned short mask;   // +0x0C, 16-bit mask
};
typedef BlitTransLucent75Alpha<unsigned short> BlitTransLucent75AlphaUS_;
GG_STATIC_ASSERT(sizeof(BlitTransLucent75AlphaUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaUS_, alpha) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaUS_, mask) == 0x0C);

// Retail setup allocates 0x10 bytes in 0x48EBF0; inline initialization at 0x48F7B5 stores the derived vptr.
template <class T> class BlitTransLucent75AlphaZRead : public Blitter {
public:
    virtual ~BlitTransLucent75AlphaZRead();
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;         // +0x04, 4-byte pointer
    unsigned short* alpha; // +0x08, 4-byte pointer
    unsigned short mask;   // +0x0C, 16-bit mask
};
typedef BlitTransLucent75AlphaZRead<unsigned short> BlitTransLucent75AlphaZReadUS_;
GG_STATIC_ASSERT(sizeof(BlitTransLucent75AlphaZReadUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaZReadUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaZReadUS_, alpha) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaZReadUS_, mask) == 0x0C);

// Retail setup allocates 0x10 bytes in 0x48EBF0; inline initialization at 0x48F896 stores the derived vptr.
template <class T> class BlitTransLucent75AlphaZReadWarp : public Blitter {
public:
    virtual ~BlitTransLucent75AlphaZReadWarp();
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;         // +0x04, 4-byte pointer
    unsigned short* alpha; // +0x08, 4-byte pointer
    unsigned short mask;   // +0x0C, 16-bit mask
};
typedef BlitTransLucent75AlphaZReadWarp<unsigned short> BlitTransLucent75AlphaZReadWarpUS_;
GG_STATIC_ASSERT(sizeof(BlitTransLucent75AlphaZReadWarpUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaZReadWarpUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaZReadWarpUS_, alpha) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaZReadWarpUS_, mask) == 0x0C);

// Retail setup allocates 0x10 bytes in 0x48EBF0; inline initialization at 0x48FA40 stores the derived vptr.
template <class T> class BlitTransLucent75AlphaZReadWrite : public Blitter {
public:
    virtual ~BlitTransLucent75AlphaZReadWrite();
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat;         // +0x04, 4-byte pointer
    unsigned short* alpha; // +0x08, 4-byte pointer
    unsigned short mask;   // +0x0C, 16-bit mask
};
typedef BlitTransLucent75AlphaZReadWrite<unsigned short> BlitTransLucent75AlphaZReadWriteUS_;
GG_STATIC_ASSERT(sizeof(BlitTransLucent75AlphaZReadWriteUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaZReadWriteUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaZReadWriteUS_, alpha) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransLucent75AlphaZReadWriteUS_, mask) == 0x0C);

inline unsigned short* BLucent75AlphaWrapRow(unsigned short* row)
{
    if (row >= gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}

#endif
