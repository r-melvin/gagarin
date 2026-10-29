// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembled from retail gamemd.exe v1.001; offsets read numerically at the address in each
//   annotation. AngerNodes is the {house, anger level} vector at HouseClass+0x5604.
//
// Round 19 HouseClass leftovers, ascending by retail address.
// Address index: 0x501A20 0x5093C0

#include "../_layout/house_class.h"
#include "../_layout/anger_scout_struct.h"
#include "../_layout/building_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/current_objects.h"

// GLOBAL: GAMEMD 0xA83D4C -- HouseClass::CurrentPlayer.
extern HouseClass* CurrentPlayer;

// FUNCTION: GAMEMD 0x501A20
// Asks every selected building that the local player does not own, that produces power, and that is
// shown to the local player, to run its slot 73 with mode 2.
void FUN_00501A20()
{
    int count = CurrentObjects.Count;
    if (count != 0) {
        for (int i = 0; i < count; i++) {
            ObjectClass* object = CurrentObjects.Items[i];
            if (object != 0 && object->vf_11() == 6) {
                BuildingClass* building = static_cast<BuildingClass*>(object);
                if (!building->IsOwnedByCurrentPlayer && building->Type->PowerBonus > 0
                    && (building->DisplayProductionTo & (1 << CurrentPlayer->Type->ArrayIndex2)))
                    building->vf_73(2);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5093C0
// Cancels the anger recorded against `house`: finds its node and adds the node's level back with the
// opposite sign.
void HouseClass::FUN_005093C0(HouseClass* house)
{
    for (int i = 0; i < AngerNodes.Count; i++) {
        if (AngerNodes.Items[i].A == (int)house) {
            UpdateAngerNodes(-AngerNodes.Items[i].B, house);
            return;
        }
    }
}
