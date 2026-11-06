// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and call shapes read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x74E930: `LEA
//   EBP,[ECX+0xF8]` (the monster's cell coordinate, pushed by address into
//   `MOV ECX,0x87F7E8; CALL 0x5657A0`, MapClass::GetCellAt), the cell's
//   `[ESI+0x44] = 0x7E` / `-1` (overlay type index) and byte `[ESI+0x11E] =
//   0` (overlay data), `PUSH -1; CALL 0x47D2B0` (RecalcAttributes), `PUSH i;
//   CALL 0x481810` (GetNeighbourCell) over eight facings with the signed
//   `i % 2` test, the 5x5 walk building `{X+dx, Y+dy}` as two words at
//   `[ESP+0x10]`, copying the dword to `[ESP+0x14]` and pushing that address
//   (the inlined by-value helper plus the const-ref temporary, the same shape
//   as the matched 0x481810), CALL 0x485AF0 on each cell, `CALL 0x74E6B0` on
//   `this`, `PUSH EBP; MOV ECX,0x87F7E8; CALL 0x56D460` and `CALL 0x584550`,
//   and the byte `[ESI+0x100] = 1`. YRpp names only
//   VeinholeMonsterClass::Recalculate, RecalculateSpread
//   @0x74E6B0, CellClass::RecalcAttributes @0x47D2B0, GetNeighbourCell
//   @0x481810, MapClass::GetCellAt @0x5657A0, ResetZones @0x56D460,
//   RecalculateSubZones @0x584550.
#ifndef GG_MATCH_MAP_VEINHOLE_MONSTER_RECALCULATE_METHODS_H
#define GG_MATCH_MAP_VEINHOLE_MONSTER_RECALCULATE_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4).
#include "_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// Displace a cell coordinate; returned by value so the caller binds a
// const-ref temporary to the copy, exactly as retail's frame shows.
static inline CellStruct CellOffset(CellStruct const& c, int dx, int dy)
{
    CellStruct ret;
    ret.X = c.X + dx;
    ret.Y = c.Y + dy;
    return ret;
}

#include "_layout/cell_class.h"
#include "_layout/map_0087f7e8.h"

#include "_layout/veinhole_monster_class.h"
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, Position) == 0xF8);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, IsDead) == 0x100);

#endif  // GG_MATCH_MAP_VEINHOLE_MONSTER_RECALCULATE_METHODS_H
