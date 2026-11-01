// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Control flow read from retail gamemd.exe v1.001 at 0x5862C0: a square of cells around a
//   centre is walked row by row; the first cell whose object list (+0xE4) is not empty ends
//   the search. __stdcall, RET 8, no receiver.
#include "cell_flag_search_shared.h"

// FUNCTION: GAMEMD 0x5862C0
// True when any cell within `radius` cells of `center` (a square) holds an object.
bool __stdcall FUN_005862C0(const CellStruct* center, int radius)
{
    for (int y = center->Y - radius; y <= center->Y + radius; y++) {
        for (int x = center->X - radius; x <= center->X + radius; x++) {
            CellStruct cell;
            cell.X = x;
            cell.Y = y;
            if (CellAt(&cell)->FirstObject) {
                return true;
            }
        }
    }
    return false;
}
