// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The slot body, call order, argument widths, and touched offsets below are
// read from the retail entry at 0x716150. This file is a provisional
// function grouping; original translation-unit ownership is unknown.
#include "_layout/techno_type_class.h"
#include "_layout/cell_class.h"
#include "_layout/building_type_class_layout.h"
#include "ui_display_chain.h"

GG_STATIC_ASSERT(offsetof(TechnoTypeClass, SpeedType) == 0x67C);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->SpeedType) == 4);
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);
GG_STATIC_ASSERT(offsetof(CellStruct, X) == 0);
GG_STATIC_ASSERT(sizeof(((CellStruct*)0)->X) == 2);
GG_STATIC_ASSERT(offsetof(CellStruct, Y) == 2);
GG_STATIC_ASSERT(sizeof(((CellStruct*)0)->Y) == 2);

// GLOBAL: GAMEMD 0xB0EB58 -- adjacent signed cell coordinates.
extern CellStruct DAT_00B0EB58;

// FUNCTION: GAMEMD 0x716150
// PARTIAL 92.3%: multiset identical; retail compares both terminator words straight against memory where cl
// reuses the first compare's 0x7FFF in AX.
bool TechnoTypeClass::vf_42(CellStruct* cell, HouseClass* owner)
{
    if (cell->X == DAT_00B0EB58.X && cell->Y == DAT_00B0EB58.Y) {
        return false;
    }

    CellStruct* offsets = vf_36(1);
    const bool isBuilding = vf_11() == 7;
    bool rejectedAny = false;
    bool acceptedAny = false;

    while (offsets != 0 &&
           !(offsets->X == 0x7FFF && offsets->Y == 0x7FFF)) {
        CellStruct candidate = *cell + *offsets++;

        if (isBuilding) {
            // Native slot 11 == 7 selects its BuildingTypeClass path.
            if (!reinterpret_cast<CellClass*>(Map_0087F7E8.FUN_005657A0(&candidate))->FUN_0047C620(
                    SpeedType, static_cast<BuildingTypeClass*>(this), owner)) {
                rejectedAny = true;
            } else {
                acceptedAny = true;
            }
        } else {
            if (!reinterpret_cast<CellClass*>(Map_0087F7E8.FUN_005657A0(&candidate))->IsClearToMove(
                    SpeedType, false, false, -1, 0, -1, true)) {
                rejectedAny = true;
            } else {
                acceptedAny = true;
            }
        }
    }

    if (isBuilding && static_cast<BuildingTypeClass*>(this)->ToTile != 0) {
        return acceptedAny;
    }
    return !rejectedAny;
}
