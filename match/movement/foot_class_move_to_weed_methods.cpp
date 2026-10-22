// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4DDB90 (name from the
//   YRpp method map).

#include "foot_class_move_to_weed_methods.h"

// FUNCTION: GAMEMD 0x4DDB90
//
// Head for the nearest weed. Nothing happens while a destination is already
// set, or when the search within `radius` yields the sentinel cell. If the
// found cell is the one this object already stands on, report true without
// moving; otherwise set the cell as the destination and report false.
bool FootWeed::MoveToWeed(int radius)
{
    if (this->Destination != 0)
        return false;

    Cell_004DDB90 cell = this->FindWeedCell(radius);
    if (cell.X == DAT_008B3D88.X && cell.Y == DAT_008B3D88.Y)
        return false;

    CoordStruct   crd;
    CoordStruct*  p = (this->*(*(WeedVtbl**)this)->GetCoords)(&crd);
    Cell_004DDB90 here;
    here.X = (short)(p->X / 256);
    here.Y = (short)(p->Y / 256);
    if (cell.X == here.X && cell.Y == here.Y)
        return true;

    (this->*(*(WeedVtbl**)this)->SetDestination)(DAT_0087F7E8.GetCellAt(cell), true);
    return false;
}
