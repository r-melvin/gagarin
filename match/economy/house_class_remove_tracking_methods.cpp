// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4FF550.

#include "house_class_remove_tracking_methods.h"

// FUNCTION: GAMEMD 0x4FF550  HouseClass::RemoveTracking (__thiscall, ret 4)
//
// The mirror of RegisterJustBuilt: an object has left the house's books. It
// clears the object's "tracked" flag, then — unless the type opts out of
// tracking entirely — walks down the per-category owned counts and the
// per-type tally for the category the object belongs to. Buildings are split
// between two counts depending on whether they are power/production relevant;
// infantry only decrement while their "still counted" flag is set; units also
// give back a second count when their type asks for it.
void House_004FF550::RemoveTracking(Techno_004FF550* pTechno)
{
    pTechno->At_3CC = false;

    if ((pTechno->*pTechno->Vtbl->GetTechnoType)()->At_232 != 0) {
        return;
    }

    if ((pTechno->*pTechno->Vtbl->GetTechnoType)()->At_C9F != 0) {
        return;
    }

    switch ((pTechno->*pTechno->Vtbl->WhatAmI)()) {
    case 6:
        if (!(pTechno->*pTechno->Vtbl->At_80)()
            && (pTechno->At_520->At_408 == 0
                || pTechno->At_520->At_408->At_5EC == 0)) {
            this->At_2F0--;
        } else {
            this->At_2E8--;
        }
        {
            TechnoType_004FF550* pType = (pTechno->*pTechno->Vtbl->GetTechnoType)();
            this->BuildingCounter.Decrement((pType->*pType->Vtbl->GetArrayIndex)());
        }
        break;

    case 2:
        this->At_2F8--;
        {
            TechnoType_004FF550* pType = (pTechno->*pTechno->Vtbl->GetTechnoType)();
            this->AircraftCounter.Decrement((pType->*pType->Vtbl->GetArrayIndex)());
        }
        break;

    case 15:
        if (pTechno->At_438 != 0) {
            this->At_2F4--;
            pTechno->At_438 = false;
        }
        {
            TechnoType_004FF550* pType = (pTechno->*pTechno->Vtbl->GetTechnoType)();
            this->InfantryCounter.Decrement((pType->*pType->Vtbl->GetArrayIndex)());
        }
        break;

    case 1:
        this->At_2E8--;
        {
            TechnoType_004FF550* pType = (pTechno->*pTechno->Vtbl->GetTechnoType)();
            this->UnitCounter.Decrement((pType->*pType->Vtbl->GetArrayIndex)());
        }
        if ((pTechno->*pTechno->Vtbl->GetTechnoType)()->At_CCE != 0) {
            if ((pTechno->*pTechno->Vtbl->GetTechnoType)()->At_5E0 == 0) {
                this->At_2EC--;
            }
        }
        break;
    }
}
