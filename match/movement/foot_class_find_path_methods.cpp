// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4CBBA0.

#include "foot_class_find_path_methods.h"

// Coordinate to cell (256 leptons per cell); inlined at the call site.
static inline Cell CellOfCoord(const CoordStruct& coord)
{
    Cell cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

// FUNCTION: GAMEMD 0x4CBBA0
//
// Ask the A* pathfinder for a route from this object's current cell to `dest`.
// The start cell is the object's coordinate (slot +0x4C) divided down to cell
// units, then advanced along the first `dirCount` entries of PathDirections by
// the walker at 0x429780; a null `buffer` returns 0 before the walk. The third
// and fourth arguments are not read.
void* FootClass::FindPath(Cell* dest, int* buffer, int unused1, int unused2,
                          int dirCount, int mode)
{
    Cell cell = CellOfCoord(this->vf_19(0));
    if (buffer == 0) {
        return 0;
    }
    cell = FUN_00429780(&cell, dirCount, this->PathDirections);
    return DAT_0087E8B8.FindPath(&cell, dest, this, buffer, -1, -1, mode);
}
