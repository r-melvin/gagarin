// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4E00B0.

#include "foot_class_jumpjet_cell_methods.h"

// FUNCTION: GAMEMD 0x4E00B0  FootClass::Jumpjet_OccupyCell (__thiscall, ret 0x4)
// Move a jumpjet's cell reservation. The old cell is released only when both
// the old and the new coordinate are real — releasing on the way to "no cell"
// would drop a reservation the caller is about to re-take.
//
// GetCellAt is called twice on purpose: retail tests through one call and
// clears through a second rather than caching the pointer.
void FootClass::Jumpjet_OccupyCell(CellStruct coords)
{
    // Bound to a reference, not accessed through `this` each time: retail
    // computes `LEA ESI,[EDI+0x564]` once and reaches the Y member as
    // `[ESI+2]`, passes ESI to GetCellAt and stores through it. Going through
    // the member directly emits `[EDI+0x566]` for the Y compare instead.
    CellStruct& current = CurrentJumpjetMapCoords;

    if (current.X != NoCell.X || current.Y != NoCell.Y)
    {
        if (coords.X != NoCell.X || coords.Y != NoCell.Y)
        {
            if (MapInstance.GetCellAt(current)->Jumpjet == this)
                MapInstance.GetCellAt(current)->Jumpjet = 0;
        }
    }

    current = coords;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8B3D88
CellStruct NoCell;
// END defined globals
