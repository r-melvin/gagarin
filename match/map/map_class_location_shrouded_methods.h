// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and the frame read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x586360: the level divisor `IDIV [0xABDE88]`,
//   the two `CDQ; AND EDX,0xFF; ADD; SAR 8` signed divides by 256 into the
//   word pair at `[ESP+4]`/`[ESP+6]`, the level-adjusted pair stored back
//   into the parameter's home slot (`[ESP+0x10]`/`[ESP+0x12]`), the flat
//   index `SHL 9; ADD` bounds-checked against 0x40000 and read from the item
//   base `[0x87F924]`, the miss fallback stamping `[0xABDC74]` (InvalidCell
//   0xABDC50, MapCoords @0x24) and the shroud bit `TEST byte [cell+0x12C],8`.
//   0x481810 is CellClass::GetNeighbourCell, matched in
//   match/map/cell_class_shroud_methods.cpp. `this` is unused (ECX never
//   read). Names cross-checked against YRpp.
#ifndef GG_MATCH_MAP_MAP_CLASS_LOCATION_SHROUDED_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_LOCATION_SHROUDED_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellStruct { short X; short Y; };
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

struct CoordStruct { int X; int Y; int Z; };
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

struct CellClass
{
    char       _pad000[0x24];           // +0x0000
    CellStruct MapCoords;               // +0x0024
    char       _pad028[0x12C - 0x28];   // +0x0028
    int        AltFlags;                // +0x012C  bit 3 = shrouded

    // FUNCTION: GAMEMD 0x481810 (decl; reloc) — CellClass::GetNeighbourCell.
    CellClass* GetNeighbourCell(int facing) const;
};
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, AltFlags)  == 0x12C);

// GLOBAL: GAMEMD 0xABDE88 — height of one cell level in leptons.
extern int LevelHeight_00586360;
// GLOBAL: GAMEMD 0x87F924 — MapClass::Instance.Cells item base.
extern CellClass** Cells_00586360;
// GLOBAL: GAMEMD 0xABDC50 — MapClass::InvalidCell (MapCoords at 0xABDC74).
extern CellClass   InvalidCell_00586360;

struct MapClass
{
    // FUNCTION: GAMEMD 0x586360 — MapClass::IsLocationShrouded.
    bool IsLocationShrouded(CoordStruct const& coords) const;
};

#endif  // GG_MATCH_MAP_MAP_CLASS_LOCATION_SHROUDED_METHODS_H
