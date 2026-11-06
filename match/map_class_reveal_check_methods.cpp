// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x5865F0.
//   Layout read off the retail exe at 0x5865F0: the cell's MapCoords at +0x24 and Level at +0x11B (MOVSX), the cell
//   array at 0x87F924 (map instance 0x87F7E8 + 0x13C) bounded by the constant 0x40000, the fallback cell at 0xABDC50
//   with its coords at 0xABDC74, the techno vtable slot +0x198 (vf_102) with one pushed argument, and the callees
//   0x6565A0 (map singleton, CellStruct*) and 0x47C3D0 (cell, Point2D const&, bool, exclude).

#include "ui_display_chain.h"
#include "_layout/cell_class.h"
#include "_layout/object_class.h"

// MapClass::operator[](CellStruct) as VC6 inlines it: the fixed 512x512
// bound, then the fallback cell with the coordinate stamped into it.
static inline CellClass* CellAt_005865F0(CellStruct pos)
{
    int idx = (pos.Y << 9) + pos.X;
    if (idx >= 0 && idx < 0x40000) {
        CellClass* pCell = Map_0087F7E8.Owned[idx];
        if (pCell != 0)
            return pCell;
    }
    InvalidCell.MapCoords = pos;
    return &InvalidCell;
}

// FUNCTION: GAMEMD 0x5865F0  MapClass::RevealCheck
//
// Walk up the isometric column above a cell, one cell diagonal per two
// height levels: any cell whose level sits in the two-level band for that
// step is optionally redrawn, and the nearest techno on it is told the house
// has discovered it. A missing cell falls back to InvalidCell after stamping
// the coordinate into it. `this` is never read — the lookup and the redraw go
// through the global instance.
void MapClass::RevealCheck(CellClass* cell, HouseClass* house, bool redraw)
{
    CellStruct pos = cell->MapCoords;

    for (int level = 1; level < 15; level += 2) {
        CellClass* pCell = CellAt_005865F0(pos);

        if (pCell->Level >= level - 2 && pCell->Level <= level) {
            if (redraw)
                Map_0087F7E8.FUN_006565A0(&pCell->MapCoords);

            Point2D offset;
            offset.X = 0;
            offset.Y = 0;
            ObjectClass* techno = pCell->FindTechnoNearestTo(&offset, false, 0);
            if (techno != 0)
                techno->vf_102(house);
        }

        pos.X++;
        pos.Y++;
    }
}
