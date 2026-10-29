// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x578AD0.

#include "map_class_traversable_methods.h"

// FUNCTION: GAMEMD 0x578AD0  MapClass::MakeTraversable (__thiscall, ret 0x8)
//
// Ask every building standing on `cell` to open up for `visitor`. The cell is
// resolved through the global map's cell array with the fixed 512x512 bound;
// a missing cell falls back to InvalidCell after stamping the coords into it.
// Along the cell's object chain, any *other* object that is a building
// (WhatAmI == 6) with the type flag at +0x16B7 set is checked: an allied owner
// gets the building's own MakeTraversable verdict returned directly; an
// unallied one that is already traversable ends the walk with true. `this` is
// never read — the walk goes through the global instance.
bool MapView_578AD0::MakeTraversable(Obj_00578AD0 const* visitor, CellStruct const& cell) const
{
    int idx = (cell.Y << 9) + cell.X;
    CellClass_00578AD0* pCell;

    if (idx < 0 || idx >= 0x40000 || (pCell = MapInstance.Cells[idx]) == 0) {
        InvalidCell.MapCoords = cell;
        pCell = &InvalidCell;
    }

    for (Obj_00578AD0* obj = pCell->FirstObject; obj != 0; obj = obj->NextObject) {
        if (visitor != obj && (obj->*obj->Vtbl->WhatAmI)() == 6 && obj->Type->At_16B7) {
            if (obj->Owner->IsAlliedWith(visitor)) {
                return obj->MakeTraversable();
            }
            if (obj->IsTraversable()) {
                break;
            }
        }
    }
    return true;
}
