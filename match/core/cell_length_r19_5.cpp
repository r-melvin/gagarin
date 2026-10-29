// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the address below.
//   Address index: 0x6B1A70.

#include "../_layout/cell.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);

// FUNCTION: GAMEMD 0x6B1A70
// Length of a cell offset in cells, truncated: sqrt(X*X + Y*Y).
int __fastcall FUN_006B1A70(const CellStruct* cell)
{
    double y = cell->Y;
    double x = cell->X;
    return (int)FUN_004CAC40(x * x + y * y);
}
