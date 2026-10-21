// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// Blitter RTTI identifies a five-slot interface at the address point below;
// slots 1-4 are the four methods declared here. An empty inline destructor
// reproduces the base deleting wrapper naturally emitted by b_trans.cpp.
// This is a compiler-emission reconstruction, not proof of original source
// spelling or a separate ordinary destructor entry. Pure slots remain runtime
// bindings, with no recovered runtime body.
#ifndef GG_MATCH_RENDER_BLITTERS_BLITTER_H
#define GG_MATCH_RENDER_BLITTERS_BLITTER_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E5B88 -- Blitter address point, five slots; slot checks
// were conditional on recorded COFF weak defaults and are not final-link proof.
class Blitter
{
public:
    // SYNTHETIC: GAMEMD 0x499CC0 -- compiler-generated deleting wrapper.
    virtual ~Blitter() {}

    virtual void BlitCopy(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl, int warp) = 0;
    virtual void BlitCopyTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, int warp, unsigned short tint) = 0;
    virtual void BlitMove(void* dest, const void* src, int len, int zval,
                          unsigned short* zbuf, unsigned short* abuf,
                          int alvl) = 0;
    virtual void BlitMoveTint(void* dest, const void* src, int len, int zval,
                              unsigned short* zbuf, unsigned short* abuf,
                              int alvl, unsigned short tint) = 0;
};

// Slot offsets of the retail interface; this layout is not an emitted table.
struct BlitterVtableLayout
{
    void* deletingDestructor;
    void* BlitCopy;
    void* BlitCopyTint;
    void* BlitMove;
    void* BlitMoveTint;
};
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(BlitterVtableLayout) == 0x14);
GG_STATIC_ASSERT(offsetof(BlitterVtableLayout, deletingDestructor) == 0x00);
GG_STATIC_ASSERT(offsetof(BlitterVtableLayout, BlitCopy) == 0x04);
GG_STATIC_ASSERT(offsetof(BlitterVtableLayout, BlitCopyTint) == 0x08);
GG_STATIC_ASSERT(offsetof(BlitterVtableLayout, BlitMove) == 0x0C);
GG_STATIC_ASSERT(offsetof(BlitterVtableLayout, BlitMoveTint) == 0x10);
#endif // GG_MATCH_RENDER_BLITTERS_BLITTER_H
