// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x452540.

#include "building_class_traversable_methods.h"

// FUNCTION: GAMEMD 0x452540
//
// Ask a gate to let something through. Non-gates are always traversable.
// A gate already in the Open mission whose transition timer is neither
// "opening" (10) nor "closed" (00) answers with IsTraversable (open and
// settled). Otherwise the gate is forced out of its current mission, Open
// is queued and started, and the caller is told to wait.
bool BuildingClass_00452540::MakeTraversable()
{
    if (!this->Type->Gate)
        return true;

    if ((this->*this->Vtbl->GetCurrentMission)() == MISSION_OPEN_00452540
        && !this->GateTimer.AreStates10()
        && !this->GateTimer.AreStates00())
    {
        return this->IsTraversable();
    }

    (this->*this->Vtbl->ForceMission)(-1);
    (this->*this->Vtbl->QueueMission)(MISSION_OPEN_00452540, false);
    (this->*this->Vtbl->NextMission)();
    return false;
}
