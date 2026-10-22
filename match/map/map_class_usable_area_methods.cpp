// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x578540 (name from the
//   YRpp method map).

#include "map_class_usable_area_methods.h"

// FUNCTION: GAMEMD 0x578540
//
// Is the cell inside the usable (visible) diamond of the map. The isometric
// diamond is tested on the two diagonals x+y and x-y against the visible
// rectangle scaled by two. With `checkLevel` the cell's height level shifts
// the x+y band, and a sloped cell just inside the top edge counts one level
// higher.
bool MapClass::IsWithinUsableArea(Cell_00578540* pCell, bool checkLevel) const
{
    int x = pCell->X;
    int y = pCell->Y;
    int level = 0;

    if (checkLevel) {
        level = pCell->Level;
        if (pCell->SlopeIndex != 0) {
            if (y + x < this->MapRectWidth + this->VisibleRectY * 2 + 4 + level)
                level = level + 1;
        }
    }

    if (y + x > this->MapRectWidth + this->VisibleRectY * 2 + level
        && y + x <= this->MapRectWidth
                    + (this->VisibleRectHeight + this->VisibleRectY) * 2 + 2 + level
        && x - y < (this->VisibleRectWidth + this->VisibleRectX) * 2 - this->MapRectWidth
        && y - x < this->MapRectWidth - this->VisibleRectX * 2)
        return true;
    return false;
}
