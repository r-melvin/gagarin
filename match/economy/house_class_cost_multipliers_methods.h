// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x50BF60: the five float multipliers at +0x5390..
//   +0x53A0 seeded with 1.0f, the owned-building list at +0x144 (Items) /
//   +0x150 (Count) walked per building, the building's Type at +0x520 and
//   the type's five factor floats at +0x16D0..+0x16E0. YRpp (consult-only,
//   no LICENSE) names CalculateCostMultipliers.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_COST_MULTIPLIERS_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_COST_MULTIPLIERS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct BuildingType_0050BF60
{
    char  _pad0000[0x16D0];       // +0x0000
    float FactorInfantry;         // +0x16D0
    float FactorUnits;            // +0x16D4
    float FactorAircraft;         // +0x16D8
    float FactorBuildings;        // +0x16DC
    float FactorDefenses;         // +0x16E0
};
GG_STATIC_ASSERT(offsetof(BuildingType_0050BF60, FactorInfantry) == 0x16D0);
GG_STATIC_ASSERT(offsetof(BuildingType_0050BF60, FactorDefenses) == 0x16E0);

struct Building_0050BF60
{
    char _pad0000[0x520];          // +0x0000
    BuildingType_0050BF60* Type;   // +0x0520
};
GG_STATIC_ASSERT(offsetof(Building_0050BF60, Type) == 0x520);

// DynamicVectorClass<BuildingClass*> at +0x140 (Items +0x144, Count +0x150).
// Read through an inlined operator[] so every factor re-reads the list and
// the building, as retail does.
struct BuildingVector_0050BF60
{
    void* Vptr;                    // +0x00
    Building_0050BF60** Items;     // +0x04
    char _pad0008[0x08];           // +0x08
    int  Count;                    // +0x10
    int  _pad0014;                 // +0x14

    Building_0050BF60*& operator[](int i) { return Items[i]; }
};
GG_STATIC_ASSERT(offsetof(BuildingVector_0050BF60, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(BuildingVector_0050BF60, Count) == 0x10);

struct House_0050BF60
{
    char _pad0000[0x140];              // +0x0000
    BuildingVector_0050BF60 Buildings; // +0x0140  owned-building list
    char _pad0158[0x5390 - 0x158];     // +0x0158
    float InfantryCostMult;            // +0x5390
    float UnitCostMult;                // +0x5394
    float AircraftCostMult;            // +0x5398
    float BuildingCostMult;            // +0x539C
    float DefenseCostMult;             // +0x53A0

    // FUNCTION: GAMEMD 0x50BF60 — HouseClass::CalculateCostMultipliers.
    void CalculateCostMultipliers();
};
GG_STATIC_ASSERT(offsetof(House_0050BF60, Buildings) == 0x140);
GG_STATIC_ASSERT(offsetof(House_0050BF60, InfantryCostMult) == 0x5390);
GG_STATIC_ASSERT(offsetof(House_0050BF60, DefenseCostMult) == 0x53A0);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_COST_MULTIPLIERS_METHODS_H
