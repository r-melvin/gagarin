// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x62A8E0.

#include "parasite_class_infect_methods.h"

#define INFECT_VT(p) ((p)->Vtbl)

// FUNCTION: GAMEMD 0x62A8E0
//
// Can this parasite latch onto `target`? The target must exist, be on the map,
// alive, have health, not already carry a parasite, be of a parasite-able type
// and not be bunkered. A naval parasite (its owner's type is Naval) additionally
// needs the target's cell to be a water tile. Every refusal shares the one
// `XOR AL,AL` tail; the acceptances share the `MOV AL,1` tail ahead of it.
bool ParasiteClass_0062A8E0::CanInfect(FootInfect* target)
{
    // Every refusal shares the one `XOR AL,AL` tail at 0x62A976, so the
    // acceptance conditions nest down to a single trailing `return false`;
    // written as seven early returns VC6 emits seven epilogues (12.2%).
    if (target != 0
        && !target->InLimbo
        && target->IsAlive
        && target->Health != 0
        && target->ParasiteEatingMe == 0
        && (target->*INFECT_VT(target)->GetTechnoType)()->At_D38
        && target->BunkerLinkedItem == 0) {
        FootInfect* owner = this->Owner;
        if (owner == 0
            || !(owner->*INFECT_VT(owner)->GetTechnoType)()->Naval
            || (target->*INFECT_VT(target)->GetCell)() == 0
            || (target->*INFECT_VT(target)->GetCell)()->Tile_Is_Water()) {
            return true;
        }
    }

    return false;
}
