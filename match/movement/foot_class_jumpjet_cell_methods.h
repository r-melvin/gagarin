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

class FootClass;

#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

class CellClass
{
public:
    char       _pad00[0xE0];   // +0x0000
    FootClass* Jumpjet;        // +0x00E0
};
GG_STATIC_ASSERT(offsetof(CellClass, Jumpjet) == 0xE0);

class MapClass
{
public:
    CellClass* GetCellAt(CellStruct const& mapCoords) const;   // GAMEMD 0x5657A0
};

// GLOBAL: GAMEMD 0x0087F7E8 — the MapClass instance (an object, not a pointer:
// retail loads its address as the immediate `MOV ECX,0x87F7E8`).
extern MapClass   MapInstance;
// GLOBAL: GAMEMD 0x008B3D88 — the "no cell" CellStruct sentinel.
extern CellStruct NoCell;

class FootClass
{
public:
    char       _pad000[0x564];   // +0x0000
    CellStruct JumpjetCoords;    // +0x0564

    void Jumpjet_OccupyCell(CellStruct coords);   // GAMEMD 0x4E00B0
};
GG_STATIC_ASSERT(offsetof(FootClass, JumpjetCoords) == 0x564);

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_JUMPJET_CELL_METHODS_H
