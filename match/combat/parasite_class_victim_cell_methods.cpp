// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x62AB40.

#include "parasite_class_victim_cell_methods.h"

// FUNCTION: GAMEMD 0x62AB40  ParasiteClass::CanExistOnVictimCell
//
// Could the parasite survive where its victim now stands. Nothing without a
// victim, nothing in the air. A non-naval parasite riding a unit is rejected
// if the cell holds an object of kind 0; on the water-ish land types (2, 3, 6)
// it is rejected unless a bridge or a shore overlay (the two overlay bands)
// carries it. Finally the cell must be free of buildings.
bool Parasite_0062AB40::CanExistOnVictimCell()
{
    Obj_0062AB40* victim = Victim;
    if (victim == 0)
        return false;
    if ((victim->*victim->Vptr->IsInAir)())
        return false;

    if ((Owner->*Owner->Vptr->GetTechnoType)()->Naval == 0) {
        if (Owner != 0 && (Owner->*Owner->Vptr->WhatAmI)() == 1) {
            if ((Victim->*Victim->Vptr->GetCell)()->FUN_0047C550(0) != 0)
                return false;
        }

        int land = (Victim->*Victim->Vptr->GetCell)()->LandType;
        if (land == 2 || land == 6 || land == 3) {
            bool blocked = true;
            if ((Victim->*Victim->Vptr->GetCell)()->Flags & 0x100)
                blocked = false;
            int overlay = (Victim->*Victim->Vptr->GetCell)()->OverlayTypeIndex;
            if (overlay >= 0x4A && overlay <= 0x63)
                blocked = false;
            if ((overlay < 0xCD || overlay > 0xE6) && blocked)
                return false;
        }
    }

    // A named bool gives retail's TEST/SETZ; returning the compare directly
    // materialises it as NEG/SBB/INC.
    bool clear = (Victim->*Victim->Vptr->GetCell)()->FUN_0047C520() == 0;
    return clear;
}
