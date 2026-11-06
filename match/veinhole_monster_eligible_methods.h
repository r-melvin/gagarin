// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x74D670: the ScenarioInit gate 0xA8E7AC,
//   VeinholeMonsterClass::Array Items 0xB1D294 / Count 0xB1D2A0 with each
//   monster's cell shorts at +0xF8 / +0xFA, MapClass::GetCellAt at 0x5657A0
//   on the map object 0x87F7E8, and the cell's Level (+0x11B, signed),
//   SlopeIndex (+0x11C) and LandType (+0xEC). YRpp
//   names IsCellEligibleForVeinHole and the array.
#ifndef GG_MATCH_MAP_VEINHOLE_MONSTER_ELIGIBLE_METHODS_H
#define GG_MATCH_MAP_VEINHOLE_MONSTER_ELIGIBLE_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/cell_class.h"

#include "_layout/cell.h"

// GLOBAL: GAMEMD 0xA8E7AC — Unsorted::ScenarioInit.
extern int DAT_00A8E7AC;

struct Monster_0074D670
{
    char _pad0000[0xF8];    // +0x0000
    CellStruct Cell;     // +0x00F8
};
GG_STATIC_ASSERT(offsetof(Monster_0074D670, Cell) == 0xF8);

// GLOBAL: GAMEMD 0xB1D294 — VeinholeMonsterClass::Array.Items.
extern Monster_0074D670** DAT_00B1D294;
// GLOBAL: GAMEMD 0xB1D2A0 — VeinholeMonsterClass::Array.Count.
extern int DAT_00B1D2A0;


struct Map_0074D670
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass* GetCellAt(const CellStruct* cell);

    // MapClass::operator[](CellStruct) as inlined: the by-value cell is copied
    // into the argument temporary and handed on by address.
    CellClass* Cell(CellStruct cell) { return GetCellAt(&cell); }
};
// GLOBAL: GAMEMD 0x87F7E8 — the map instance.
extern Map_0074D670 MapInstance_0074D670;

// The owning class. Nothing at this address touches an instance, so no layout
// is recovered here; the struct exists so the routine is spelled as the static
// member it is rather than as a free function, and so the next address on this
// class has somewhere to attach.
#include "_layout/veinhole_monster_class.h"

#endif  // GG_MATCH_MAP_VEINHOLE_MONSTER_ELIGIBLE_METHODS_H
