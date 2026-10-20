// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x50BF60.

#include "house_class_cost_multipliers_methods.h"

// FUNCTION: GAMEMD 0x50BF60  HouseClass::CalculateCostMultipliers
//
// Start every cost multiplier at one and fold in each owned building's five
// type factors, re-reading the list pointer and the building for every
// factor as retail does.
//
// MATCHED 100% (44/44). The one lever: write the five multipliers through a
// `float*` local aimed at the first of them rather than through the named
// members. With the named float members cl 8804's type-based alias analysis
// proves the stores cannot touch the int `Count` and hoists
// `MOV EDX,[ECX+0x150]` above the whole function (4.3%); routing them through
// a float pointer makes the Count read live again, so the entry test loads it
// and the back edge re-reads it in place (`CMP EAX,dword ptr [ECX+0x150]`),
// which is exactly retail's loop. A `*(volatile int*)&Count` read in the loop
// condition gets the re-read too but costs a `MOV EDX,mem; CMP EAX,EDX` pair
// at the back edge instead of retail's folded memory compare (84.4%).
void House_0050BF60::CalculateCostMultipliers()
{
    float* mult = &InfantryCostMult;

    mult[0] = 1.0f;
    mult[1] = 1.0f;
    mult[2] = 1.0f;
    mult[3] = 1.0f;
    mult[4] = 1.0f;

    for (int i = 0; i < Buildings.Count; ++i) {
        mult[0] = Buildings[i]->Type->FactorInfantry * mult[0];
        mult[1] = Buildings[i]->Type->FactorUnits * mult[1];
        mult[2] = Buildings[i]->Type->FactorAircraft * mult[2];
        mult[3] = Buildings[i]->Type->FactorBuildings * mult[3];
        mult[4] = Buildings[i]->Type->FactorDefenses * mult[4];
    }
}
