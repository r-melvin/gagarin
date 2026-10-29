// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x4E00B0. 0x005657A0 is MapClass::GetCellAt and
//   0x0087F7E8 the MapClass instance, both already bound in
//   cell_class_shroud_methods.h; CellClass::Jumpjet @0xE0 comes from
//   cell_class_jumpjet_methods.h, where TryAssignJumpjet calls *this* function.
//
// The pair at 0x008B3D88/0x008B3D8A is a CellStruct sentinel meaning "no cell".
// Retail compares against it a word at a time, which is what pins the members
// as shorts.
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_JUMPJET_CELL_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_JUMPJET_CELL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"   // FootClass::CurrentJumpjetMapCoords @0x564, CellStruct
#include "../_layout/cell_class.h"   // CellClass::Jumpjet @0xE0

class MapView_5657A0_4
{
public:
    CellClass* GetCellAt(CellStruct const& mapCoords) const;   // GAMEMD 0x5657A0
};

// GLOBAL: GAMEMD 0x0087F7E8 — the MapClass instance (an object, not a pointer:
// retail loads its address as the immediate `MOV ECX,0x87F7E8`).
extern MapView_5657A0_4   MapInstance;
// GLOBAL: GAMEMD 0x008B3D88 — the "no cell" CellStruct sentinel.
extern CellStruct NoCell;

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_JUMPJET_CELL_METHODS_H
