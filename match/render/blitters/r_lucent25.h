// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c. | behaviour-confirmed-name
// Field offsets below are confirmed by the leaf accesses. The owner at
// 0x48EBF0 allocates the non-alpha leaves as 0xC bytes and alpha leaves as
// 0x10 bytes, then stores their vptrs at +0; those stores identify the size
// assertions for each specialization. This is a method/layout view, not
// constructor, destructor, pool ownership, or derived-vtable recovery.
// Allocation -> vptr evidence: 0x48FBCC -> 0x7E5570,
// 0x48FCE2 -> 0x7E5510, 0x48FD78 -> 0x7E54E0, 0x48FE8E -> 0x7E5480;
// 0x48FFDF -> 0x7E5430, 0x490149 -> 0x7E53E0,
// 0x49022A -> 0x7E53B0, 0x490349 -> 0x7E5360.
#ifndef GG_MATCH_RENDER_BLITTERS_R_LUCENT25_H
#define GG_MATCH_RENDER_BLITTERS_R_LUCENT25_H

#include <stddef.h>
#include "rle_blitter.h"
#include "r_shared_zwrap.h"
#include "b_shared_alpha.h"

// Inline row-wrap operation observed at the RLE Z/alpha loop tails.
inline unsigned short* RLEL25AlphaWrapRow(unsigned short* row)
{
    if (row >= gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}

template <class T> class RLEBlitTransLucent25 : public RLEBlitter {
public:
    virtual void RLEBlit(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*);
    virtual void RLEBlitTint(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*, unsigned short);
    const T* palette; // +4
    unsigned short mask; // +8
};

// This non-alpha layout is backed by +4 palette / +8 mask accesses in the
// methods below and 0xC allocations in the owner initialization.
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent25<unsigned short>) == 0x0C);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25<unsigned short>, palette) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25<unsigned short>, mask) == 8);

template <class T> class RLEBlitTransLucent25ZRead : public RLEBlitter {
public:
    virtual void RLEBlit(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*);
    virtual void RLEBlitTint(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*, unsigned short);
    const T* palette; // +4
    unsigned short mask; // +8
};
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent25ZRead<unsigned short>) == 0x0C);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25ZRead<unsigned short>, palette) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25ZRead<unsigned short>, mask) == 8);

template <class T> class RLEBlitTransLucent25ZReadWarp : public RLEBlitter {
public:
    virtual void RLEBlit(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*);
    virtual void RLEBlitTint(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*, unsigned short);
    const T* palette; // +4
    unsigned short mask; // +8
};
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent25ZReadWarp<unsigned short>) == 0x0C);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25ZReadWarp<unsigned short>, palette) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25ZReadWarp<unsigned short>, mask) == 8);

template <class T> class RLEBlitTransLucent25ZReadWrite : public RLEBlitter {
public:
    virtual void RLEBlit(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*);
    virtual void RLEBlitTint(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*, unsigned short);
    const T* palette; // +4
    unsigned short mask; // +8
};
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent25ZReadWrite<unsigned short>) == 0x0C);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25ZReadWrite<unsigned short>, palette) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25ZReadWrite<unsigned short>, mask) == 8);

template <class T> class RLEBlitTransLucent25Alpha : public RLEBlitter {
public:
    virtual ~RLEBlitTransLucent25Alpha();
    virtual void RLEBlit(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*);
    virtual void RLEBlitTint(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*, unsigned short);
    const T* palette; // +4
    unsigned short* alpha_tab; // +8
    unsigned short mask; // +0xC
};
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent25Alpha<unsigned short>) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25Alpha<unsigned short>, palette) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25Alpha<unsigned short>, alpha_tab) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25Alpha<unsigned short>, mask) == 0xC);

template <class T> class RLEBlitTransLucent25AlphaZRead : public RLEBlitter {
public:
    virtual ~RLEBlitTransLucent25AlphaZRead();
    virtual void RLEBlit(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*);
    virtual void RLEBlitTint(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*, unsigned short);
    const T* palette; // +4
    unsigned short* alpha_tab; // +8
    unsigned short mask; // +0xC
};
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent25AlphaZRead<unsigned short>) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25AlphaZRead<unsigned short>, palette) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25AlphaZRead<unsigned short>, alpha_tab) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25AlphaZRead<unsigned short>, mask) == 0xC);

template <class T> class RLEBlitTransLucent25AlphaZReadWarp : public RLEBlitter {
public:
    virtual ~RLEBlitTransLucent25AlphaZReadWarp();
    virtual void RLEBlit(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*);
    virtual void RLEBlitTint(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*, unsigned short);
    const T* palette; // +4
    unsigned short* alpha_tab; // +8
    unsigned short mask; // +0xC
};
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent25AlphaZReadWarp<unsigned short>) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25AlphaZReadWarp<unsigned short>, palette) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25AlphaZReadWarp<unsigned short>, alpha_tab) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25AlphaZReadWarp<unsigned short>, mask) == 0xC);

template <class T> class RLEBlitTransLucent25AlphaZReadWrite : public RLEBlitter {
public:
    virtual ~RLEBlitTransLucent25AlphaZReadWrite();
    virtual void RLEBlit(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*);
    virtual void RLEBlitTint(void*, const void*, int, int, int, unsigned short*, unsigned short*, int, int, const signed char*, unsigned short);
    const T* palette; // +4
    unsigned short* alpha_tab; // +8
    unsigned short mask; // +0xC
};
GG_STATIC_ASSERT(sizeof(RLEBlitTransLucent25AlphaZReadWrite<unsigned short>) == 0x10);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25AlphaZReadWrite<unsigned short>, palette) == 4);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25AlphaZReadWrite<unsigned short>, alpha_tab) == 8);
GG_STATIC_ASSERT(offsetof(RLEBlitTransLucent25AlphaZReadWrite<unsigned short>, mask) == 0xC);

#endif
