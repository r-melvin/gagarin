// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4FBF60: on the house `[ESI+0x34]` (the house type)
//   and `[ESI+0x53DC]` (the flag cell, pushed to 0x4FBE40 and stored at the
//   end); on the type `[EAX+0xB8]` (pushed to 0x483410); the map singleton
//   as the immediate `MOV ECX,0x87F7E8` feeding CALL 0x568300
//   (CoordinatesLegal, one pushed cell pointer, AL), CALL 0x5657A0
//   (GetCellAt, one pushed cell pointer) and CALL 0x56DC20 (NearByLocation,
//   fifteen pushed arguments: out pointer, cell pointer, 1, -1, 0, 0, 1, 1,
//   0, 0, 0, 1, close-to pointer, 0, 0); the 4-byte sentinel at 0xA8EF98
//   compared word-wise (`CMP AX,[0xA8EF98]` / `CMP CX,[0xA8EF9A]`); and the
//   cell's own 0x483410 (__thiscall, one pushed int, AL). The cell copy
//   lives in the first parameter's home slot ([ESP+0x14]) and the zeroed
//   close-to cell in the second's ([ESP+0x58]/[ESP+0x5A]); the
//   NearByLocation out buffer is the one real local. Names cross-checked
//   against YRpp HouseClass::DroppedFlag / UpdateFlagCoords,
//   MapClass::CoordinatesLegal / NearByLocation
//   and the sibling match/economy/house_class_flag_methods.h (Type @0x34,
//   the +0x53DC slot, ColorSchemeIndex @0xB8), re-derived here.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_DROPPED_FLAG_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_DROPPED_FLAG_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/cell.h"
#include "../_layout/map_0087f7e8.h"


#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_DROPPED_FLAG_METHODS_H
