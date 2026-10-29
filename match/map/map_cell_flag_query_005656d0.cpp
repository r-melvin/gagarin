// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5656D0: cell array at map+0x13C,
//   cell index (Y << 9) + X bounded by 0x40000, InvalidCell at 0xABDC50 and the cell flag
//   dword at cell+0x12C.
//
// Address index: 0x5656D0

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"
#include "../_layout/cell_class.h"

// Only the cell array of the map is read.
struct MapView_005656D0
{
    char        _pad0[0x13C];
    CellClass** Cells;  // +0x13C

    // The live cell at `cell`, or the invalid cell stamped with the coordinate.
    CellClass* GetCell(CellStruct cell);
};
GG_STATIC_ASSERT(offsetof(MapView_005656D0, Cells) == 0x13C);

// GLOBAL: GAMEMD 0xABDC50
extern CellClass InvalidCell;

inline CellClass* MapView_005656D0::GetCell(CellStruct cell)
{
    int idx = (cell.Y << 9) + cell.X;
    CellClass* pCell;
    if (idx < 0 || idx >= 0x40000 || (pCell = Cells[idx]) == 0) {
        InvalidCell.MapCoords = cell;
        pCell = &InvalidCell;
    }
    return pCell;
}

// FUNCTION: GAMEMD 0x5656D0
// Returns bit 3 of the flags of the cell at `cell`.
bool __stdcall FUN_005656D0(MapView_005656D0* map, CellStruct cell)
{
    CellStruct at;
    at.Y = cell.Y;
    at.X = cell.X;
    return (map->GetCell(at)->AltFlags >> 3) & 1;
}
