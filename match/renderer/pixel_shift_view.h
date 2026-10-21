// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. Retail display shift operands at
// 0x8A0DD0..0x8A0DE4; retained working names from the verified blitter view.
#ifndef GG_MATCH_RENDERER_PIXEL_SHIFT_VIEW_H
#define GG_MATCH_RENDERER_PIXEL_SHIFT_VIEW_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Address view beginning at 0x8A0DD0 over the six DWORD shift operands used by
// WriteAlpha. These bytes share storage with the six scalar shift globals used
// elsewhere; this declaration does not claim separate storage or a full owner.
// The access order follows the instructions in this method; no channel identity
// or enclosing-object extent is asserted here.
struct BTranslucentPixelFormat
{
    int pos0;   // +0x00  0x8A0DD0
    int loss0;  // +0x04  0x8A0DD4
    int pos2;   // +0x08  0x8A0DD8
    int loss2;  // +0x0C  0x8A0DDC
    int pos1;   // +0x10  0x8A0DE0
    int loss1;  // +0x14  0x8A0DE4
};

GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, pos0) == 0);
GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, loss0) == 4);
GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, pos2) == 8);
GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, loss2) == 0xC);
GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, pos1) == 0x10);
GG_STATIC_ASSERT(offsetof(BTranslucentPixelFormat, loss1) == 0x14);
GG_STATIC_ASSERT(sizeof(BTranslucentPixelFormat) == 0x18);

// GLOBAL: GAMEMD 0x8A0DD0
extern "C" BTranslucentPixelFormat gg_b_translucent_pixel_format;

#endif
