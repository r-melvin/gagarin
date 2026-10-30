// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x486E70:
//     * three __thiscall getters returning a 16-byte rectangle through the
//       hidden-pointer convention (`LEA EAX,[ESP+n]; PUSH EAX; MOV ECX,this;
//       CALL`): 0x47FF80, 0x47FB90 and 0x47FDE0. The rectangle's members are
//       `[p+0]` X, `[p+4]` Y, `[p+8]` Width, `[p+0xC]` Height — the width and
//       height are the `TEST; JLE` validity tests.
//     * the tactical origin globals `[0x886FA0]` / `[0x886FA4]` subtracted
//       from X / Y, already named the same way in
//       match/map/veinhole_monster_draw_methods.cpp.
//     * `MOV ECX,[0x887324]` — the tactical/projector instance *pointer*;
//       0x6D2790 takes the rectangle by value (`PUSH 0; SUB ESP,0x10` then
//       four dword stores through `MOV EDX,ESP`) plus a trailing flag.
//     * `MOV EAX,<this>; ADD EAX,0x24; MOV ECX,0x87F7E8; CALL 0x6551C0` —
//       CellClass::MapCoords at +0x24 handed to a MapClass singleton method.
//   Names cross-checked against YRpp / RectangleStruct.
#ifndef GG_MATCH_MAP_CELL_CLASS_MARK_REDRAW_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_MARK_REDRAW_METHODS_H

#include <stddef.h>
#include "../_layout/map_0087f7e8.h"
#include "../_layout/tactical.h"
#include "../_rt/gg_static_assert.h"

#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

#include "../_layout/geometry2d.h"
GG_STATIC_ASSERT(offsetof(RectangleStruct, Width)  == 0x8);
GG_STATIC_ASSERT(offsetof(RectangleStruct, Height) == 0xC);
GG_STATIC_ASSERT(sizeof(RectangleStruct)           == 0x10);

// GLOBAL: GAMEMD 0x886FA0 / 0x886FA4 — the tactical view origin.
extern int DAT_00886FA0;
extern int DAT_00886FA4;



#include "../_layout/cell_class.h"
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);

#endif  // GG_MATCH_MAP_CELL_CLASS_MARK_REDRAW_METHODS_H
