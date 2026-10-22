// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M3 candidate; instructions revalidated against pinned retail gamemd.exe. | behaviour-confirmed-name
// Cluster r-lucent50: eight RLEBlitter method specializations for
// unsigned-short pixels. The alpha-buffer handle is retained as an observed
// pointer-sized field; its allocation and destruction are outside this TU.
// Object extents and touched member offsets follow allocation/store evidence
// at 0x48EBF0.
// The two-argument constructors are the owner 0x48EBF0's inline construction: after
// `push 0xC; call 0x7C8E17` each site stores the pointer at +4, the second value at +8
// and the vptr, nothing else. blitter_ddtors_lucent_methods.cpp instantiates them to
// emit the vtables and scalar deleting destructors.
#ifndef GG_MATCH_RENDER_BLITTERS_R_LUCENT50_H
#define GG_MATCH_RENDER_BLITTERS_R_LUCENT50_H

#include <stddef.h>
#include "rle_blitter.h"
#include "r_shared_zwrap.h"
#include "b_shared_alpha.h"

// Alpha-buffer row wrap (retail re-reads the global 0x87E8A4 at every wrap).
inline unsigned short* RLELucent50AlphaWrapRow(unsigned short* row)
{
    if (row >= gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}

#define R_LUCENT50_SLOTS \
    virtual void RLEBlit(void* dest, const void* src, int len, int skip, \
                         int zval, unsigned short* zbuf, unsigned short* abuf, \
                         int alvl, int warp, const signed char* zshape); \
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip, \
                             int zval, unsigned short* zbuf, \
                             unsigned short* abuf, int alvl, int warp, \
                             const signed char* zshape, unsigned short tint);

// RLEBlitTransLucent50<unsigned short>: no depth test.
// Retail vtable address point: 0x7E5580 (table emission is outside this TU).
template <class T>
class RLEBlitTransLucent50 : public RLEBlitter
{
public:

    R_LUCENT50_SLOTS

    const T* table;           // +0x04
    unsigned short mask;      // +0x08
    RLEBlitTransLucent50(const T* t, unsigned short m) : table(t), mask(m) {}
};

typedef RLEBlitTransLucent50<unsigned short> RLEBlitTransLucent50US_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent50US_) == 0xC);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50US_, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50US_, mask) == 8);

// RLEBlitTransLucent50ZRead<unsigned short>: depth test against zbuf.
// Retail vtable address point: 0x7E5520 (table emission is outside this TU).
template <class T>
class RLEBlitTransLucent50ZRead : public RLEBlitter
{
public:

    R_LUCENT50_SLOTS

    const T* table;           // +0x04
    unsigned short mask;      // +0x08
    RLEBlitTransLucent50ZRead(const T* t, unsigned short m) : table(t), mask(m) {}
};

typedef RLEBlitTransLucent50ZRead<unsigned short> RLEBlitTransLucent50ZReadUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent50ZReadUS_) == 0xC);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50ZReadUS_, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50ZReadUS_, mask) == 8);

// RLEBlitTransLucent50ZReadWarp<unsigned short>: depth test; background sampled from dest[warp].
// Retail vtable address point: 0x7E54F0 (table emission is outside this TU).
template <class T>
class RLEBlitTransLucent50ZReadWarp : public RLEBlitter
{
public:

    R_LUCENT50_SLOTS

    const T* table;           // +0x04
    unsigned short mask;      // +0x08
    RLEBlitTransLucent50ZReadWarp(const T* t, unsigned short m) : table(t), mask(m) {}
};

typedef RLEBlitTransLucent50ZReadWarp<unsigned short> RLEBlitTransLucent50ZReadWarpUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent50ZReadWarpUS_) == 0xC);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50ZReadWarpUS_, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50ZReadWarpUS_, mask) == 8);

// RLEBlitTransLucent50ZReadWrite<unsigned short>: depth test, passing pixel also writes its depth.
// Retail vtable address point: 0x7E5490 (table emission is outside this TU).
template <class T>
class RLEBlitTransLucent50ZReadWrite : public RLEBlitter
{
public:

    R_LUCENT50_SLOTS

    const T* table;           // +0x04
    unsigned short mask;      // +0x08
    RLEBlitTransLucent50ZReadWrite(const T* t, unsigned short m) : table(t), mask(m) {}
};

typedef RLEBlitTransLucent50ZReadWrite<unsigned short> RLEBlitTransLucent50ZReadWriteUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent50ZReadWriteUS_) == 0xC);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50ZReadWriteUS_, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50ZReadWriteUS_, mask) == 8);

// RLEBlitTransLucent50Alpha<unsigned short>: no depth test; source colour is looked up through the alpha buffer.
// Retail vtable address point: 0x7E5440 (table emission is outside this TU).
template <class T>
class RLEBlitTransLucent50Alpha : public RLEBlitter
{
public:

    R_LUCENT50_SLOTS

    const T* table;           // +0x04
    unsigned short* alpha_handle; // +0x08
    unsigned short mask;      // +0x0C
};

typedef RLEBlitTransLucent50Alpha<unsigned short> RLEBlitTransLucent50AlphaUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent50AlphaUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaUS_, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaUS_, alpha_handle) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaUS_, mask) == 0xC);

// RLEBlitTransLucent50AlphaZRead<unsigned short>: alpha lookup plus depth test.
// Retail vtable address point: 0x7E53F0 (table emission is outside this TU).
template <class T>
class RLEBlitTransLucent50AlphaZRead : public RLEBlitter
{
public:

    R_LUCENT50_SLOTS

    const T* table;           // +0x04
    unsigned short* alpha_handle; // +0x08
    unsigned short mask;      // +0x0C
};

typedef RLEBlitTransLucent50AlphaZRead<unsigned short> RLEBlitTransLucent50AlphaZReadUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent50AlphaZReadUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaZReadUS_, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaZReadUS_, alpha_handle) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaZReadUS_, mask) == 0xC);

// RLEBlitTransLucent50AlphaZReadWarp<unsigned short>: alpha lookup, depth test, background from dest[warp].
// Retail vtable address point: 0x7E53C0 (table emission is outside this TU).
template <class T>
class RLEBlitTransLucent50AlphaZReadWarp : public RLEBlitter
{
public:

    R_LUCENT50_SLOTS

    const T* table;           // +0x04
    unsigned short* alpha_handle; // +0x08
    unsigned short mask;      // +0x0C
};

typedef RLEBlitTransLucent50AlphaZReadWarp<unsigned short> RLEBlitTransLucent50AlphaZReadWarpUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent50AlphaZReadWarpUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaZReadWarpUS_, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaZReadWarpUS_, alpha_handle) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaZReadWarpUS_, mask) == 0xC);

// RLEBlitTransLucent50AlphaZReadWrite<unsigned short>: alpha lookup, depth test and depth write.
// Retail vtable address point: 0x7E5370 (table emission is outside this TU).
template <class T>
class RLEBlitTransLucent50AlphaZReadWrite : public RLEBlitter
{
public:

    R_LUCENT50_SLOTS

    const T* table;           // +0x04
    unsigned short* alpha_handle; // +0x08
    unsigned short mask;      // +0x0C
};

typedef RLEBlitTransLucent50AlphaZReadWrite<unsigned short> RLEBlitTransLucent50AlphaZReadWriteUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent50AlphaZReadWriteUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaZReadWriteUS_, table) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaZReadWriteUS_, alpha_handle) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent50AlphaZReadWriteUS_, mask) == 0xC);

#undef R_LUCENT50_SLOTS

#endif // GG_MATCH_RENDER_BLITTERS_R_LUCENT50_H
