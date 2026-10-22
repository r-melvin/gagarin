// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// RLEBlitter is the separate root at RTTI TypeDescriptor 0x81EF48, vtable
// address point 0x7E5BA0. The observed table has deleting slot 0 at 0x499DA0,
// pure slots 1-2 at 0x4C9150, and no base classes. This declaration-only view
// supplies the interface and four-byte base prefix; it does not emit that table.
#ifndef GG_MATCH_RENDER_BLITTERS_RLE_BLITTER_H
#define GG_MATCH_RENDER_BLITTERS_RLE_BLITTER_H

#include "blitter.h"

// VTABLE: GAMEMD 0x7E5BA0
class RLEBlitter
{
public:
    virtual ~RLEBlitter() {}
    virtual void RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape) = 0;
    virtual void RLEBlitTint(void* dest, const void* src, int len, int skip,
                             int zval, unsigned short* zbuf,
                             unsigned short* abuf, int alvl, int warp,
                             const signed char* zshape,
                             unsigned short tint) = 0;
};
GG_STATIC_ASSERT(sizeof(RLEBlitter) == 4);

struct RLEBlitterVtableLayout
{
    void* deletingDestructor;
    void* RLEBlit;
    void* RLEBlitTint;
};
GG_STATIC_ASSERT(sizeof(RLEBlitterVtableLayout) == 0x0C);
GG_STATIC_ASSERT(offsetof(RLEBlitterVtableLayout, deletingDestructor) == 0x00);
GG_STATIC_ASSERT(offsetof(RLEBlitterVtableLayout, RLEBlit) == 0x04);
GG_STATIC_ASSERT(offsetof(RLEBlitterVtableLayout, RLEBlitTint) == 0x08);

#endif
