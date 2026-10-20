// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4FB6B0.

#include "house_class_register_built_methods.h"

// FUNCTION: GAMEMD 0x4FB6B0  HouseClass::RegisterJustBuilt (__thiscall, ret 4)
//
// A factory has just finished something. The house records which type it was
// per category, bumps that category's per-type tally unless the type opts out,
// and picks the "unit ready" announcement: the rules-wide one for the category,
// overridden by the type's own creation sound when it has one. Nothing is said
// for buildings unless their type supplies a sound.
void House_004FB6B0::RegisterJustBuilt(Techno_004FB6B0* pTechno)
{
    int voice = -1;

    this->At_246 = 1;

    TechnoType_004FB6B0* pType = (pTechno->*pTechno->Vtbl->GetTechnoType)();

    switch ((pTechno->*pTechno->Vtbl->WhatAmI)()) {
    case 1:
        this->At_274 = (pType->*pType->Vtbl->GetArrayIndex)();
        if (pType->At_C9F == 0) {
            this->UnitCounter.Increment((pType->*pType->Vtbl->GetArrayIndex)());
        }
        voice = RulesInstance_004FB6B0->At_178;
        break;

    case 15:
        this->At_270 = (pType->*pType->Vtbl->GetArrayIndex)();
        if (pType->At_C9F == 0) {
            this->InfantryCounter.Increment((pType->*pType->Vtbl->GetArrayIndex)());
        }
        voice = RulesInstance_004FB6B0->At_17C;
        break;

    case 6:
        this->At_26C = (pType->*pType->Vtbl->GetArrayIndex)();
        if (pType->At_C9F == 0) {
            this->BuildingCounter.Increment((pType->*pType->Vtbl->GetArrayIndex)());
        }
        break;

    case 2:
        this->At_278 = (pType->*pType->Vtbl->GetArrayIndex)();
        if (pType->At_C9F == 0) {
            this->AircraftCounter.Increment((pType->*pType->Vtbl->GetArrayIndex)());
        }
        voice = RulesInstance_004FB6B0->At_180;
        break;
    }

    if (pType->At_534 != -1) {
        voice = pType->At_534;
    }

    if (voice != -1) {
        Coord_004FB6B0 coords = pTechno->Location;
        VocClass_PlayAt_004FB6B0(voice, coords, 0);
    }

    this->At_1FC = 1;
}
