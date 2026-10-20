// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x452360.

#include "building_class_offline_methods.h"

// FUNCTION: GAMEMD 0x452360
//
// Take a powered building offline. Only structures that are currently
// powered and actually depend on power (a positive drain, or the Powered
// flag) do anything: the power flag drops, a redraw is requested, the owner's
// two blackout-activated bytes and its tech-tree-recheck byte are raised, the
// building's animations and light are disabled, the local player hears the
// EVA line, and any factory queue the building served is re-evaluated.
void BuildingClass_00452360::GoOffline()
{
    if (!this->HasPower)
        return;

    Type_00452360* type = this->Type;
    if (type->PowerDrain > 0 || type->Powered) {
        this->HasPower = 0;
        this->NeedsRedraw = 1;
        this->Owner->PowerBlackoutWasActivated = 1;
        this->Owner->RadarBlackoutWasActivated = 1;
        this->Owner->RecheckTechTree = 1;
        this->DisableStuff();
        if (this->Owner->IsControlledByCurrentPlayer())
            VoxClass_00452360::Play(EvaBuildingOffLine, -1, -1);
        if (this->Type->Factory != 0)
            this->Owner->Update_FactoriesQueues(this->Type->Factory, this->Type->Naval, 0);
    }
}
