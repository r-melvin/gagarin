// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x481810, 0x487630, 0x487950),
//   cross-checked against YRpp
//   (reconfirmed numerically here). CellView_00481810 derives AbstractClass.
//
// CellView_00481810 — shroud queries. GetNeighbourCell, ReduceShroudCounter and Unshroud now
// live on the canonical CellClass in tu050_cell_class.cpp; this view keeps the two
// location tests whose overlay-union Point2D cannot be built against the canonical
// Point2D (it has constructors, so it cannot be a union member):
//   * MapCoords     @0x24  (CellStruct, 4 bytes) — IsShrouded, FUN_004879B0
#ifndef GG_MATCH_MAP_CELL_CLASS_SHROUD_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_SHROUD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4): the dword at [this+0x24].
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// Vector2D<int> — the sub-cell coordinate passed by const-ref to GetFloorHeight.
// class (not struct): retail's type descriptor is .?AVPoint2D. Kept as a local plain view
// because the GetCellCoords-style bodies overlay it on a CellStruct in a union, which the
// canonical geometry2d.h Point2D (user constructors) cannot be a member of.
class Point2D
{
public:
    int X;  // +0x00
    int Y;  // +0x04
};

// Vector3D<int> — the world coordinate handed to MapClass::IsLocationShrouded.
#include "../_layout/coord_struct.h"

class CellView_00481810;

// MapClass singleton — only the two helpers IsShrouded / FUN_004879B0
// forward to, declared (no body) so cl emits relocatable __thiscall calls.
// The retail singleton object lives at the fixed address 0x87F7E8.
class MapView_5657A0_3
{
public:
    bool       IsLocationShrouded(CoordStruct const& coords) const; // 0x586360
    bool       FUN_005865E0(CoordStruct const& coords) const;       // 0x5865E0
};

class CellView_00481810
{
public:
    char       _base[0x24];                 // +0x00  AbstractClass (vtable + base)
    CellStruct MapCoords;                    // +0x24
    char       _pad28[0x148 - 0x28];         // +0x28

    // 0x47B3A0  CellView_00481810::GetFloorHeight — retail callee we are NOT matching;
    // declared (no body) so cl emits a relocatable __thiscall call.
    int GetFloorHeight(Point2D const& subcoords) const;

    // 0x487950
    bool IsShrouded() const;
    // 0x4879B0
    bool FUN_004879B0() const;
};

GG_STATIC_ASSERT(offsetof(CellView_00481810, MapCoords)     == 0x24);

#endif  // GG_MATCH_MAP_CELL_CLASS_SHROUD_METHODS_H
