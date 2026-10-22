// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c. | YRpp-cross-check
// RTTI and entry-origin retail instructions establish eight Blitter-derived
// address-point identities and the member accesses below. This header is a
// method/layout view for explicit <unsigned short> specializations only; this
// TU does not instantiate the classes or emit their deleting destructors or tables.
#ifndef GG_MATCH_RENDER_BLITTERS_B_LUCENT25_PRODUCTION_H
#define GG_MATCH_RENDER_BLITTERS_B_LUCENT25_PRODUCTION_H
#include <stddef.h>
#include "blitter.h"
#include "b_shared_alpha.h"

// Retail object setup: allocation call site 0x48F14A pushes 0xc; nearby stores use this vtable pointer.
// VTABLE: GAMEMD 0x7E59A8 -- retail identity evidence; no table emitted by this TU.
template <class T> class BlitTransLucent25 : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat; // +0x04, 4-byte pointer access confirmed by retail
    unsigned short mask; // +0x08, 16-bit access confirmed by retail
};
GG_STATIC_ASSERT(sizeof(BlitTransLucent25<unsigned short>) == 0x0C);
typedef BlitTransLucent25<unsigned short> BlitTransLucent25US_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent25US_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25US_, mask) == 0x08);

// Retail object setup: allocation call site 0x48F272 pushes 0xc; nearby stores use this vtable pointer.
// VTABLE: GAMEMD 0x7E5900 -- retail identity evidence; no table emitted by this TU.
template <class T> class BlitTransLucent25ZRead : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat; // +0x04, 4-byte pointer access confirmed by retail
    unsigned short mask; // +0x08, 16-bit access confirmed by retail
};
GG_STATIC_ASSERT(sizeof(BlitTransLucent25ZRead<unsigned short>) == 0x0C);
typedef BlitTransLucent25ZRead<unsigned short> BlitTransLucent25ZReadUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent25ZReadUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25ZReadUS_, mask) == 0x08);

// Retail object setup: allocation call site 0x48F2FF pushes 0xc; nearby stores use this vtable pointer.
// VTABLE: GAMEMD 0x7E58B8 -- retail identity evidence; no table emitted by this TU.
template <class T> class BlitTransLucent25ZReadWarp : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat; // +0x04, 4-byte pointer access confirmed by retail
    unsigned short mask; // +0x08, 16-bit access confirmed by retail
};
GG_STATIC_ASSERT(sizeof(BlitTransLucent25ZReadWarp<unsigned short>) == 0x0C);
typedef BlitTransLucent25ZReadWarp<unsigned short> BlitTransLucent25ZReadWarpUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent25ZReadWarpUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25ZReadWarpUS_, mask) == 0x08);

// Retail object setup: allocation call site 0x48F427 pushes 0xc; nearby stores use this vtable pointer.
// VTABLE: GAMEMD 0x7E5810 -- retail identity evidence; no table emitted by this TU.
template <class T> class BlitTransLucent25ZReadWrite : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat; // +0x04, 4-byte pointer access confirmed by retail
    unsigned short mask; // +0x08, 16-bit access confirmed by retail
};
GG_STATIC_ASSERT(sizeof(BlitTransLucent25ZReadWrite<unsigned short>) == 0x0C);
typedef BlitTransLucent25ZReadWrite<unsigned short> BlitTransLucent25ZReadWriteUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent25ZReadWriteUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25ZReadWriteUS_, mask) == 0x08);

// Retail object setup: allocation call site 0x48F5A7 pushes 0x10; nearby stores use this vtable pointer.
// VTABLE: GAMEMD 0x7E5780 -- retail identity evidence; no table emitted by this TU.
template <class T> class BlitTransLucent25Alpha : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat; // +0x04, 4-byte pointer access confirmed by retail
    unsigned short* alpha; // +0x08, 4-byte pointer access confirmed by retail
    unsigned short mask; // +0x0C, 16-bit access confirmed by retail
};
GG_STATIC_ASSERT(sizeof(BlitTransLucent25Alpha<unsigned short>) == 0x10);
typedef BlitTransLucent25Alpha<unsigned short> BlitTransLucent25AlphaUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaUS_, alpha) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaUS_, mask) == 0x0C);

// Retail object setup: allocation call site 0x48F812 pushes 0x10; nearby stores use this vtable pointer.
// VTABLE: GAMEMD 0x7E5690 -- retail identity evidence; no table emitted by this TU.
template <class T> class BlitTransLucent25AlphaZRead : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat; // +0x04, 4-byte pointer access confirmed by retail
    unsigned short* alpha; // +0x08, 4-byte pointer access confirmed by retail
    unsigned short mask; // +0x0C, 16-bit access confirmed by retail
};
GG_STATIC_ASSERT(sizeof(BlitTransLucent25AlphaZRead<unsigned short>) == 0x10);
typedef BlitTransLucent25AlphaZRead<unsigned short> BlitTransLucent25AlphaZReadUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaZReadUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaZReadUS_, alpha) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaZReadUS_, mask) == 0x0C);

// Retail object setup: allocation call site 0x48F8F3 pushes 0x10; nearby stores use this vtable pointer.
// VTABLE: GAMEMD 0x7E5648 -- retail identity evidence; no table emitted by this TU.
template <class T> class BlitTransLucent25AlphaZReadWarp : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat; // +0x04, 4-byte pointer access confirmed by retail
    unsigned short* alpha; // +0x08, 4-byte pointer access confirmed by retail
    unsigned short mask; // +0x0C, 16-bit access confirmed by retail
};
GG_STATIC_ASSERT(sizeof(BlitTransLucent25AlphaZReadWarp<unsigned short>) == 0x10);
typedef BlitTransLucent25AlphaZReadWarp<unsigned short> BlitTransLucent25AlphaZReadWarpUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaZReadWarpUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaZReadWarpUS_, alpha) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaZReadWarpUS_, mask) == 0x0C);

// Retail object setup: allocation call site 0x48FA9D pushes 0x10; nearby stores use this vtable pointer.
// VTABLE: GAMEMD 0x7E55D0 -- retail identity evidence; no table emitted by this TU.
template <class T> class BlitTransLucent25AlphaZReadWrite : public Blitter
{
public:
    virtual void BlitCopy(void*, const void*, int, int, unsigned short*, unsigned short*, int, int);
    virtual void BlitCopyTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, int, unsigned short);
    virtual void BlitMove(void*, const void*, int, int, unsigned short*, unsigned short*, int);
    virtual void BlitMoveTint(void*, const void*, int, int, unsigned short*, unsigned short*, int, unsigned short);
    const T* xlat; // +0x04, 4-byte pointer access confirmed by retail
    unsigned short* alpha; // +0x08, 4-byte pointer access confirmed by retail
    unsigned short mask; // +0x0C, 16-bit access confirmed by retail
};
GG_STATIC_ASSERT(sizeof(BlitTransLucent25AlphaZReadWrite<unsigned short>) == 0x10);
typedef BlitTransLucent25AlphaZReadWrite<unsigned short> BlitTransLucent25AlphaZReadWriteUS_;
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaZReadWriteUS_, xlat) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaZReadWriteUS_, alpha) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitTransLucent25AlphaZReadWriteUS_, mask) == 0x0C);

#endif
