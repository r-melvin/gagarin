// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x487D70. The jumpjet
//   occupant slot is CellClass +0xE0; 0x4E00B0 is FootClass::Jumpjet_OccupyCell
//   and 0x0089E748 the coordinate global used when clearing.
#ifndef GG_MATCH_MAP_CELL_CLASS_JUMPJET_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_JUMPJET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4); passed by value as a single dword.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// FootClass::Jumpjet_OccupyCell @0x4E00B0 — __fastcall with the object in ECX
// and the cell coordinate pushed. Declared only; relocation-normalised.
class ObjectClass;
void Jumpjet_OccupyCell(ObjectClass* object, CellStruct coords);

// GLOBAL: GAMEMD 0x0089E748 — the coordinate handed over when a cell releases
// its jumpjet occupant.
extern CellStruct JumpjetClearCoords;

#include "../_layout/cell_class.h"
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, Jumpjet)   == 0xE0);

#endif  // GG_MATCH_MAP_CELL_CLASS_JUMPJET_METHODS_H
