// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Control flow read from retail gamemd.exe v1.001 at 0x578640: the map width at +0xF4, the cell
//   level (+0x11B) and slope index (+0x11C), and four diamond-edge tests against a rectangle of
//   four ints (X, Y, Width, Height).
#include "cell_flag_search_shared.h"

// FUNCTION: GAMEMD 0x578640
// True when `cell` lies inside the diamond-shaped screen footprint of the cell rectangle `rect`.
// With `useLevel` the cell's height (one more for a sloped cell near the upper edge) shifts
// the footprint.
bool MapView_578460::FUN_00578640(const int* rect, const CellStruct* cell, bool useLevel)
{
    int x = cell->X;
    int level = 0;
    int y = cell->Y;
    if (useLevel) {
        CellClass* c = CellAt(cell);
        level = c->Level;
        if (c->SlopeIndex != 0 && y + x < MapWidth + rect[1] * 2 + 4 + level) {
            level++;
        }
    }
    if (y + x > MapWidth + rect[1] * 2 + level
        && y + x <= MapWidth + (rect[3] + rect[1]) * 2 + 2 + level
        && x - y < (rect[2] + rect[0]) * 2 - MapWidth
        && y - x < MapWidth - rect[0] * 2) {
        return true;
    }
    return false;
}
