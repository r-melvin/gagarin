// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Offsets reconfirmed
//   numerically from the disassembly at the listed address.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x565730  MapClass::GetTargetCell  (__thiscall)

#include "map_class_target_methods.h"

// FUNCTION: GAMEMD 0x565730  (__thiscall)
// Convert the location to a cell index (signed /256 per axis, Y<<9 + X), and
// return the live cell at that index when it is in range and non-null.
// Otherwise stamp the truncated cell coord into InvalidCell.MapCoords and
// return &InvalidCell.
CellClass* MapClass::GetTargetCell(Point2D& location)
{
    int x = location.X / 256;
    int y = location.Y / 256;
    int idx = (y << 9) + x;

    CellClass* pCell;
    if (idx >= 0 && idx < this->TotalCells &&
        (pCell = this->Cells[idx]) != 0)
    {
        return pCell;
    }

    CellStruct cell;
    cell.X = (short)x;
    cell.Y = (short)y;
    InvalidCell.MapCoords = cell;
    return &InvalidCell;
}
