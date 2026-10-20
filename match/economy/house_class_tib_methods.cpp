// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @0x4F9610 and @0x500510
//   (Ghidra disasm). Names cross-checked against YRpp HouseClass.h (consult-
//   only, no LICENSE); each offset/address reconfirmed against the binary.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4F9610   HouseClass::GiveTiberium       (__thiscall)
//   FUNCTION: GAMEMD 0x500510   HouseClass::GetPrimaryFactory  (__thiscall)
//   GLOBAL:   GAMEMD 0xB0F4E8   TiberiumClass::Array  (DynamicVectorClass<TiberiumClass*>)
//   GLOBAL:   GAMEMD 0x7EAA00   float 5.0f  (FMUL multiplicand)
//   LIBRARY:  GAMEMD 0x7C5F00   __ftol      (CRT float->long; excluded from match)

#include "house_class_tib_methods.h"

// GLOBAL: GAMEMD 0xB0F4E8 — the engine's global Tiberium type array.
extern DynamicVectorClass_TiberiumPtr TiberiumArray;

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4F9610  (__thiscall)
//
// Accrue refined Tiberium into the house: a flat stat counter (StatAccrued54E8
// gets amount*5) and credits (Balance gets the Tiberium's Value scaled by the
// country's IncomeMult and the amount). Each accumulator is truncated to int
// (__ftol). Returns the amount (st0 holds `amount` on exit).
//
//   FLD amount; FMUL 5.0f; FIADD [54E8]; __ftol -> [54E8]
//   FILD Tib->Value; FMUL Type->IncomeMult; FMUL amount; FIADD Balance;
//     __ftol -> Balance;  return amount
// ---------------------------------------------------------------------------
float HouseClass::GiveTiberium(float amount, int type)
{
    this->StatAccrued54E8 = (int)(amount * 5.0f + this->StatAccrued54E8);
    this->Balance = (int)(TiberiumArray.Items[type]->Value
                          * this->Type->IncomeMult * amount + this->Balance);
    return amount;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x500510  (__thiscall)
//
// Return the house's primary FactoryClass for the given object kind. Dense
// switch on absID over [Unit..UnitType] (DEC EAX; CMP 0x27; JA -> default 0):
//   Unit/UnitType         -> naval ? Primary_ForShips : Primary_ForVehicles
//   Aircraft/AircraftType -> Primary_ForAircraft
//   Building/BuildingType -> buildCat==Combat ? Primary_ForDefenses
//                                             : Primary_ForBuildings
//   Infantry/InfantryType -> Primary_ForInfantry
//   default               -> NULL
// ---------------------------------------------------------------------------
FactoryClass* HouseClass::GetPrimaryFactory(AbstractType absID, bool naval, BuildCat buildCat) const
{
    switch (absID)
    {
    case abs_Infantry:
    case abs_InfantryType:
        return this->Primary_ForInfantry;

    case abs_Unit:
    case abs_UnitType:
        return naval ? this->Primary_ForShips : this->Primary_ForVehicles;

    case abs_Building:
    case abs_BuildingType:
        return (buildCat == bc_Combat) ? this->Primary_ForDefenses
                                       : this->Primary_ForBuildings;

    case abs_Aircraft:
    case abs_AircraftType:
        return this->Primary_ForAircraft;

    default:
        return 0;
    }
}
