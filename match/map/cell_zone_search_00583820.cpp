// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Full control flow read from retail gamemd.exe v1.001 at 0x583820.
//   The same two opposite-facing walks as 0x5835D0 run from the cell at
//   `start`; each walk's last qualifying cell becomes a candidate. The two
//   candidates, and the cells one and two steps beyond the first walk's
//   facing, are tried in order: the first inside the usable map area whose
//   zone word (five words per cell, clamped index) equals the requested zone
//   is returned.
#include "cell_flag_search_shared.h"

// A cell displaced by one of the eight one-cell steps.
inline CellStruct Displaced(const CellStruct& cell, const CellStruct& step)
{
    CellStruct result;
    result.X = cell.X + step.X;
    result.Y = cell.Y + step.Y;
    return result;
}

// FUNCTION: GAMEMD 0x583820
Cell MapView_578460::FUN_00583820(const CellStruct* start, int zoneWordOffset, int targetZone)
{
    Cell selected;
    CellClass* cell = CellAt(start);
    if ((cell->Flags & 0x100) == 0) {
        selected.X = cell->MapCoords.X;
        selected.Y = cell->MapCoords.Y;
        return selected;
    }

    unsigned int firstFacing = (cell->Flags & 0x800) ? 2 : 4;
    unsigned int secondFacing = (firstFacing - 4) & 7;
    CellClass* first = cell;
    CellClass* second = cell;
    CellStruct firstEnd = DAT_00ABD480;
    CellStruct secondEnd = DAT_00ABD480;

    for (;;) {
        if (first->Flags & 0x100) {
            first = first->GetNeighbourCell(firstFacing);
            if ((first->Flags & 0x100) == 0
                && (first->IsBridgeTile() || first->IsWoodBridgeTile())
                && first->LandType != 3)
                firstEnd = first->MapCoords;
        }
        if (second->Flags & 0x100) {
            second = second->GetNeighbourCell(secondFacing);
            if ((second->Flags & 0x100) == 0
                && (second->IsBridgeTile() || second->IsWoodBridgeTile())
                && second->LandType != 3)
                secondEnd = second->MapCoords;
        }
        if ((first->Flags & 0x100) == 0 && (second->Flags & 0x100) == 0)
            break;
    }

    unsigned int sideFacing = (firstFacing + 2) & 7;
    unsigned int backFacing = (firstFacing - 2) & 7;
    CellStruct candidates[6];
    candidates[0] = firstEnd;
    candidates[1] = Displaced(firstEnd, DAT_0089F688[sideFacing]);
    candidates[2] = Displaced(firstEnd, DAT_0089F688[backFacing]);
    candidates[3] = secondEnd;
    candidates[4] = Displaced(secondEnd, DAT_0089F688[sideFacing]);
    candidates[5] = Displaced(secondEnd, DAT_0089F688[backFacing]);

    for (int i = 0; i < 6; ++i) {
        if (FUN_00578460(&candidates[i], true)) {
            int zoneIndex = (MapWidth + MapHeight + 1) * candidates[i].Y + candidates[i].X;
            if (zoneIndex < 0)
                zoneIndex = 0;
            else if (zoneIndex >= CellCount)
                zoneIndex = CellCount - 1;
            if (ZoneWords[zoneWordOffset + zoneIndex * 5] == targetZone) {
                selected.X = candidates[i].X;
                selected.Y = candidates[i].Y;
                return selected;
            }
        }
    }
    selected.X = DAT_00ABD480.X;
    selected.Y = DAT_00ABD480.Y;
    return selected;
}
