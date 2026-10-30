// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Full control flow read from retail gamemd.exe v1.001 at 0x5835D0.
//   Starting at the cell for `origin`, two walks follow neighbours in two
//   opposite facings until each reaches a cell whose flag bit 8 is clear.
//   The last qualifying cell of each walk is a candidate; the candidate that
//   lies in the usable map area and is nearer to `comparison` is returned.
//   The result is written through a hidden pointer (the type has a
//   constructor), and the function is __stdcall with RET 0xC.
#include "cell_flag_search_shared.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- square root, __cdecl.
double __cdecl FUN_004CAC40(double value);
// LIBRARY: GAMEMD 0x7C5F00 -- the double-to-int conversion behind (int).

// FUNCTION: GAMEMD 0x5835D0
Cell __stdcall FUN_005835D0(const CellStruct* origin, const CellStruct* comparison)
{
    Cell selected;
    CellClass* cell = CellAt(origin);
    if ((cell->Flags & 0x100) == 0) {
        selected.X = cell->MapCoords.X;
        selected.Y = cell->MapCoords.Y;
        return selected;
    }

    unsigned int firstFacing = (cell->Flags & 0x800) ? 2 : 4;
    unsigned int secondFacing = (firstFacing - 4) & 7;
    CellStruct firstEnd = DAT_00ABD480;
    CellStruct secondEnd = DAT_00ABD480;
    CellClass* first = cell;
    CellClass* second = cell;

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

    selected.X = DAT_00ABD480.X;
    selected.Y = DAT_00ABD480.Y;
    if (DAT_0087F7E8.FUN_00578460(&firstEnd, true)) {
        selected.X = firstEnd.X;
        selected.Y = firstEnd.Y;
    }
    if (DAT_0087F7E8.FUN_00578460(&secondEnd, true)) {
        if (selected.X == DAT_00ABD480.X && selected.Y == DAT_00ABD480.Y) {
            selected.X = secondEnd.X;
            selected.Y = secondEnd.Y;
        } else {
            short firstDx = selected.X - comparison->X;
            short firstDy = selected.Y - comparison->Y;
            short secondDx = secondEnd.X - comparison->X;
            short secondDy = secondEnd.Y - comparison->Y;
            short firstDistance = (int)FUN_004CAC40(
                (double)firstDx * firstDx + (double)firstDy * firstDy);
            short secondDistance = (int)FUN_004CAC40(
                (double)secondDx * secondDx + (double)secondDy * secondDy);
            if (secondDistance < firstDistance) {
                selected.X = secondEnd.X;
                selected.Y = secondEnd.Y;
            }
        }
    }

    return selected;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABDC74
CellStruct DAT_00ABDC74;
// END defined globals
