// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x457CE0.

#include "building_class_occupy_methods.h"

// FUNCTION: GAMEMD 0x457CE0
//
// May this infantry enter the building? The building must be occupiable, not
// mid-unload or mid-garrison mission, on the usable map, and not warping out.
// An occupier needs the same owner (or a passive owner), a free slot, a
// building above red health and no mind control; an assaulter needs a
// hostile owner and somebody already inside to attack.
//
// The two branches are an if/else that fall into one shared `return true`;
// separate true returns per branch turn the last tests into SETE/SETNE.
bool Obj_00457CE0::CanBeOccupiedBy(Obj_00457CE0* infantry)
{
    if (infantry == 0) {
        return false;
    }
    if (!BuildingType->CanBeOccupied) {
        return false;
    }
    if (CurrentMission == 0x12 || CurrentMission == 0x13) {
        return false;
    }

    Coord_00457CE0 buf;
    if (!MapInstance_00457CE0.IsWithinUsableArea((this->*Vptr->GetCoords)(&buf))) {
        return false;
    }
    if ((this->*Vptr->IsBeingWarpedOut)()) {
        return false;
    }

    InfantryType_00457CE0* type = infantry->InfantryType;
    if (type->Occupier) {
        if (Owner != infantry->Owner && !Owner->Type->MultiplayPassive) {
            return false;
        }
        if ((this->*Vptr->GetOccupantCount)() == BuildingType->MaxNumberOccupants) {
            return false;
        }
        if (IsRedHP()) {
            return false;
        }
        if (infantry->IsMindControlled()) {
            return false;
        }
    } else {
        if (!type->Assaulter) {
            return false;
        }
        if (Owner->IsAlliedWith(infantry)) {
            return false;
        }
        if ((this->*Vptr->GetOccupantCount)() == 0) {
            return false;
        }
    }
    return true;
}
