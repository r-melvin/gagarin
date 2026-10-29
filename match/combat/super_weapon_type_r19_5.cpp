// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 (vtable 0x7F4090 slot 27,
//   entry 0x7F40FC). Implemented on the canonical SuperWeaponTypeClass.
//   Address index: 0x6CEF80.

#include "../_layout/super_weapon_type_class.h"
#include "../_layout/building_class.h"
#include "../_layout/house_class.h"

// GLOBAL: GAMEMD 0xA83D4C -- the local player's house.
extern HouseClass* CurrentPlayer;

// FUNCTION: GAMEMD 0x6CEF80
// The action this type performs on a target. Type 10 only acts on a building
// that belongs to an ally of the local player; otherwise it yields 0x46.
int SuperWeaponTypeClass::vf_27(int unused, AbstractClass* target)
{
    if (this->Type == 10) {
        if (!target || target->vf_11() != 6)
            return 0x46;
        BuildingClass* building = (BuildingClass*)(target->vf_11() == 6 ? target : 0);
        if (!building->Owner->IsAlliedWith(CurrentPlayer))
            return 0x46;
    }
    return this->Action;
}
