// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x4593A0.

#include "building_class_unload_bunker_methods.h"

// FUNCTION: GAMEMD 0x4593A0  BuildingClass::UnloadBunker
//
// Let the bunkered unit out: its locomotor is switched back on through the
// COM slot +0x58, it is placed one half-cell off the bunker's own position
// through slot +0x70 (smart-pointer null checks and E_POINTER inlined), its
// slot +0x544 gets 1.0, the two back-links are cleared and the building goes
// through its +0x274 virtual with 3.
//
// The returned-coordinate buffer is scoped to the block that reads it. Retail's
// frame is that one 12-byte buffer: the adjusted copy lives in EBX/EBP and its
// Z is spilled into the dead buffer's third slot, which VC6 only does once the
// buffer's scope has closed. With the buffer and the adjusted copy in one scope
// the frame is 0x18 (95.6%).
void Building_004593A0::UnloadBunker()
{
    Unit_004593A0* unit = BunkerLinkedItem;
    if (unit != 0 && (unit->*unit->Vptr->WhatAmI)() == 1) {
        if (unit->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL0_004593A0(unit->Locomotor, 0x58);

        Coord_004593A0 coords;
        {
            Coord_004593A0 buf;
            Coord_004593A0* here = (this->*this->Vptr->GetCoords)(&buf);
            coords.X = here->X - 0x80;
            coords.Y = here->Y + 0x80;
            coords.Z = here->Z;
        }

        if (unit->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL70_004593A0(unit->Locomotor, 0x47, coords);

        (unit->*unit->Vptr->At_544)(1.0);
        unit->BunkerLinkedItem = 0;
        BunkerLinkedItem = 0;
        (this->*this->Vptr->At_274)(3);
    }
}
