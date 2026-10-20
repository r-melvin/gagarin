// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// XYWH bounds fields are read at 0x7BAF10/0x7BAF90 (XSurface pixel access).
// Point fields/stack width: retail BitFont::Lock 0x4348F0 and ToolTipManager
// accesses at 0x724AD0. Rectangle result layout: Surface::GetRect 0x411510.
#ifndef GG_MATCH_LAYOUT_GEOMETRY2D_H
#define GG_MATCH_LAYOUT_GEOMETRY2D_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Point2D { int X; int Y; };
GG_STATIC_ASSERT(offsetof(Point2D, X) == 0x00);
GG_STATIC_ASSERT(offsetof(Point2D, Y) == 0x04);
GG_STATIC_ASSERT(sizeof(Point2D) == 0x08);

// Coordinates plus dimensions, as distinct from left/top/right/bottom bounds.
struct XYWHStruct { int X; int Y; int Width; int Height; };
GG_STATIC_ASSERT(offsetof(XYWHStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(XYWHStruct, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(XYWHStruct, Width) == 0x08);
GG_STATIC_ASSERT(offsetof(XYWHStruct, Height) == 0x0C);
GG_STATIC_ASSERT(sizeof(XYWHStruct) == 0x10);

struct LTRBStruct { int Left; int Top; int Right; int Bottom; };
GG_STATIC_ASSERT(offsetof(LTRBStruct, Left) == 0x00);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Right) == 0x08);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Bottom) == 0x0C);
GG_STATIC_ASSERT(sizeof(LTRBStruct) == 0x10);
#endif
