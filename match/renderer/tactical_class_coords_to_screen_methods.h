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

#include "../_layout/geometry2d.h"
#include "../_layout/coord_struct.h"
#include "../_layout/tactical.h"

// GLOBAL: GAMEMD 0xB0CD48 — the height-to-pixel scale (runtime-initialised
// double; zero in the image).
extern double DAT_00B0CD48;

#endif  // GG_MATCH_RENDERER_TACTICAL_CLASS_COORDS_TO_SCREEN_METHODS_H
