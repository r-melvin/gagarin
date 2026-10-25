// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. Retail display shift operands at
// 0x8A0DD0..0x8A0DE4; retained working names from the verified blitter view.
#ifndef GG_MATCH_RENDERER_PIXEL_SHIFT_VIEW_H
#define GG_MATCH_RENDERER_PIXEL_SHIFT_VIEW_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Canonical reconstruction representation of six observed DWORD cells at
// 0x8A0DD0..0x8A0DE4. Native writer 0x4BA770 stores each complete DWORD;
// the existing reconstruction accessor uses an eight-byte pair stride.
// Original declaration form is unknown: six independent globals also fit this
// footprint. Only this reconstructed 24-byte storage representation is owned.
// Existing pos/loss field names retain the verified blitter access order.
struct BTranslucentPixelFormat
{
    int pos0;   // +0x00  0x8A0DD0
    int loss0;  // +0x04  0x8A0DD4
    int pos2;   // +0x08  0x8A0DD8
    int loss2;  // +0x0C  0x8A0DDC
    int pos1;   // +0x10  0x8A0DE0
    int loss1;  // +0x14  0x8A0DE4
};

GG_STATIC_ASSERT(sizeof(int) == 4);
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
