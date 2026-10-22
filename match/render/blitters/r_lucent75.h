// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: frozen M3 r-lucent75 packet (SHA-verified) and retail instruction | behaviour-confirmed-name
// accesses. This is a method-facing leaf view; it does not claim lifetime code,
// complete owner hierarchy, or emitted derived vtables.
#ifndef GG_MATCH_RENDER_BLITTERS_R_LUCENT75_H
#define GG_MATCH_RENDER_BLITTERS_R_LUCENT75_H
#include <stddef.h>
#include "blitter.h"
#include "rle_blitter.h"
#include "r_shared_zwrap.h"
#include "b_shared_alpha.h"
template <class T>
class RLEBlitTransLucent75 : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);
    const T* table; // +0x04
    unsigned short mask; // +0x08
    RLEBlitTransLucent75(const T* t, unsigned short m) : table(t), mask(m) {}
};

typedef RLEBlitTransLucent75<unsigned short> RLEBlitTransLucent75_us;

GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent75_us) == 0x0C);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75_us, table) == 0x04);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75_us, mask) == 0x08);

template <class T>
class RLEBlitTransLucent75ZRead : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);
    const T* table; // +0x04
    unsigned short mask; // +0x08
    RLEBlitTransLucent75ZRead(const T* t, unsigned short m) : table(t), mask(m) {}
};

typedef RLEBlitTransLucent75ZRead<unsigned short> RLEBlitTransLucent75ZRead_us;

GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent75ZRead_us) == 0x0C);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75ZRead_us, table) == 0x04);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75ZRead_us, mask) == 0x08);

template <class T>
class RLEBlitTransLucent75ZReadWarp : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);
    const T* table; // +0x04
    unsigned short mask; // +0x08
    RLEBlitTransLucent75ZReadWarp(const T* t, unsigned short m) : table(t), mask(m) {}
};

typedef RLEBlitTransLucent75ZReadWarp<unsigned short> RLEBlitTransLucent75ZReadWarp_us;

GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent75ZReadWarp_us) == 0x0C);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75ZReadWarp_us, table) == 0x04);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75ZReadWarp_us, mask) == 0x08);

template <class T>
class RLEBlitTransLucent75ZReadWrite : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);
    const T* table; // +0x04
    unsigned short mask; // +0x08
    RLEBlitTransLucent75ZReadWrite(const T* t, unsigned short m) : table(t), mask(m) {}
};

typedef RLEBlitTransLucent75ZReadWrite<unsigned short> RLEBlitTransLucent75ZReadWrite_us;

GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent75ZReadWrite_us) == 0x0C);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75ZReadWrite_us, table) == 0x04);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75ZReadWrite_us, mask) == 0x08);

template <class T>
class RLEBlitTransLucent75Alpha : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);
    const T* table; // +0x04
    unsigned short* rows; // +0x08
    unsigned short mask; // +0x0C
};

typedef RLEBlitTransLucent75Alpha<unsigned short> RLEBlitTransLucent75Alpha_us;

GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent75Alpha_us) == 0x10);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75Alpha_us, table) == 0x04);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75Alpha_us, rows) == 0x08);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75Alpha_us, mask) == 0x0C);

template <class T>
class RLEBlitTransLucent75AlphaZRead : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);
    const T* table; // +0x04
    unsigned short* rows; // +0x08
    unsigned short mask; // +0x0C
};

typedef RLEBlitTransLucent75AlphaZRead<unsigned short> RLEBlitTransLucent75AlphaZRead_us;

GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent75AlphaZRead_us) == 0x10);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75AlphaZRead_us, table) == 0x04);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75AlphaZRead_us, rows) == 0x08);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75AlphaZRead_us, mask) == 0x0C);

template <class T>
class RLEBlitTransLucent75AlphaZReadWarp : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);
    const T* table; // +0x04
    unsigned short* rows; // +0x08
    unsigned short mask; // +0x0C
};

typedef RLEBlitTransLucent75AlphaZReadWarp<unsigned short> RLEBlitTransLucent75AlphaZReadWarp_us;

GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent75AlphaZReadWarp_us) == 0x10);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75AlphaZReadWarp_us, table) == 0x04);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75AlphaZReadWarp_us, rows) == 0x08);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75AlphaZReadWarp_us, mask) == 0x0C);

template <class T>
class RLEBlitTransLucent75AlphaZReadWrite : public RLEBlitter
{
public:
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape);
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape, unsigned short tint);
    const T* table; // +0x04
    unsigned short* rows; // +0x08
    unsigned short mask; // +0x0C
};

typedef RLEBlitTransLucent75AlphaZReadWrite<unsigned short> RLEBlitTransLucent75AlphaZReadWrite_us;

GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent75AlphaZReadWrite_us) == 0x10);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75AlphaZReadWrite_us, table) == 0x04);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75AlphaZReadWrite_us, rows) == 0x08);

GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent75AlphaZReadWrite_us, mask) == 0x0C);
inline unsigned short* RLELucent75AlphaWrapRow(unsigned short* row)
{
    if (row >= gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}
#endif
