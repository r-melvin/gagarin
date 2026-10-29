// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x487D00, 0x480A30),
//   cross-checked against YRpp (reconfirmed
//   numerically here). CellView_00480A30 derives AbstractClass.
//
// CellView_00480A30 — radiation / cell-coordinate helpers. This TU models only the
// members the two matched methods touch:
//   * MapCoords @0x24 (CellStruct, 4 bytes) — read by GetCellCoords
//   * RadLevel  @0xF0 (double)              — clamped by RadLevel_Decrease
#ifndef GG_MATCH_MAP_CELL_CLASS_RAD_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_RAD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4): the dword at [this+0x24].
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// Vector2D<int> — the sub-cell coordinate passed by const-ref to GetFloorHeight.
struct Point2D
{
    int X;  // +0x00
    int Y;  // +0x04
};

// Vector3D<int> — the world-coordinate out buffer filled by GetCellCoords.
#include "../_layout/coord_struct.h"

class CellView_00480A30
{
public:
    char       _base[0x24];                 // +0x00  AbstractClass (vtable + base)
    CellStruct MapCoords;                    // +0x24  read by GetCellCoords
    char       _pad28[0xF0 - 0x28];          // +0x28
    double     RadLevel;                     // +0xF0  clamped by RadLevel_Decrease

    // 0x47B3A0  CellView_00480A30::GetFloorHeight — retail callee we are NOT matching;
    // declared (no body) so cl emits a relocatable __thiscall call.
    int GetFloorHeight(Point2D const& subcoords) const;

    // 0x480A30
    CoordStruct* GetCellCoords(CoordStruct* pBuffer) const;
    // 0x487D00
    void RadLevel_Decrease(double amount);
};

GG_STATIC_ASSERT(offsetof(CellView_00480A30, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellView_00480A30, RadLevel) == 0xF0);

#endif  // GG_MATCH_MAP_CELL_CLASS_RAD_METHODS_H
