// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Leading shape-file words read by0x69DD83,0x4B4E10 and0x6D4E8D.
// Eight-byte fixed prefix; frame payloads follow this header.
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
    short Frames; // MOVSX [ESI+6] at6D4E8D
};
GG_STATIC_ASSERT(offsetof(ShapeHeader, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(ShapeHeader, Width) == 2);
GG_STATIC_ASSERT(offsetof(ShapeHeader, Height) == 4);
GG_STATIC_ASSERT(offsetof(ShapeHeader, Frames) == 6);
GG_STATIC_ASSERT(sizeof(((ShapeHeader*)0)->Frames) == 2);
GG_STATIC_ASSERT(sizeof(((ShapeHeader*)0)->Width) == 2);
GG_STATIC_ASSERT(sizeof(((ShapeHeader*)0)->Height) == 2);
GG_STATIC_ASSERT(sizeof(ShapeHeader) == 8);
#endif
