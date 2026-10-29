// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x5F8CE0..0x5F9061 updates the optional turret/barrel pairs when
// the kind is 0x28, virtual slot39 returns a pointer, and byte +0xCA1 is set.
#include "../_layout/object_type_class.h"
#include "../_layout/techno_type_class.h"
#include "../platform/ccfile_class.h"
#include <stdio.h>
#include <stdlib.h>

// FUNCTION: GAMEMD 0x5F8CE0
void ObjectTypeClass::FUN_005F8CE0()
{
    // Native UnitType RTTI at table7F6218 lists the TechnoType base at +0.
    if (vf_11() == 0x28 && vf_39() && static_cast<TechnoTypeClass*>(this)->bools_C8C[21]) {
        char name[256];
        char path[260];
        // STRING: GAMEMD 0x832ABC
        sprintf(name, "%sTUR", ImageFile.Data);
        // STRING: GAMEMD 0x8194AC
        _makepath(path, 0, 0, name, ".VXL");
        CCFileClass turretFile(path);
        if (turretFile.Exists(0)) {
            delete TurretVoxel.unknown_00;
            TurretVoxel.unknown_00 = new Obj_00755D10(&turretFile, 0);
            if (TurretVoxel.unknown_00 && !TurretVoxel.unknown_00->unknown_00) {
                sprintf(name, "%sTUR", ImageFile.Data);
                // STRING: GAMEMD 0x8194A0
                _makepath(path, 0, 0, name, ".HVA");
                CCFileClass animationFile(path);
                delete TurretVoxel.HVAData;
                TurretVoxel.HVAData = new Obj_005BD5A0(&animationFile);
                TurretVoxel.HVAData->FUN_005BD730(TurretVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_0C);
            }
        }
        // STRING: GAMEMD 0x832AD0
        sprintf(name, "%sBARL", ImageFile.Data);
        _makepath(path, 0, 0, name, ".VXL");
        CCFileClass barrelFile(path);
        if (barrelFile.Exists(0)) {
            delete BarrelVoxel.unknown_00;
            BarrelVoxel.unknown_00 = new Obj_00755D10(&barrelFile, 0);
            if (BarrelVoxel.unknown_00 && !BarrelVoxel.unknown_00->unknown_00) {
                sprintf(name, "%sBARL", ImageFile.Data);
                _makepath(path, 0, 0, name, ".HVA");
                CCFileClass animationFile(path);
                delete BarrelVoxel.HVAData;
                BarrelVoxel.HVAData = new Obj_005BD5A0(&animationFile);
                BarrelVoxel.HVAData->FUN_005BD730(BarrelVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_0C);
            }
        }
    }
}
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_C8C) + 21 == 0xCA1);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->bools_C8C[21]) == 1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageFile) == 0x1F8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, TurretVoxel) == 0xB8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, BarrelVoxel) == 0xC0);
