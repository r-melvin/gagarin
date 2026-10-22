// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x578390 and 0x578460.

#include "map_class_local_radar_methods.h"

// MapClass::operator[](CellStruct) as VC6 inlines it: the fixed 512x512
// bound through the global instance, then the fallback cell with the
// coordinate stamped into it.
static inline CellClass_00578390* CellAt_00578390(Cell_00578390* pos)
{
    int idx = (pos->Y << 9) + pos->X;
    if (idx >= 0 && idx < 0x40000) {
        CellClass_00578390* pCell = MapInstance_00578390.Cells[idx];
        if (pCell != 0)
            return pCell;
    }
    InvalidCell_00578390.MapCoords = *pos;
    return &InvalidCell_00578390;
}

// FUNCTION: GAMEMD 0x578460  MapClass::IsWithinUsableArea
//
// Is the cell inside the usable (visible) diamond of the map. The isometric
// diamond is tested on the two diagonals x+y and x-y against the visible
// rectangle scaled by two. With `checkLevel` the cell is looked up and its
// height level shifts the x+y band; a sloped cell just inside the top edge
// counts one level higher. `x` is declared before `y` so the y + x sums
// take y as the LEA base, as retail has them.
bool Map_00578390::IsWithinUsableArea(Cell_00578390* cell, bool checkLevel)
{
    int level = 0;
    int x = cell->X;
    int y = cell->Y;

    if (checkLevel) {
        CellClass_00578390* pCell = CellAt_00578390(cell);
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
