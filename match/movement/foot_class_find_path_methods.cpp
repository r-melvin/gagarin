// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4CBBA0.

#include "foot_class_find_path_methods.h"

// FUNCTION: GAMEMD 0x4CBBA0
//
// Ask the A* pathfinder for a route from this object's current cell to `dest`.
// The start cell is the object's coordinate (slot +0x4C) divided down to cell
// units, then advanced along the first `dirCount` entries of PathDirections by
// the walker at 0x429780; a null `buffer` returns 0 before the walk. The third
// and fourth arguments are not read.
void* FootPath::FindPath(Cell_004CBBA0* dest, int* buffer, int unused1, int unused2,
                         int dirCount, int mode)
{
    CoordStruct   crd;
    CoordStruct*  p = (this->*(*(PathVtbl**)this)->GetCoords)(&crd, 0);
    Cell_004CBBA0 r;

    r.X = (short)(p->X / 256);
    r.Y = (short)(p->Y / 256);

    Cell_004CBBA0 cell = r;

    if (buffer == 0) {
        return 0;
    }

    cell = FUN_00429780(&cell, dirCount, this->PathDirections);

    return DAT_0087E8B8.FindPath(&cell, dest, this, buffer, -1, -1, mode);
}
