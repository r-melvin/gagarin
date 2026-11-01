// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001, REA
// ev_13702d519d31100fade6558f5dbcac0d871040b489a1fc592df21c9d696034fb
// and ev_bc4a650047f273aca945c2a104c644f3ae01be8472cff2e0147aacb27d12eb11.
// Complete entry disassembly establishes both __fastcall coordinate inputs,
// the lookup bounds, fallback write, and CellClass field +0x44 comparisons.
#include "cell_type_predicates_00580b20.h"

static inline NeighborCell_0057CBE0* LookupCell_00580B20(NeighborCoord_0057CBE0* cell)
{
    int index = cell->Y * 512 + cell->X;
    if (index >= 0 && index < 0x40000) {
        NeighborCell_0057CBE0* found = NeighborCells[index];
        if (found) return found;
    }
    NeighborFallback.Coordinates = *cell;
    return &NeighborFallback;
}

// FUNCTION: GAMEMD 0x580B20
int FUN_00580B20(NeighborCoord_0057CBE0* cell)
{
    int type = LookupCell_00580B20(cell)->At_44;
    return type >= 0x4A && type <= 0x65;
}

// FUNCTION: GAMEMD 0x580B70
int FUN_00580B70(NeighborCoord_0057CBE0* cell)
{
    int type = LookupCell_00580B20(cell)->At_44;
    return type >= 0xCD && type <= 0xE8;
}
