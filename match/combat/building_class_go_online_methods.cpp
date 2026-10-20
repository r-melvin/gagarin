// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x452260.

#include "building_class_go_online_methods.h"

// FUNCTION: GAMEMD 0x452260  BuildingClass::GoOnline (__thiscall)
//
// Bring an unpowered building back online, unless it is EMP-locked. The
// power flag rises, a redraw is requested, the owner's two blackout-activated
// bytes and its tech-tree-recheck byte are raised, the building's light,
// end post and enabled animations come back (EnableStuff, expanded inline),
// any factory queue the building serves is re-evaluated, and the local
// player hears the EVA line.
void BuildingClass_00452260::GoOnline()
{
    if (this->HasPower)
        return;
    if (this->EMPLockRemaining != 0)
        return;

    this->HasPower = 1;
    this->NeedsRedraw = 1;
    this->Owner->PowerBlackoutWasActivated = 1;
    this->Owner->RadarBlackoutWasActivated = 1;
    this->Owner->RecheckTechTree = 1;
    this->EnableStuff();
    if (this->Type->Factory != 0)
        this->Owner->Update_FactoriesQueues(this->Type->Factory, this->Type->Naval, 0);
    if (this->Owner->IsControlledByCurrentPlayer())
        VoxClass_00452260::Play(EvaBuildingOnLine_00452260, -1, -1);
}
