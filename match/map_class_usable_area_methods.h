// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x578540: on the cell `MOVSX EDX,[EAX+0x26]` /
//   `MOVSX EDI,[EAX+0x24]` (MapCoords.Y / .X), `MOV BL,[EAX+0x11C]`
//   (SlopeIndex byte) and `MOVSX ESI,[EAX+0x11B]` (Level, signed char); on
//   the map `[ECX+0xF4]` (MapRect.Width), `[ECX+0xFC]` / `[ECX+0x100]` /
//   `[ECX+0x104]` / `[ECX+0x108]` (VisibleRect X / Y / Width / Height).
//   Names cross-checked against YRpp;
//   MapRect @0xEC / VisibleRect @0xFC agree with
//   match/map_class_more_methods.h (Width @0xF4, Height @0xF8) and
//   match/map_class_sublocation_methods.h (Level @0x11B).
#ifndef GG_MATCH_MAP_MAP_CLASS_USABLE_AREA_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_USABLE_AREA_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

#include "_layout/cell_class.h"
#include "ui_display_chain.h"

#endif  // GG_MATCH_MAP_MAP_CLASS_USABLE_AREA_METHODS_H
