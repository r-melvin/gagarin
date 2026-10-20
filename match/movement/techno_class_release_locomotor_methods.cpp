// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x70FEE0.

#include "techno_class_release_locomotor_methods.h"

// FUNCTION: GAMEMD 0x70FEE0
//
// Drop the object this techno's locomotor is carrying. A carried foot unit
// still in the air is marked crashing and manipulated by this techno's
// owner, told to forget its target and destination; one on the ground is
// simply let go. Either way the link is cleared and, on request, so is
// this techno's own target.
void Techno_0070FEE0::ReleaseLocomotor(bool clearTarget)
{
    if (LocomotorTarget != 0) {
        LocomotorTarget->LocomotorSource = 0;
        if (LocomotorTarget != 0 && (LocomotorTarget->AbstractFlags & 4)) {
            if ((LocomotorTarget->*LocomotorTarget->Vptr->GetHeight)() > 0) {
                LocomotorTarget->IsCrashing = 1;
                LocomotorTarget->IsBeingManipulated = 1;
                LocomotorTarget->BeingManipulatedBy = this;
                LocomotorTarget->ChronoWarpedByHouse = Owner;
                (LocomotorTarget->*LocomotorTarget->Vptr->At_3A0)();
                (LocomotorTarget->*LocomotorTarget->Vptr->SetDestination)(0, true);
                LocomotorTarget = 0;
                if (clearTarget) {
                    (this->*Vptr->SetTarget)(0);
                }
                return;
            }
            (LocomotorTarget->*LocomotorTarget->Vptr->SetDestination)(0, true);
            Techno_0070FEE0* foot;
            if (LocomotorTarget == 0) {
                foot = 0;
            } else {
                foot = (LocomotorTarget->AbstractFlags & 4) ? LocomotorTarget : 0;
            }
            foot->IsLetGoByLocomotor = 1;
            (LocomotorTarget->*LocomotorTarget->Vptr->SetDestination)(0, true);
        }
        LocomotorTarget = 0;
        if (clearTarget) {
            (this->*Vptr->SetTarget)(0);
        }
    }
}
