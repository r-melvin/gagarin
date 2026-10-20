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
// PARTIAL (95.6%, 65/68; mnemonic multiset identical). Retail's frame is one
// 12-byte coordinate buffer: the adjusted copy lives in EBX/EBP with only its
// Z spilled, into the dead buffer's own third slot. VC6 gives the adjusted
// copy its own 12 bytes (frame 0x18), so the three frame-size instructions
// differ. Copying the struct from the returned pointer and adjusting in place
// (88.2%), three int locals (95.6%) and a constructor temporary built at the
// call (34.8%) do not collapse the frame.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EBP,
// ESI, EDI on both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
void Building_004593A0::UnloadBunker()
{
    Unit_004593A0* unit = BunkerLinkedItem;
    if (unit != 0 && (unit->*unit->Vptr->WhatAmI)() == 1) {
        if (unit->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL0_004593A0(unit->Locomotor, 0x58);

        Coord_004593A0 buf;
        Coord_004593A0* here = (this->*this->Vptr->GetCoords)(&buf);
        Coord_004593A0 coords;
        coords.X = here->X - 0x80;
        coords.Y = here->Y + 0x80;
        coords.Z = here->Z;

        if (unit->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL70_004593A0(unit->Locomotor, 0x47, coords);

        (unit->*unit->Vptr->At_544)(1.0);
        unit->BunkerLinkedItem = 0;
        BunkerLinkedItem = 0;
        (this->*this->Vptr->At_274)(3);
    }
}
