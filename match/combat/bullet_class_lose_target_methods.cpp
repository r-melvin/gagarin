// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x468430.

#include "bullet_class_lose_target_methods.h"

// Coordinate to cell: a signed division by the 256 leptons per cell on each
// axis (`CDQ; AND EDX,0xFF; ADD; SAR 8`). Returned by value so that VC6
// materialises the hidden-pointer temporary retail has at [ESP+8].
static inline CellStruct Coord2Cell_00468430(const CoordStruct* coord)
{
    CellStruct cell;
    cell.X = (short)(coord->X / 256);
    cell.Y = (short)(coord->Y / 256);
    return cell;
}

// FUNCTION: GAMEMD 0x468430
//
// The bullet's target has gone away: fall back to the map cell the target
// stood on so the shot still lands there. While a scenario is being built,
// when the target was airborne, or when its cell is the null sentinel, the
// target is simply dropped.
//
// The cell is read out of the target's coordinates up front, before the
// tests, and the target pointer is re-read from the member for each call.
void BulletClass::LoseTarget()
{
    CoordStruct coord;
    CellStruct  cell = Coord2Cell_00468430(
        (this->Target->*this->Target->Vtbl->At_48)(&coord));

    if (DAT_00A8E7AC == 0
        && !(this->Target->*this->Target->Vtbl->At_54)()
        && (cell.X != DAT_0089DDF0.X || cell.Y != DAT_0089DDF0.Y)) {
        this->Target = MapInstance.GetCellAt(cell);
        return;
    }

    this->Target = 0;
}
