// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// CellView_00481810 shroud location tests, ordered ascending by retail address.
#include "cell_class_shroud_methods.h"

// The retail MapClass singleton lives at this fixed address; calling through it
// makes cl emit `mov ecx,0x87F7E8` exactly as retail does.
#define MapInstance (reinterpret_cast<MapView_5657A0_3*>(0x87F7E8))

// FUNCTION: GAMEMD 0x487950  CellView_00481810::IsShrouded (__thiscall)
//   Builds the cell-centre world coord (MapCoords.*256+128, GetFloorHeight) and
//   asks the map whether that location is under shroud.
bool CellView_00481810::IsShrouded() const
{
    // MapCoords (a CellStruct) is materialised into the same stack slot that
    // later serves as the {128,128} sub-cell Point2D handed to GetFloorHeight —
    // retail reuses that slot, so model it with an explicit overlay union.
    union { CellStruct mc; Point2D pt; } u;
    u.mc = this->MapCoords;
    int x = u.mc.X * 256 + 128;
    int y = u.mc.Y * 256 + 128;
    u.pt.X = 128;
    u.pt.Y = 128;
    int z = this->GetFloorHeight(u.pt);

    CoordStruct crd;
    crd.X = x;
    crd.Y = y;
    crd.Z = z;
    return MapInstance->IsLocationShrouded(crd);
}

// FUNCTION: GAMEMD 0x4879B0  (__thiscall)
//   The same cell-centre coordinate as IsShrouded, handed to the map's other
//   location test (0x5865E0).
bool CellView_00481810::FUN_004879B0() const
{
    union { CellStruct mc; Point2D pt; } u;
    u.mc = this->MapCoords;
    int x = u.mc.X * 256 + 128;
    int y = u.mc.Y * 256 + 128;
    u.pt.X = 128;
    u.pt.Y = 128;
    int z = this->GetFloorHeight(u.pt);

    CoordStruct crd;
    crd.X = x;
    crd.Y = y;
    crd.Z = z;
    return MapInstance->FUN_005865E0(crd);
}
