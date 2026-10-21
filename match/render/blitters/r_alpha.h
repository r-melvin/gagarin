// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M3 candidate; instruction/layout facts revalidated against pinned retail gamemd.exe.
// Production-only method declarations for the six unsigned-short RLE alpha leaves.
// This package excludes constructors, destructors, deleting wrappers, vtable emission,
// alpha-pool storage, and pool lifetime claims. Derived slot/table address points are
// not claimed by this TU. Touched layout offsets come from retail member loads/stores.
#ifndef GG_MATCH_RENDER_BLITTERS_R_ALPHA_H
#define GG_MATCH_RENDER_BLITTERS_R_ALPHA_H

#include <stddef.h>
#include "rle_blitter.h"
#include "r_shared_zwrap.h"
#include "b_shared_alpha.h"

inline unsigned short* RLEAlphaWrapRow(unsigned short* row)
{
    if (row >= gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}

#define R_ALPHA_SLOTS \
    virtual void RLEBlit(void* dest, const void* src, int len, int skip, \
                         int zval, unsigned short* zbuf, unsigned short* abuf, \
                         int alvl, int warp, const signed char* zshape); \
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip, \
                             int zval, unsigned short* zbuf, unsigned short* abuf, \
                             int alvl, int warp, const signed char* zshape, \
                             unsigned short tint);

// RLEBlitTransXlatAlpha<unsigned short>: methods only; lifetime and emitted table are outside this TU.
template <class T>
class RLEBlitTransXlatAlpha : public RLEBlitter
{
public:
    R_ALPHA_SLOTS
    const T* table; // +0x04
    unsigned short* alpha; // +0x08
};
typedef RLEBlitTransXlatAlpha<unsigned short> RLEBlitTransXlatAlphaUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransXlatAlphaUS_) == 0xC);
GG_STATIC_ASSERT(offsetof(RLEBlitTransXlatAlphaUS_, table) == 0x4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransXlatAlphaUS_, alpha) == 0x8);

// RLEBlitTransXlatAlphaZRead<unsigned short>: methods only; lifetime and emitted table are outside this TU.
template <class T>
class RLEBlitTransXlatAlphaZRead : public RLEBlitter
{
public:
    R_ALPHA_SLOTS
    const T* table; // +0x04
    unsigned short* alpha; // +0x08
};
typedef RLEBlitTransXlatAlphaZRead<unsigned short> RLEBlitTransXlatAlphaZReadUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransXlatAlphaZReadUS_) == 0xC);
GG_STATIC_ASSERT(offsetof(RLEBlitTransXlatAlphaZReadUS_, table) == 0x4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransXlatAlphaZReadUS_, alpha) == 0x8);

// RLEBlitTransXlatAlphaZReadWrite<unsigned short>: methods only; lifetime and emitted table are outside this TU.
template <class T>
class RLEBlitTransXlatAlphaZReadWrite : public RLEBlitter
{
public:
    R_ALPHA_SLOTS
    const T* table; // +0x04
    unsigned short* alpha; // +0x08
};
typedef RLEBlitTransXlatAlphaZReadWrite<unsigned short> RLEBlitTransXlatAlphaZReadWriteUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransXlatAlphaZReadWriteUS_) == 0xC);
GG_STATIC_ASSERT(offsetof(RLEBlitTransXlatAlphaZReadWriteUS_, table) == 0x4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransXlatAlphaZReadWriteUS_, alpha) == 0x8);

// RLEBlitTransZRemapXlatAlpha<unsigned short>: methods only; lifetime and emitted table are outside this TU.
template <class T>
class RLEBlitTransZRemapXlatAlpha : public RLEBlitter
{
public:
    R_ALPHA_SLOTS
    const unsigned char* const* remap; // +0x04
    const T* table; // +0x08
    unsigned short* alpha; // +0x0C
};
typedef RLEBlitTransZRemapXlatAlpha<unsigned short> RLEBlitTransZRemapXlatAlphaUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransZRemapXlatAlphaUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatAlphaUS_, remap) == 0x4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatAlphaUS_, table) == 0x8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatAlphaUS_, alpha) == 0xC);

// RLEBlitTransZRemapXlatAlphaZRead<unsigned short>: methods only; lifetime and emitted table are outside this TU.
template <class T>
class RLEBlitTransZRemapXlatAlphaZRead : public RLEBlitter
{
public:
    R_ALPHA_SLOTS
    const unsigned char* const* remap; // +0x04
    const T* table; // +0x08
    unsigned short* alpha; // +0x0C
};
typedef RLEBlitTransZRemapXlatAlphaZRead<unsigned short> RLEBlitTransZRemapXlatAlphaZReadUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransZRemapXlatAlphaZReadUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatAlphaZReadUS_, remap) == 0x4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatAlphaZReadUS_, table) == 0x8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatAlphaZReadUS_, alpha) == 0xC);

// RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>: methods only; lifetime and emitted table are outside this TU.
template <class T>
class RLEBlitTransZRemapXlatAlphaZReadWrite : public RLEBlitter
{
public:
    R_ALPHA_SLOTS
    const unsigned char* const* remap; // +0x04
    const T* table; // +0x08
    unsigned short* alpha; // +0x0C
};
typedef RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short> RLEBlitTransZRemapXlatAlphaZReadWriteUS_;
GG_STATIC_ASSERT(sizeof(RLEBlitTransZRemapXlatAlphaZReadWriteUS_) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatAlphaZReadWriteUS_, remap) == 0x4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatAlphaZReadWriteUS_, table) == 0x8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransZRemapXlatAlphaZReadWriteUS_, alpha) == 0xC);

#undef R_ALPHA_SLOTS

#endif // GG_MATCH_RENDER_BLITTERS_R_ALPHA_H
