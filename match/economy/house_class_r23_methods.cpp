// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   HouseClass members matched against retail gamemd.exe v1.001 (round 23); disassembled from each
//   entry point. Counter and tracker offsets are those pinned in match/_layout/house_class.h.
//
// Address index: 0x4FF700

#include "../_layout/house_class.h"
#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/unit_type_class.h"

// FUNCTION: GAMEMD 0x4FF700
// Count a newly owned object against this house: the per-category owned total and, for categories
// that are tracked, the per-type owned counter and the built-types tally. Infantry already counted
// through the special flag are not counted twice.
void HouseClass::FUN_004FF700(TechnoClass* techno)
{
    techno->CountedAsOwned = true;
    if (!techno->vf_33()->Insignificant && !techno->vf_33()->bools_C8C[19]) {
        switch (techno->vf_11()) {
        case 6: {
            BuildingClass* building = static_cast<BuildingClass*>(techno);
            if (!building->vf_32() && (!building->Type->UndeploysInto || !building->Type->UndeploysInto->ResourceGatherer))
                OwnedBuildings++;
            else
                OwnedUnits++;
            int index = techno->vf_33()->vf_16();
            OwnedBuildingTypes.FUN_0049FA00(index);
            BuiltBuildingTypes.IncrementUnitTotal(index);
            return;
        }
        case 2: {
            OwnedAircraft++;
            int index = techno->vf_33()->vf_16();
            OwnedAircraftTypes.FUN_0049FA00(index);
            BuiltAircraftTypes.IncrementUnitTotal(index);
            return;
        }
        case 0xF: {
            int index = techno->vf_33()->vf_16();
            if (!techno->CountedAsOwnedSpecial && !techno->Absorbed) {
                OwnedInfantry++;
                techno->CountedAsOwnedSpecial = true;
            }
            OwnedInfantryTypes.FUN_0049FA00(index);
            BuiltInfantryTypes.IncrementUnitTotal(index);
            return;
        }
        case 1: {
            OwnedUnits++;
            int index = techno->vf_33()->vf_16();
            OwnedUnitTypes.FUN_0049FA00(index);
            BuiltUnitTypes.IncrementUnitTotal(index);
            if (techno->vf_33()->Naval && techno->vf_33()->Passengers == 0)
                OwnedNavy++;
            break;
        }
        }
    }
}
