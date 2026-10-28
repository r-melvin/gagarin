// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob1
// Native 0x5F8110..0x5F8CDA. The main file lives across the whole function;
// each optional model/animation pair has nested file-object lifetimes.
#include "../_layout/object_type_class.h"
#include "../_layout/techno_type_class.h"
#include "../platform/ccfile_class.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTION: GAMEMD 0x5F8110
void ObjectTypeClass::FUN_005F8110()
{
    bool failed = false;
    char path[260];
    char name[256];
    // STRING: GAMEMD 0x8194AC
    _makepath(path, 0, 0, ImageFile, ".VXL");
    CCFileClass mainFile(path);
    if (mainFile.Exists(0)) {
        delete MainVoxel.unknown_00;
        MainVoxel.unknown_00 = new Obj_00755D10(&mainFile, 0);
        if (!MainVoxel.unknown_00 || MainVoxel.unknown_00->unknown_00) failed = true;
        // STRING: GAMEMD 0x8194A0
        _makepath(path, 0, 0, ImageFile, ".HVA");
        CCFileClass animationFile(path);
        delete MainVoxel.HVAData;
        MainVoxel.HVAData = new Obj_005BD5A0(&animationFile);
        if (!MainVoxel.HVAData || MainVoxel.HVAData->unknown_00) failed = true;
        else MainVoxel.HVAData->FUN_005BD730(MainVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_0C);
    } else failed = true;

    // Native table 0x7F6218 slot 11 targets 0x748170 (returns 0x28).
    // Its raw RTTI lists UnitTypeClass -> TechnoTypeClass -> ObjectTypeClass
    // at offset zero, supporting these checked inherited-field accesses.
    if (vf_11() == 0x28 && !static_cast<TechnoTypeClass*>(this)->bools_C8C[21]) {
        // STRING: GAMEMD 0x832AE4
        if (strcmp(ID, "APC") == 0) {
            // STRING: GAMEMD 0x832AE0
            sprintf(name, "%sW", ImageFile.Data);
            _makepath(path, 0, 0, name, ".VXL");
            CCFileClass modelFile(path);
            if (modelFile.Exists(0)) {
                delete TurretVoxel.unknown_00;
                TurretVoxel.unknown_00 = new Obj_00755D10(&modelFile, 0);
                if (!TurretVoxel.unknown_00 || TurretVoxel.unknown_00->unknown_00) failed = true;
                sprintf(name, "%sW", ImageFile.Data);
                _makepath(path, 0, 0, name, ".HVA");
                CCFileClass animationFile(path);
                delete TurretVoxel.HVAData;
                TurretVoxel.HVAData = new Obj_005BD5A0(&animationFile);
                if (!TurretVoxel.HVAData || TurretVoxel.HVAData->unknown_00) failed = true;
                else TurretVoxel.HVAData->FUN_005BD730(TurretVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_0C);
            }
        }
        if (NoSpawnAlt) {
            // STRING: GAMEMD 0x832AD8
            sprintf(name, "%sWO", ImageFile.Data);
            _makepath(path, 0, 0, name, ".VXL");
            CCFileClass modelFile(path);
            if (modelFile.Exists(0)) {
                delete TurretVoxel.unknown_00;
                TurretVoxel.unknown_00 = new Obj_00755D10(&modelFile, 0);
                if (!TurretVoxel.unknown_00 || TurretVoxel.unknown_00->unknown_00) failed = true;
                sprintf(name, "%sWO", ImageFile.Data);
                _makepath(path, 0, 0, name, ".HVA");
                CCFileClass animationFile(path);
                delete TurretVoxel.HVAData;
                TurretVoxel.HVAData = new Obj_005BD5A0(&animationFile);
                if (!TurretVoxel.HVAData || TurretVoxel.HVAData->unknown_00) failed = true;
                else TurretVoxel.HVAData->FUN_005BD730(TurretVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_0C);
            }
        }
    } else {
        if (vf_11() == 0x28 && static_cast<TechnoTypeClass*>(this)->FUN_00717880()
            && !static_cast<TechnoTypeClass*>(this)->IsGattling) {
            for (int i = 0; i < static_cast<TechnoTypeClass*>(this)->TurretCount; ++i) {
                if (!FUN_005F7A90(ImageFile, i)) { failed = true; break; }
            }
        } else {
            // STRING: GAMEMD 0x832ABC
            sprintf(name, "%sTUR", ImageFile.Data);
            _makepath(path, 0, 0, name, ".VXL");
            CCFileClass modelFile(path);
            if (modelFile.Exists(0)) {
                delete TurretVoxel.unknown_00;
                TurretVoxel.unknown_00 = new Obj_00755D10(&modelFile, 0);
                if (!TurretVoxel.unknown_00 || TurretVoxel.unknown_00->unknown_00) failed = true;
                sprintf(name, "%sTUR", ImageFile.Data);
                _makepath(path, 0, 0, name, ".HVA");
                CCFileClass animationFile(path);
                delete TurretVoxel.HVAData;
                TurretVoxel.HVAData = new Obj_005BD5A0(&animationFile);
                if (!TurretVoxel.HVAData || TurretVoxel.HVAData->unknown_00) failed = true;
                else TurretVoxel.HVAData->FUN_005BD730(TurretVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_0C);
            }
        }
    }
    if (vf_11() != 0x28 || static_cast<TechnoTypeClass*>(this)->bools_C8C[21]) {
        if (vf_11() == 0x28 && static_cast<TechnoTypeClass*>(this)->FUN_00717880()
            && !static_cast<TechnoTypeClass*>(this)->IsGattling) {
            for (int i = 0; i < static_cast<TechnoTypeClass*>(this)->TurretCount; ++i) {
                if (!FUN_005F7DB0(ImageFile, i)) { failed = true; break; }
            }
        } else {
            // STRING: GAMEMD 0x832AD0
            sprintf(name, "%sBARL", ImageFile.Data);
            _makepath(path, 0, 0, name, ".VXL");
            CCFileClass modelFile(path);
            if (modelFile.Exists(0)) {
                delete BarrelVoxel.unknown_00;
                BarrelVoxel.unknown_00 = new Obj_00755D10(&modelFile, 0);
                if (!BarrelVoxel.unknown_00 || BarrelVoxel.unknown_00->unknown_00) failed = true;
                sprintf(name, "%sBARL", ImageFile.Data);
                _makepath(path, 0, 0, name, ".HVA");
                CCFileClass animationFile(path);
                delete BarrelVoxel.HVAData;
                BarrelVoxel.HVAData = new Obj_005BD5A0(&animationFile);
                if (!BarrelVoxel.HVAData || BarrelVoxel.HVAData->unknown_00) failed = true;
                else BarrelVoxel.HVAData->FUN_005BD730(BarrelVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_0C);
            }
        }
    }
    if (failed) {
        if (MainVoxel.unknown_00) {
            delete MainVoxel.unknown_00;
            MainVoxel.unknown_00 = 0;
        }
        if (MainVoxel.HVAData) {
            delete MainVoxel.HVAData;
            MainVoxel.HVAData = 0;
        }
        if (vf_11() == 0x28 && static_cast<TechnoTypeClass*>(this)->FUN_00717880()
            && !static_cast<TechnoTypeClass*>(this)->IsGattling) {
            FUN_005F8080();
        } else {
            // Native 0x5F8AD5..0x5F8B19 clears the turret pair here.
            if (TurretVoxel.unknown_00) {
                delete TurretVoxel.unknown_00;
                TurretVoxel.unknown_00 = 0;
            }
            if (TurretVoxel.HVAData) {
                delete TurretVoxel.HVAData;
                TurretVoxel.HVAData = 0;
            }
        }
    } else {
        int dimension = MainVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_A0[0];
        // Native compares the stored count as signed in this reader.
        for (int i = 0; i < static_cast<int>(MainVoxel.unknown_00->unknown_04); ++i) {
            if (dimension <= MainVoxel.unknown_00->FUN_007564b0(i, 0)->unknown_A0[0])
                dimension = MainVoxel.unknown_00->FUN_007564b0(i, 0)->unknown_A0[0];
            if (dimension <= MainVoxel.unknown_00->FUN_007564b0(i, 0)->unknown_A0[1])
                dimension = MainVoxel.unknown_00->FUN_007564b0(i, 0)->unknown_A0[1];
            if (dimension <= MainVoxel.unknown_00->FUN_007564b0(i, 0)->unknown_A0[2])
                dimension = MainVoxel.unknown_00->FUN_007564b0(i, 0)->unknown_A0[2];
        }
        if (dimension <= 8) dimension = 8;
        MaxDimension = dimension;
        VoxelMainCache.ResetStorage();
        VoxelTurretWeaponCache.ResetStorage();
        VoxelShadowCache.ResetStorage();
        VoxelTurretBarrelCache.ResetStorage();
    }
}
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_C8C) + 21 == 0xCA1);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->bools_C8C[21]) == 1);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, IsGattling) == 0xCD5);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, TurretCount) == 0x808);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, MainVoxel) == 0xb0);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, TurretVoxel) == 0xb8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, BarrelVoxel) == 0xc0);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageFile) == 0x1f8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, NoSpawnAlt) == 0x1e8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, MaxDimension) == 0x1ec);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelMainCache) == 0x244);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelTurretWeaponCache) == 0x258);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelShadowCache) == 0x26c);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelTurretBarrelCache) == 0x280);
