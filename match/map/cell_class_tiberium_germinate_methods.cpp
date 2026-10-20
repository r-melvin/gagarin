// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4838E0.

#include "cell_class_tiberium_germinate_methods.h"

// First building / terrain object occupying the cell, or null. Both walks are
// gated by the IsActive byte and are inlined by retail (WhatAmI == 6 for a
// building, 0x24 for a terrain object); the not-found exit of each walk is
// threaded straight past the caller's null test.
inline Obj_004838E0* Cell_004838E0::GetBuilding() const
{
    if (DAT_00A8E9A0) {
        for (Obj_004838E0* obj = this->FirstObject; obj; obj = obj->NextObject) {
            if ((obj->*obj->Vtbl->WhatAmI)() == 6) {
                return obj;
            }
        }
    }
    return 0;
}

inline Obj_004838E0* Cell_004838E0::GetTerrain() const
{
    if (DAT_00A8E9A0) {
        for (Obj_004838E0* obj = this->FirstObject; obj; obj = obj->NextObject) {
            if ((obj->*obj->Vtbl->WhatAmI)() == 0x24) {
                return obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4838E0
//
// Can ore/gems spread into this cell?  The cell must be inside the usable map
// area, carry neither of the two blocking flags, not sit under a live building
// whose type forbids growth, not hold a terrain object whose type forbids it,
// have a land type that accepts ore, carry no overlay yet, have nothing at
// +0x11C, and its isometric tile type (when in range) must allow tiberium.
// The tiberium argument is not consulted.  Written as one conjunction so every
// failing guard shares the single trailing `return false` block.
bool Cell_004838E0::CanTiberiumGerminate(void* tiberium)
{
    Building_004838E0* bld;
    Terrain_004838E0* ter;
    int idx;
    if (MapInstance_004838E0.IsWithinUsableArea(&this->MapCoords, true)
        && !(this->Flags & 0x500)
        && !((bld = (Building_004838E0*)this->GetBuilding()) != 0
             && ((Obj_004838E0*)bld)->Health > 0
             && !bld->Type->At_C9A
             && !bld->Type->At_1701)
        && !((ter = (Terrain_004838E0*)this->GetTerrain()) != 0
             && ter->Type->At_2B1)
        && GroundTable_004838E0[this->LandType].At_000
        && this->OverlayTypeIndex == -1
        && !this->At_11C
        && ((idx = this->IsoTileTypeIndex) < 0
            || idx >= IsoTileArray_004838E0.Count
            || IsoTileArray_004838E0.Items[idx]->At_306)) {
        return true;
    }
    return false;
}
