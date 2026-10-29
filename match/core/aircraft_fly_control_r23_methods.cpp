// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41B760.
//   IFlyControl slots of AircraftClass (table 0x7E2250); see
//   aircraft_fly_control_r8_methods.cpp for the neighbouring slot 5.
#include "../_layout/abstract_class.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/aircraft_type_class.h"
#include "../_layout/building_class.h"
#include "../_layout/techno_type_class.h"
#include "../combat/weapon_type_class.h"

// FUNCTION: GAMEMD 0x0041B760
//
// The aircraft's current heading as one of eight compass steps. A linked
// partner's body facing is used when there is a link, otherwise the aircraft's
// own second facing when it carries a passenger; with neither, the rules value.
int __stdcall AircraftClass::vf_04()
{
    DirStruct heading;
    DirStruct* facing;
    if (HasAnyLink()) {
        TechnoClass* partner = FUN_0065AD40(0);
        facing = partner->PrimaryFacing.FUN_004C93D0(&heading);
    } else if (Passengers.FirstPassenger != 0) {
        facing = SecondaryFacing.FUN_004C93D0(&heading);
    } else {
        return RulesInstance->unknown_044;
    }
    return (((facing->Whole >> 12) + 1) >> 1) & 7;
}

// FUNCTION: GAMEMD 0x0041B6A0
//
// How eager the aircraft is to carry: 100 when its type is a carryall and it
// either has a link or holds a passenger, else 0. A carryall that is empty and
// linked to a building of the right kind and category is refused first.
int __stdcall AircraftClass::vf_03()
{
    if (Type->Carryall && !Passengers.FirstPassenger && HasAnyLink()) {
        TechnoClass* partner = FUN_0065AD40(0);
        if (vf_97() == 7 && partner && partner->vf_11() == 6) {
            BuildingTypeClass* partnerType = ((BuildingClass*)partner)->Type;
            if (partnerType->bools_16A4[5] || partnerType->bools_16A4[0x27]) {
                return 0;
            }
        }
    }

    if ((HasAnyLink() && Type->Carryall) || (Passengers.FirstPassenger && Type->Carryall)) {
        return 100;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x0041B7F0
//
// Whether the aircraft's first weapon fires a projectile of the plain kind:
// there must be a weapon, its projectile's count field must not exceed 1, and
// the projectile's flag byte must be clear.
int __stdcall AircraftClass::vf_06()
{
    WeaponStruct* weapon = vf_254(0);
    if (!weapon) {
        return 0;
    }
    WeaponTypeClass* weaponType = weapon->WeaponType;
    if (!weaponType) {
        return 0;
    }
    BulletTypeClass* projectile = weaponType->Projectile;
    if (projectile->unknown_2DC > 1) {
        return 0;
    }
    return projectile->unknown_29E == 0;
}
