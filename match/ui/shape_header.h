// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Leading shape-file words read by 0x69DD83 and 0x4B4E10.
// Shared unchanged from the input-controls declaration; later file data is opaque.
#ifndef GG_MATCH_UI_SHAPE_HEADER_H
#define GG_MATCH_UI_SHAPE_HEADER_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct ShapeHeader
{
    short unknown_00;
    short Width;
    short Height;
};
GG_STATIC_ASSERT(offsetof(ShapeHeader, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(ShapeHeader, Width) == 2);
GG_STATIC_ASSERT(offsetof(ShapeHeader, Height) == 4);
GG_STATIC_ASSERT(sizeof(((ShapeHeader*)0)->Width) == 2);
GG_STATIC_ASSERT(sizeof(((ShapeHeader*)0)->Height) == 2);
GG_STATIC_ASSERT(sizeof(ShapeHeader) == 6);
#endif
