// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x586780.
//   Offsets read off the retail exe at 0x586780: the rectangle is read as `[EBX]`, `[EBX+4]`, `[EBX+8]`, `[EBX+0xC]`
//   (X, Y, Width, Height); the cell index is `(short)Y << 9 + (short)X` bounded by 0x40000 into the cell table at
//   0x87F924 with the fallback cell 0xABDC50 whose MapCoords (+0x24 = 0xABDC74) receive the requested coordinate; on the
//   cell `[ESI+0xDC]` (masked by 1 << bit), `[ESI+0x44]` (OverlayTypeIndex, -1 = none), `[ESI+0x4C]` and the byte
//   `[ESI+0x11C]` (SlopeIndex). Calls: 0x47C550 with one pushed 0 and 0x47C520 with none (both __thiscall on the cell),
//   and 0x578390 on the map with (rect, 1).

#include "ui_display_chain.h"
#include "_layout/cell_class.h"

// MapClass::GetCellAt written out inline by retail: the flat-array lookup,
// falling back to InvalidCell stamped with the requested coordinate.
static inline CellClass* CellAt_00586780(CellStruct c)
{
    int idx = (c.Y << 9) + c.X;
    if (idx >= 0 && idx < 0x40000) {
        CellClass* p = Map_0087F7E8.Owned[idx];
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
bool MapClass::IsAreaFree(RectangleStruct* rect, int bit)
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

            CellClass* cell = CellAt_00586780(c);

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

    return this->FUN_00578390(rect, true);
}
