// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   UnitTypeClass virtual overrides read off retail gamemd.exe v1.001 (vtable of
//   UnitTypeClass, RTTI-named). Functions are in ascending retail address order.

#include <new.h>
#include "../_layout/unit_type_class.h"
#include "../_layout/unit_class.h"
#include "../_layout/obj_004a1d30.h"

// GLOBAL: GAMEMD 0xB1D138 -- run-time derived z extent used by vf_31.
extern int DAT_00B1D138;

// FUNCTION: GAMEMD 0x747560
// Create a UnitClass of this type for the given house.
ObjectClass* UnitTypeClass::vf_35(HouseClass* house)
{
    return new UnitClass(this, house);
}

// FUNCTION: GAMEMD 0x747590
// Footprint extent from the type's largest dimension, clamped to 60.
CoordStruct UnitTypeClass::vf_30()
{
    int v = MaxDimension;
    int x = v - v / 4;
    int z = v - v / 4;
    if (x >= 60) x = 60;
    if (z >= 60) z = 60;
    CoordStruct r;
    r.X = x; r.Y = x; r.Z = z;
    return r;
}

// FUNCTION: GAMEMD 0x7475D0
CoordStruct UnitTypeClass::vf_31()
{
    CoordStruct result;
    result.X = 0x100;
    result.Y = 0x100;
    result.Z = DAT_00B1D138 * 2;
    return result;
}

// FUNCTION: GAMEMD 0x747F70
// Feed the unit-type flags into the sync checksum.
void UnitTypeClass::vf_13(Obj_004A1D30* crc)
{
    TechnoTypeClass::vf_13(crc);
    crc->FUN_004A1D50(MovementRestrictedTo);
    crc->FUN_004A1CA0(Passive);
    crc->FUN_004A1CA0(CrateGoodie);
    crc->FUN_004A1CA0(Harvester);
    crc->FUN_004A1CA0(Weeder);
    crc->FUN_004A1CA0(unknown_E10);
    crc->FUN_004A1CA0(HasTurret);
    crc->FUN_004A1CA0(IsTilter);
    crc->FUN_004A1CA0(IsSimpleDeployer);
    crc->FUN_004A1CA0(UseTurretShadow);
}
