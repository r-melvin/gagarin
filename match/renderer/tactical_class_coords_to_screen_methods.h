// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6D1F10: the coordinate is read as `[EBX]`, `[EBX+4]`,
//   `[EBX+8]` (X, Y, Z), the result is stored as `[EAX]` / `[EAX+4]` through
//   the first stacked argument, the height scale is `FMUL [0xB0CD48]` and the
//   rounding bias `FADD [0x7E1738]` (0.5), with the truncation through the
//   CRT `__ftol` at 0x7C5F00. `this` is never read (RET 8, two stacked
//   arguments). The method name is the YRpp one (name only).
#ifndef GG_MATCH_RENDERER_TACTICAL_CLASS_COORDS_TO_SCREEN_METHODS_H
#define GG_MATCH_RENDERER_TACTICAL_CLASS_COORDS_TO_SCREEN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Point2D_006D1F10
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
};
GG_STATIC_ASSERT(sizeof(Point2D_006D1F10) == 0x8);

struct Coord_006D1F10
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
    int Z;                    // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_006D1F10) == 0xC);
GG_STATIC_ASSERT(offsetof(Coord_006D1F10, Z) == 0x8);

// GLOBAL: GAMEMD 0xB0CD48 — the height-to-pixel scale (runtime-initialised
// double; zero in the image).
extern double DAT_00B0CD48;

struct Tactical_006D1F10
{
    // FUNCTION: GAMEMD 0x6D1F10 — Tactical::CoordsToScreen. `this` is
    // unused; the coordinate is projected to the raw iso pixel position.
    Point2D_006D1F10* CoordsToScreen(Point2D_006D1F10* pDest,
                                     const Coord_006D1F10* pCoord);
};

#endif  // GG_MATCH_RENDERER_TACTICAL_CLASS_COORDS_TO_SCREEN_METHODS_H
