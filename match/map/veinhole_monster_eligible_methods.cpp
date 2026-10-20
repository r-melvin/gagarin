// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x74D670.

#include <stdlib.h>
#include "veinhole_monster_eligible_methods.h"

// FUNCTION: GAMEMD 0x74D670  VeinholeMonsterClass::IsCellEligibleForVeinHole
//
// During scenario setup anything goes. Otherwise the cell must be at least
// three cells from every existing veinhole, sit above ground level, and the
// 3x3 block around it must be flat, of land type zero and all at that level.
bool __fastcall VeinholeMonsterClass::IsCellEligibleForVeinHole(const Cell_0074D670* cell)
{
    if (DAT_00A8E7AC > 0)
        return true;

    for (int i = DAT_00B1D2A0 - 1; i >= 0; --i) {
        Monster_0074D670* monster = DAT_00B1D294[i];
        if (abs(cell->X - monster->Cell.X) < 3 && abs(cell->Y - monster->Cell.Y) < 3)
            return false;
    }

    int level = MapInstance_0074D670.GetCellAt(cell)->Level;
    if (level < 1)
        return false;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            Cell_0074D670 spot;
            spot.X = cell->X + dx;
            spot.Y = cell->Y + dy;
            CellClass_0074D670* c = MapInstance_0074D670.Cell(spot);
            if (c->SlopeIndex != 0 || c->LandType != 0 || c->Level != level)
                return false;
        }
    }
    return true;
}
