// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at 0x6E4560, inside the TAction.cpp range.
//
//   Address index: 0x6E4560

#include <string.h>
#include "taction_class_methods.h"
#include "../_layout/house_class.h"
#include "../_layout/building_class.h"

// FUNCTION: GAMEMD 0x006E4560
// Flash every building of the house whose type ID equals the action's text, for
// the action's parameter. Fails when there is no house.
bool TActionClass::FUN_006E4560(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (house == 0)
        return false;
    for (int i = house->Buildings.Count - 1; i >= 0; i--) {
        BuildingClass* building = house->Buildings.Items[i];
        if (strcmp(building->Type->ID, unknown_54) == 0)
            building->DurationRemaining = unknown_90;
    }
    return true;
}
