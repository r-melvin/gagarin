// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6D2140: the coordinate is read as `[EBX]`, `[EBX+4]`,
//   `[EBX+8]` (X, Y, Z) off the first stacked argument, the 60x30 iso
//   projection is inlined with the Y spill/reload through `[ESP+0x10]`, the
//   height scale is `FMUL [0xB0CD48]`, the bias `FIADD [ESP+0x1C]` (the dead
//   first-argument slot) and the rounding constant `FADD [0x7E1738]` (0.5)
//   with the truncation through the CRT `__ftol` at 0x7C5F00; the result is
//   stored through the second stacked argument `[EAX]` / `[EAX+4]`, the view
//   offset is `[EBP+0xB0]` / `[EBP+0xB4]`, and the visibility bounds are the
//   globals `[0xB0CE30]` (+0x168) and `[0xB0CE34]` (+0xB4). `this` is only
//   read for the offset (RET 8, two stacked arguments). The method name is
//   the YRpp one (name only).
#ifndef GG_MATCH_UI_TACTICAL_CLASS_COORDS_TO_CLIENT_METHODS_H
#define GG_MATCH_UI_TACTICAL_CLASS_COORDS_TO_CLIENT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/tactical.h"
#include "../_layout/coord_struct.h"
#include "../_layout/geometry2d.h"

extern double DAT_00B0CD48;
// GLOBAL: GAMEMD 0xB0CE30 — view X extent.
extern int DAT_00B0CE30;
// GLOBAL: GAMEMD 0xB0CE34 — view Y extent.
extern int DAT_00B0CE34;

#endif  // GG_MATCH_UI_TACTICAL_CLASS_COORDS_TO_CLIENT_METHODS_H
