// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x578080.

#include "map_class_zpos_methods.h"

// FUNCTION: GAMEMD 0x578080  MapClass::GetZPos (__thiscall, ret 0x4)
// Ground height under a world coordinate. `this` is unused — the cell comes
// from the global array — and an out-of-range or empty cell falls back to the
// spare cell, whose MapCoords are stamped first so the height query still has
// something sensible to work from.
//
// The `CDQ; AND EDX,0xFF; ADD; SAR 8` sequences are VC6's signed divide by 256,
// so the source divides rather than shifts.
int MapClass::GetZPos(CoordStruct* coords)
{
    // Retail copies both ints in one go (`MOV EAX,[ECX]; MOV EDX,[ECX+4]` then
    // two stores) and afterwards re-reads coords->Y from memory — the shape of
    // a struct copy followed by fresh member reads, not of two scalar loads
    // kept live (which costs the reload and one instruction).
    Point2D subcoords = *(Point2D*)coords;

    int cellX = coords->X / 256;
    int cellY = coords->Y / 256;
    int index = cellY * MAP_CELL_PITCH + cellX;

    CellClass* cell;
    if (index < 0 || index >= CellArrayCount || (cell = CellArrayItems[index]) == 0)
    {
        CellStruct coordsOfCell;
        coordsOfCell.X = (short)cellX;
        coordsOfCell.Y = (short)cellY;
        SpareCell.MapCoords = coordsOfCell;

        cell = &SpareCell;
    }

    return cell->GetFloorHeight(subcoords);
}
