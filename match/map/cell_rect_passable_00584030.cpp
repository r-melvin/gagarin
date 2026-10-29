// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Control flow read from retail gamemd.exe v1.001 at 0x584030: a rectangle of cells (X, Y,
//   Width, Height as ints) is walked row by row; every cell's Passability (+0x4C) must be 3 or 4.
//   __stdcall, RET 4, no receiver.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
#include "cell_flag_search_shared.h"
#include "../_layout/geometry2d.h"

// FUNCTION: GAMEMD 0x584030
// True when every cell of the rectangle has passability 3 or 4.
bool __stdcall FUN_00584030(const RectangleStruct* rect)
{
    int height = rect->Height;
    int width = rect->Width;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            CellStruct cell;
            int cx = rect->X + x;
            int cy = rect->Y + y;
            cell.Y = cy;
            cell.X = cx;
            int passability = CellAt(&cell)->Passability;
            if (passability != 4 && passability != 3) {
                return false;
            }
        }
    }
    return true;
}
