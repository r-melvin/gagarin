// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x481810, 0x487630, 0x487950),
//   cross-checked against YRpp
//   (reconfirmed numerically here). CellClass derives AbstractClass.
//
// CellClass — shroud / neighbour helpers. This TU models only the members the
// three matched methods touch:
//   * MapCoords     @0x24  (CellStruct, 4 bytes) — IsShrouded, GetNeighbourCell
//   * AltFlags      @0x12c (int)                  — ReduceShroudCounter
//   * ShroudCounter @0x130 (int)                  — ReduceShroudCounter
//   * Flags         @0x140 (int)                  — ReduceShroudCounter
#ifndef GG_MATCH_MAP_CELL_CLASS_SHROUD_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_SHROUD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4): the dword at [this+0x24].
// Vector2D<short>::operator+ returns a temporary by value — GetNeighbourCell
// passes MapCoords+AdjacentCell as that prvalue, so model the operator.
struct CellStruct
{
    short X;  // +0x00
    short Y;  // +0x02

    CellStruct operator+(CellStruct const& a) const
    {
        CellStruct ret;
        ret.X = X + a.X;
        ret.Y = Y + a.Y;
        return ret;
    }
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// Vector2D<int> — the sub-cell coordinate passed by const-ref to GetFloorHeight.
struct Point2D
{
    int X;  // +0x00
    int Y;  // +0x04
};

// Vector3D<int> — the world coordinate handed to MapClass::IsLocationShrouded.
struct CoordStruct
{
    int X;  // +0x00
    int Y;  // +0x04
    int Z;  // +0x08
};

class CellClass;

// MapClass singleton — only the two helpers GetNeighbourCell / IsShrouded
// forward to, declared (no body) so cl emits relocatable __thiscall calls.
// The retail singleton object lives at the fixed address 0x87F7E8.
class MapClass
{
public:
    CellClass* GetCellAt(CellStruct const& mapCoords) const;        // 0x5657A0
    bool       IsLocationShrouded(CoordStruct const& coords) const; // 0x586360
    bool       FUN_005865E0(CoordStruct const& coords) const;       // 0x5865E0
};

// AdjacentCell[FacingType] — the static {dX,dY} step table at 0x89F688.
// Referenced by absolute address so cl emits the same displacement retail does.
#define AdjacentCell (reinterpret_cast<CellStruct const*>(0x89F688))

class CellClass
{
public:
    char       _base[0x24];                 // +0x00  AbstractClass (vtable + base)
    CellStruct MapCoords;                    // +0x24
    char       _pad28[0x12C - 0x28];         // +0x28
    int        AltFlags;                     // +0x12C
    int        ShroudCounter;                // +0x130
    char       _pad134[0x140 - 0x134];       // +0x134
    int        Flags;                        // +0x140

    // 0x47B3A0  CellClass::GetFloorHeight — retail callee we are NOT matching;
    // declared (no body) so cl emits a relocatable __thiscall call.
    int GetFloorHeight(Point2D const& subcoords) const;

    // 0x481810
    CellClass* GetNeighbourCell(int facing) const;
    // 0x4876F0
    void Unshroud();
    // 0x487630
    void ReduceShroudCounter();
    // 0x487950
    bool IsShrouded() const;
    // 0x4879B0
    bool FUN_004879B0() const;
};

GG_STATIC_ASSERT(offsetof(CellClass, MapCoords)     == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, AltFlags)      == 0x12C);
GG_STATIC_ASSERT(offsetof(CellClass, ShroudCounter) == 0x130);
GG_STATIC_ASSERT(offsetof(CellClass, Flags)         == 0x140);

#endif  // GG_MATCH_MAP_CELL_CLASS_SHROUD_METHODS_H
