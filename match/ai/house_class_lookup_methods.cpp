// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x510ED0.

#include "house_class_lookup_methods.h"

// FUNCTION: GAMEMD 0x510ED0
//
// Map a "<Player @ X>" house-type index (0x117B..0x1182 = A..H) to the house
// that spawned at that starting position.  Each letter arm asks the scenario's
// HouseIndices table for the HouseClass::Array index of that slot; the index
// is then bounds-checked against the array before being dereferenced.  Any
// other type index yields null.
//
// The eight arms are a plain if-chain in retail, each arm pushing its slot
// constant and falling into one cross-jumped copy of the lookup call.
HouseClass* __fastcall HouseClass::FindByPlayerAt(int at)
{
    int idx;

    if (at == 0x117B) {
        idx = ScenarioInstance->GetHouseIndex(0);
    } else if (at == 0x117C) {
        idx = ScenarioInstance->GetHouseIndex(1);
    } else if (at == 0x117D) {
        idx = ScenarioInstance->GetHouseIndex(2);
    } else if (at == 0x117E) {
        idx = ScenarioInstance->GetHouseIndex(3);
    } else if (at == 0x117F) {
        idx = ScenarioInstance->GetHouseIndex(4);
    } else if (at == 0x1180) {
        idx = ScenarioInstance->GetHouseIndex(5);
    } else if (at == 0x1181) {
        idx = ScenarioInstance->GetHouseIndex(6);
    } else if (at == 0x1182) {
        idx = ScenarioInstance->GetHouseIndex(7);
    } else {
        return 0;
    }

    if (idx >= 0 && idx < HouseArray.Count) {
        return HouseArray.Items[idx];
    }
    return 0;
}
