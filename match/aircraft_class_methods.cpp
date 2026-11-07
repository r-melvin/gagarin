// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at the entry below (AircraftClass
//   primary vtable 0x7E22A4, slot 54), read with the Ghidra CLI from the entry point.
#include "_layout/aircraft_class.h"
#include "_layout/aircraft_type_class.h"
#include "_layout/gbl_0087f7e8.h"
#include "weapon_type_class.h"

// FUNCTION: GAMEMD 0x414310
// Slot 54: a flying type is raised by its height above the ground unless it is a missile or already on the usable
// map; once the base accepts the placement the turret is set to the facing, the stage timer restarts and slot 337
// is told whether the type's slot 47 value equals slot 114.
bool AircraftClass::vf_54(const CoordStruct& coord, int a2)
{
    CoordStruct loc = coord;
    if (!Type->MissileSpawn) {
        if (!Spawned && DAT_0087F7E8.FUN_005785F0(coord))
            loc.Z = DAT_0087F7E8.FUN_00578080(coord);
        else
            loc.Z = DAT_0087F7E8.FUN_00578080(coord) + Type->vf_47();
    }
    if (FootClass::vf_54(loc, a2)) {
        if (!Type->Selectable || !Type->Landable
            || (vf_254(0)->WeaponType && vf_254(0)->WeaponType->Camera))
            Spawned = 1;
        if (Passengers.FirstPassenger)
            HasPassengers = 1;
        DirStruct dir;
        dir.Raw = (a2 & 0xFF) << 8;
        SecondaryFacing.FUN_004C9300(&dir);
        SetRate(1);
        StageClass::Value = 0;
        if (vf_114() == Type->vf_47())
            vf_337(1.0);
        else
            vf_337(0.0);
        return true;
    }
    return false;
}
