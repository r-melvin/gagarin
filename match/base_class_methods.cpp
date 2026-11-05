// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   BaseClass (the AI base node list embedded in HouseClass at +0x5700) is named by
//   RTTI; its vtable is at 0x7E3880.
//
// BaseClass members between 0x42E780 and 0x42EB50. Ordered ascending by retail address.
#include <windows.h>
#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/cell.h"
#include "_layout/base_node_class.h"
#include "_layout/house_class.h"
#include "_layout/building_class.h"
#include "_layout/cell_class.h"
#include "_layout/map_0087f7e8.h"
#include "_layout/overlay_type_class.h"
#include "_layout/session_class.h"

extern BuildingTypeClass** DAT_00A83C6C;   // GLOBAL: GAMEMD 0xA83C6C
extern Cell DAT_0089C310;                  // GLOBAL: GAMEMD 0x89C310

// FUNCTION: GAMEMD 0x42E780
// Whether node `index` is already covered: it has a live building, or its cell shows the
// overlay of its type, or a building stands on the cell.
bool BaseClass::FUN_0042E780(int index)
{
    if (FUN_0042E820(index)) {
        return true;
    }
    int type = unknown_08[index].unknown_00;
    if (type >= 0) {
        BuildingTypeClass* buildingType = DAT_00A83C6C[type];
        if (buildingType->bools_1570[1]) {
            CellClass* cell = DAT_0087F7E8.FUN_005657A0(&unknown_08[index].unknown_04);
            int overlay = buildingType->ToOverlay->ArrayIndex;
            if (cell->OverlayTypeIndex == overlay) {
                return true;
            }
            BuildingClass* building = cell->GetBuilding();
            if (building) {
                return true;
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x42EA30
// The node matching this building's type and cell, when the building belongs to this base's house.
BaseNodeClass* BaseClass::FUN_0042EA30(BuildingClass* building)
{
    if (building->Owner == unknown_74) {
        for (int i = 0; i < unknown_14; i++) {
            if (building->Type->ArrayIndex == unknown_08[i].unknown_00) {
                if (building->vf_110() == unknown_08[i].unknown_04) {
                    return &unknown_08[i];
                }
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x42EB50
// First node of `type` (any type for -1) that is not yet covered; -1 when none.
int BaseClass::FUN_0042EB50(int type)
{
    for (int i = 0; i < unknown_14; i++) {
        if (type == -1) {
            if (!FUN_0042E780(i)) {
                if (Session_00A8B238.GameMode == 0 || !unknown_08[i].unknown_08) {
                    return i;
                }
                if (unknown_74->FUN_0050CAD0(&unknown_08[i])) {
                    unknown_08[i].unknown_04 = DAT_0089C310;
                    return i;
                }
            }
        } else if (unknown_08[i].unknown_00 == type && !FUN_0042E780(i)) {
            return i;
        }
    }
    return -1;
}
