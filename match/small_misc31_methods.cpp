// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x413A30.

#include "small_misc31_methods.h"

// FUNCTION: GAMEMD 0x413A30
// Lepton coordinates to cell coordinates. The divide is signed - the
// `CDQ; AND EDX,0xFF; ADD; SAR 8` idiom, not a bare shift - so negative
// coordinates round toward zero rather than away from it.
CellPair Coord2i::FUN_00413A30() const
{
    CellPair result;

    result.x = (short)(X / 256);
    result.y = (short)(Y / 256);

    return result;
}
