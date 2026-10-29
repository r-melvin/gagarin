// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4158E0.

#include "mission_stop_methods.h"

// FUNCTION: GAMEMD 0x4158E0
//
// One tick of a mission that is chasing something. Three outcomes, all reporting
// the same value: with no target the chase is dropped and the mission is
// switched; with a target but nothing at +0x5A4 the target is merely re-armed;
// and once the target is inside the rules-supplied range the mission switches and
// a counter is decremented.
//
// The +0x6D3 counter is decremented rather than cleared, so several of these can
// be outstanding at once.
int AircraftClass_004158E0::FUN_004158E0()
{
    AircraftClass_004158E0* target = this->Target;

    if (target == 0) {
        (this->*this->Vtbl->At_480)(0, 1);
        (this->*this->Vtbl->At_1E8)(4, 0);
        return 3;
    }

    if (this->At_5A4 == 0) {
        (this->*this->Vtbl->At_480)(target, 1);
        return 3;
    }

    if (this->FUN_005F6440(target) <= RulesInstance->ParadropRadius) {
        (this->*this->Vtbl->At_1E8)(0x1B, 0);
        this->At_6D3 = this->At_6D3 - 1;
    }

    return 3;
}
