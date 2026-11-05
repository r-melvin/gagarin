// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Calling convention read from the retail gamemd.exe v1.001 call sites of 0x4AED70.
#ifndef GG_MATCH_SHAPE_BLIT_004AED70_H
#define GG_MATCH_SHAPE_BLIT_004AED70_H

#include "_layout/geometry2d.h"

// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) -- shape blitter, __fastcall: surface in ECX, conversion in EDX and
// fourteen stack words (RET 0x38; the last two are a point passed by value). The surface, conversion and shape stay
// void*: callers hold them through several views and no canonical shape file type is settled.
void __fastcall FUN_004AED70(void* surface, void* conversion, void* shape,
    int frame, const Point2D* point, RectangleStruct* clip, int flags,
    int a8, int z, int a10, int intensity, int a12, int a13, int a14,
    Point2D offset);

#endif  // GG_MATCH_SHAPE_BLIT_004AED70_H
