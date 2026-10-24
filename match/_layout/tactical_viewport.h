// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Live XYWH storage: Display4A8960 writes all four DWORDs at886FA0..886FAC;
// Tactical6D2B60 reads the origin and dimensions. No copied viewport object.
#ifndef GG_MATCH_LAYOUT_TACTICAL_VIEWPORT_H
#define GG_MATCH_LAYOUT_TACTICAL_VIEWPORT_H
#include "geometry2d.h"
extern RectangleStruct Viewport_00886FA0; // GLOBAL: GAMEMD 0x886FA0 (decl; reloc)
GG_STATIC_ASSERT(offsetof(RectangleStruct, X) == 0);
GG_STATIC_ASSERT(offsetof(RectangleStruct, Y) == 4);
GG_STATIC_ASSERT(offsetof(RectangleStruct, Width) == 8);
GG_STATIC_ASSERT(offsetof(RectangleStruct, Height) == 12);
GG_STATIC_ASSERT(sizeof(RectangleStruct) == 16);
#endif
