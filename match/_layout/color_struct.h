// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Packed RGB stores4355B0; Tactical6DBF5C..6DBF6F copies3bytes then blends.
// User construction also explains VC6's guarded local-static cleanup registration;
// no manually implemented guard or atexit call is part of the source model.
#ifndef GG_MATCH_LAYOUT_COLOR_STRUCT_H
#define GG_MATCH_LAYOUT_COLOR_STRUCT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// ColorStruct — packed RGB triple (no padding; size = 3).
struct ColorStruct
{
    unsigned char R;   // +0x00
    unsigned char G;   // +0x01
    unsigned char B;   // +0x02
    ColorStruct() {}
    // CALLEE: GAMEMD 0x4355B0; inline zero construction in6DBEF2..6DBF06.
    ColorStruct(unsigned char r, unsigned char g, unsigned char b) : R(r), G(g), B(b) {}
    // Declaration: GAMEMD 0x6612C0, ratio and target pointer stacked, RET8.
    void FUN_006612C0(int ratio, const ColorStruct& target);
};

GG_STATIC_ASSERT(offsetof(ColorStruct, R) == 0x00);
GG_STATIC_ASSERT(offsetof(ColorStruct, G) == 0x01);
GG_STATIC_ASSERT(offsetof(ColorStruct, B) == 0x02);
GG_STATIC_ASSERT(sizeof(ColorStruct)      == 3);

#endif
