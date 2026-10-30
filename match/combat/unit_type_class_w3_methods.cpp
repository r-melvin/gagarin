// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   UnitTypeClass virtual overrides read off retail gamemd.exe v1.001 (vtable of
//   UnitTypeClass, RTTI-named). Functions are in ascending retail address order.

#include <new.h>
#include "../_layout/unit_type_class.h"
#include "../_layout/unit_class.h"
#include "../_layout/obj_004a1d30.h"

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
