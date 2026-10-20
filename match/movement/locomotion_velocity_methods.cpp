// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check

#include "locomotion_velocity_methods.h"

// FUNCTION: GAMEMD 0x70F670
//
// Add this object's current contribution to the mover, remembering what was
// contributed so the undo below can take exactly that much back out.
void VelocitySource_0070F670::ApplyVelocity(Mover_0070F670* mover)
{
    if (mover != 0) {
        int amount = (this->*this->Vtbl->CurrentContribution)();
        this->Contribution = amount;
        mover->Accumulate((this->*this->Vtbl->Convert)(amount));
    }
}

// FUNCTION: GAMEMD 0x70F6A0
//
// Take the remembered contribution back out of the mover and forget it.
void VelocitySource_0070F670::RemoveVelocity(Mover_0070F670* mover)
{
    if (mover != 0) {
        int amount = -this->Contribution;
        mover->Accumulate((this->*this->Vtbl->Convert)(amount));
        this->Contribution = 0;
    }
}
