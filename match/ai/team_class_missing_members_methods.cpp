// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6EF4D0.

#include "team_class_missing_members_methods.h"

// FUNCTION: GAMEMD 0x6EF4D0
//
// Fill `out` with the techno types the team still needs: every taskforce
// entry's type is appended Amount times, then each live member's type strikes
// one copy out again.
//
// The taskforce is re-read through the team type on every access (the inlined
// AddItem calls a virtual, so nothing is hoisted); the per-entry amount is a
// local, which is what lets the inner loop count down through a spilled slot.
void Team_006EF4D0::GetTaskForceMissingMemberTypes(TypeVector_006EF4D0* out)
{
    int i;
    int j;

    for (i = 0; i < this->Type->TaskForce->CountEntries; i++) {
        TechnoType_006EF4D0* type = this->Type->TaskForce->Entries[i].Type;
        int amount = this->Type->TaskForce->Entries[i].Amount;
        for (j = 0; j < amount; j++) {
            out->AddItem(type);
        }
    }

    for (Foot_006EF4D0* member = this->FirstUnit; member != 0;
         member = member->NextTeamMember) {
        TechnoType_006EF4D0* type = (member->*member->Vtbl->GetTechnoType)();
        int index = out->FindItemIndex(type);
        if (index != -1) {
            out->RemoveItem(index);
        }
    }
}
