// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x586780.

#include "map_class_area_free_methods.h"

// MapClass::GetCellAt written out inline by retail: the flat-array lookup,
// falling back to InvalidCell stamped with the requested coordinate.
inline CellClass* Map_00586780::GetCellAt(CellStruct c)
{
    int idx = (c.Y << 9) + c.X;
    if (idx >= 0 && idx < 0x40000) {
        CellClass* p = DAT_0087F924[idx];
        if (p) {
            return p;
        }
    }
    InvalidCell.MapCoords = c;
    return &InvalidCell;
}

// FUNCTION: GAMEMD 0x586780  MapClass::IsAreaFree (__thiscall, ret 0x8)
//
// Sweep every cell of `rect` (the cell lookup is MapClass::GetCellAt written
// out inline, falling back to InvalidCell stamped with the coordinate) and
// refuse the area when any cell holds a terrain object, has the `bit` flag
// set in its +0xDC word, carries an overlay, has something at +0x4C, is
// sloped, or holds a building. A clean sweep defers to InLocalRadar(rect).
bool Map_00586780::IsAreaFree(Rect_00586780* rect, int bit)
{
    int mask;
    if (bit != -1) {
        mask = 1 << bit;
    } else {
        mask = 0;
    }

    for (int x = rect->X; x < rect->X + rect->Width; ++x) {
        for (int y = rect->Y; y < rect->Y + rect->Height; ++y) {
            CellStruct c;
            c.X = (short)x;
            c.Y = (short)y;

            CellClass* cell = this->GetCellAt(c);

            if (cell->GetTerrain(false)
                || (mask & cell->BaseSpacerOfHouses)
                || cell->OverlayTypeIndex != -1
                || cell->Passability
                || cell->SlopeIndex
                || cell->GetBuilding()) {
                return false;
            }
        }
    }

    return this->InLocalRadar(rect, true);
}
