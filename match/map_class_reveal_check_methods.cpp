// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x5865F0.

#include "map_class_reveal_check_methods.h"

// MapClass::operator[](CellStruct) as VC6 inlines it: the fixed 512x512
// bound, then the fallback cell with the coordinate stamped into it.
static inline CellClass_005865F0* CellAt_005865F0(Cell_005865F0 pos)
{
    int idx = (pos.Y << 9) + pos.X;
    if (idx >= 0 && idx < 0x40000) {
        CellClass_005865F0* pCell = MapInstance_005865F0.Cells[idx];
        if (pCell != 0)
            return pCell;
    }
    InvalidCell_005865F0.MapCoords = pos;
    return &InvalidCell_005865F0;
}

// FUNCTION: GAMEMD 0x5865F0  MapClass::RevealCheck
//
// Walk up the isometric column above a cell, one cell diagonal per two
// height levels: any cell whose level sits in the two-level band for that
// step is optionally redrawn, and the nearest techno on it is told the house
// has discovered it. A missing cell falls back to InvalidCell after stamping
// the coordinate into it. `this` is never read — the lookup and the redraw go
// through the global instance.
void Map_005865F0::RevealCheck(CellClass_005865F0* cell, House_005865F0* house, bool redraw)
{
    Cell_005865F0 pos = cell->MapCoords;

    for (int level = 1; level < 15; level += 2) {
        CellClass_005865F0* pCell = CellAt_005865F0(pos);

        if (pCell->Level >= level - 2 && pCell->Level <= level) {
            if (redraw)
                MapInstance_005865F0.FUN_006565A0(&pCell->MapCoords);

            Point_005865F0 offset;
            offset.X = 0;
            offset.Y = 0;
            Techno_005865F0* techno = pCell->FindTechnoNearestTo(offset, false, 0);
            if (techno != 0)
                (techno->*techno->Vptr->DiscoveredBy)(house);
        }

        pos.X++;
        pos.Y++;
    }
}
