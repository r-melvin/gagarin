// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x41DA20.

#include "airstrike_class_reset_target_methods.h"

// FUNCTION: GAMEMD 0x41DA20
//
// Point the strike at a new target. If the aircraft on the strike do not
// all agree on their +0x2FC link with the head aircraft, the strike is
// cleared instead. Otherwise a building that was the old target is told
// the strike is off and redrawn, a building that is the new target is
// linked to this strike, told it is on for 100000 frames and redrawn, and
// every aircraft whose link is positive is retargeted and sent to mission
// 1, which flags the strike as engaged.
void Airstrike_0041DA20::ResetTarget(Target_0041DA20* target)
{
    Foot_0041DA20* first = this->FirstObject;
    if (first != 0) {
        Foot_0041DA20* foot = first->NextTeamMember;
        while (foot != 0) {
            if (foot->At_2FC != first->At_2FC) {
                this->ClearTarget();
                return;
            }
            foot = foot->NextTeamMember;
        }
    }

    Target_0041DA20* oldBuilding = AsBuilding_0041DA20(this->Target);
    Target_0041DA20* newBuilding = AsBuilding_0041DA20(target);

    if (oldBuilding != 0) {
        oldBuilding->Airstrike = 0;
        (oldBuilding->*oldBuilding->Vtbl->At_158)();
        (oldBuilding->*oldBuilding->Vtbl->Mark)(2);
    }
    this->Target = 0;
    if (newBuilding != 0) {
        newBuilding->Airstrike = this;
        (newBuilding->*newBuilding->Vtbl->At_15C)(100000);
        (newBuilding->*newBuilding->Vtbl->Mark)(2);
    }

    Foot_0041DA20* foot = this->FirstObject;
    this->Target = target;
    for (int i = 0; i < this->At_30; i++) {
        if (foot != 0) {
            if (foot->At_2FC > 0) {
                (foot->*foot->Vtbl->SetTarget)(target);
                (foot->*foot->Vtbl->SetMission)(1, 0);
                this->At_3D = 1;
            }
            foot = foot->NextTeamMember;
        }
    }
}
