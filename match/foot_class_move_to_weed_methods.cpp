// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4DDB90 (name from the
//   YRpp method map).

#include "foot_class_move_to_weed_methods.h"

// Coordinate to cell (256 leptons per cell); inlined at the call site.
static inline Cell CellOfCoord(const CoordStruct& coord)
{
    Cell cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

// FUNCTION: GAMEMD 0x4DDB90
//
// Head for the nearest weed. Nothing happens while a destination is already
// set, or when the search within `radius` yields the sentinel cell. If the
// found cell is the one this object already stands on, report true without
// moving; otherwise set the cell as the destination and report false.
bool FootClass::MoveToWeed(int radius)
{
    if (this->Destination != 0)
        return false;

    Cell cell = this->FindWeedCell(radius);
    if (cell.X == DAT_008B3D88.X && cell.Y == DAT_008B3D88.Y)
        return false;

    Cell here = CellOfCoord(this->vf_18());
    if (cell.X == here.X && cell.Y == here.Y)
        return true;

    this->SetDestination(DAT_0087F7E8.FUN_005657A0(&cell), true);
    return false;
}
