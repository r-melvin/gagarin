// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6F09C0 (name from
//   the YRpp method map).

#include "team_type_class_create_methods.h"
#include "../_layout/session_class.h"

// FUNCTION: GAMEMD 0x6F09C0  TeamTypeClass::CreateTeam (__thiscall, ret 0x4)
//
// Instantiate one team of this type for `house`. With no house given, the
// type's own Owner is used, or failing that the country index is resolved to
// a house (giving up when it names none). Outside scenario setup a
// non-negative Max caps the instances: in campaign mode against the type's
// own live count, otherwise against the house's count of this type. The team
// is allocated at its retail size and constructed in place.
TeamClass* TeamTypeClass::CreateTeam(HouseClass* house)
{
    // STRING: GAMEMD 0x842E7C
    FUN_004068E0("Create_One_Of...\n");

    if (house == 0) {
        house = this->Owner;
        if (house == 0) {
            if (!FUN_00510F60(this->idxHouse)) {
                return 0;
            }
            house = FindHouseByCountryIndex(this->idxHouse);
            if (house == 0) {
                return 0;
            }
        }
    }

    if (ScenarioInit_00A8E7AC == 0 && this->Max >= 0) {
        if (Session_00A8B238.GameMode == 0) {
            if (this->InstanceCount >= this->Max) {
                return 0;
            }
        } else {
            if (house->FUN_005095D0(this) >= this->Max) {
                return 0;
            }
        }
    }

    // STRING: GAMEMD 0x842E58
    FUN_004068E0("Creating a new team named '%s'.\n", this->Name.Data);

    TeamClass* team = (TeamClass*)operator new(sizeof(TeamClass));
    return team ? team->Construct(this, house, 0) : 0;
}
