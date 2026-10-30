// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   VoxelAnimTypeClass destruction and stream loading, read off retail gamemd.exe v1.001
//   (vtable 0x7F6548). /Ob2: the scalar deleting destructor carries the destructor body
//   inline, and the no-initialisation constructor is expanded in Load.
//   Address index: 0x74AF70 dtor, 0x74B810 Load, 0x74BA30 deleting dtor.

#include <new.h>
#include "../_layout/voxel_anim_type_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_class_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../_layout/techno_type_class.h"
#include "../_layout/voxel_resource_data.h"
#include "../platform/ccfile_class.h"
#include "../core/rules_class_ini_support.h"

// GLOBAL: GAMEMD 0x7E2800
extern const double DAT_007E2800;
// FUNCTION: GAMEMD 0x74BB20 (decl; reloc)
VoxelAnimTypeClass* __fastcall FUN_0074BB20(const char* id, DynamicVectorClass<VoxelAnimTypeClass*>* registry);


// GLOBAL: GAMEMD 0xB0F670 -- the shared object registry.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F670;
// GLOBAL: GAMEMD 0xA8EB28 -- the voxel animation type registry.
extern DynamicVectorClass<VoxelAnimTypeClass*> DAT_00A8EB28;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// FUNCTION: GAMEMD 0x74AF70
VoxelAnimTypeClass::~VoxelAnimTypeClass()
{
    AnnounceExpiredPointer(1);
    DAT_00B0F670.RemoveItem(this);
    DAT_00A8EB28.RemoveItem(this);
    if (unknown_296) {
        MainVoxel.unknown_00 = 0;
        MainVoxel.HVAData = 0;
    }
}

// FUNCTION: GAMEMD 0x74B050
// Reads the voxel animation type's rules section: the object type reader first, then every key over its
// current value. The model is shared from another type when a Share* key asks, else loaded from the image file.
bool VoxelAnimTypeClass::vf_25(CCINIClass* ini)
{
    char path[0x200];
    bool shareBody;
    bool shareTurret;
    bool shareBarrel;

    ini->Reset();
    if (ObjectTypeClass::vf_25(ini)) {
        {
            char buffer[0x80];
            // STRING: GAMEMD 0x818610
            Normalized = ini->ReadBool(ID.Data, "Normalized", Normalized);
            // STRING: GAMEMD 0x818604
            Translucent = ini->ReadBool(ID.Data, "Translucent", Translucent);
            // STRING: GAMEMD 0x818518
            IsTiberium = ini->ReadBool(ID.Data, "IsTiberium", IsTiberium);
            // STRING: GAMEMD 0x8184B0
            IsMeteor = ini->ReadBool(ID.Data, "IsMeteor", IsMeteor);
            // STRING: GAMEMD 0x8184F4
            Elasticity = ini->ReadDouble(ID.Data, "Elasticity", Elasticity);
            // STRING: GAMEMD 0x845F14
            double minAngular = ini->ReadDouble(ID.Data, "MinAngularVelocity", -1.0);
            if (minAngular != DAT_007E2800)
                MinAngularVelocity = minAngular * 0.01745277777777778;
            // STRING: GAMEMD 0x845F00
            double maxAngular = ini->ReadDouble(ID.Data, "MaxAngularVelocity", -1.0);
            if (maxAngular != DAT_007E2800)
                MaxAngularVelocity = maxAngular * 0.01745277777777778;
            // STRING: GAMEMD 0x845EF4
            Duration = ini->ReadInteger(ID.Data, "Duration", Duration);
            // STRING: GAMEMD 0x8184E0
            MinZVel = ini->ReadDouble(ID.Data, "MinZVel", MinZVel);
            // STRING: GAMEMD 0x845EEC
            MaxZVel = ini->ReadDouble(ID.Data, "MaxZVel", MaxZVel);
            // STRING: GAMEMD 0x8184E8
            MaxXYVel = ini->ReadDouble(ID.Data, "MaxXYVel", MaxXYVel);
            // STRING: GAMEMD 0x8184C8
            { void* t = Spawns; Spawns = ini->ReadString(ID.Data, "Spawns", STR_00889F64, buffer, 0x80) ? FUN_0074BB20(buffer, &DAT_00A8EB28) : t; }
            // STRING: GAMEMD 0x8184BC
            SpawnCount = ini->ReadInteger(ID.Data, "SpawnCount", SpawnCount);
            // STRING: GAMEMD 0x845EDC
            shareBody = ini->ReadBool(ID.Data, "ShareBodyData", false);
            // STRING: GAMEMD 0x845ECC
            shareTurret = ini->ReadBool(ID.Data, "ShareTurretData", false);
            // STRING: GAMEMD 0x845EBC
            shareBarrel = ini->ReadBool(ID.Data, "ShareBarrelData", false);
            // STRING: GAMEMD 0x845EB0
            VoxelIndex = ini->ReadInteger(ID.Data, "VoxelIndex", VoxelIndex);
            // STRING: GAMEMD 0x818418
            { int t = StartSound; int index; StartSound = (ini->ReadString(ID.Data, "StartSound", STR_00889F64, buffer, 0x80) && (index = VocClass::FindIndex(buffer)) != -1) ? index : t; }
            // STRING: GAMEMD 0x818404
            { int t = StopSound; int index; StopSound = (ini->ReadString(ID.Data, "StopSound", STR_00889F64, buffer, 0x80) && (index = VocClass::FindIndex(buffer)) != -1) ? index : t; }
            // STRING: GAMEMD 0x8183F8
            { void* t = BounceAnim; BounceAnim = ini->ReadString(ID.Data, "BounceAnim", STR_00889F64, buffer, 0x80) ? AnimType_FindPtr(buffer) : t; }
            // STRING: GAMEMD 0x8183EC
            { void* t = ExpireAnim; ExpireAnim = ini->ReadString(ID.Data, "ExpireAnim", STR_00889F64, buffer, 0x80) ? AnimType_FindPtr(buffer) : t; }
            // STRING: GAMEMD 0x8183E0
            { void* t = TrailerAnim; TrailerAnim = ini->ReadString(ID.Data, "TrailerAnim", STR_00889F64, buffer, 0x80) ? AnimType_FindPtr(buffer) : t; }
            // STRING: GAMEMD 0x81859C
            Damage = ini->ReadInteger(ID.Data, "Damage", Damage);
            // STRING: GAMEMD 0x8183BC
            DamageRadius = ini->ReadInteger(ID.Data, "DamageRadius", DamageRadius);
            // STRING: GAMEMD 0x8183B4
            { void* t = Warhead; Warhead = ini->ReadString(ID.Data, "Warhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t; }
            // STRING: GAMEMD 0x845EA0
            { void* t = AttachedSystem; AttachedSystem = ini->ReadString(ID.Data, "AttachedSystem", STR_00889F64, buffer, 0x80) ? ParticleSystemType_FindPtr(buffer) : t; }
        }
        unknown_296 = shareBody || shareBarrel || shareTurret;
        if (unknown_296) {
            // STRING: GAMEMD 0x845E94
            TechnoTypeClass* source = ini->GetTechnoType(ID.Data, "ShareSource");
            if (source) {
                if (shareBody) {
                    MainVoxel.unknown_00 = source->MainVoxel.unknown_00;
                    MainVoxel.HVAData = source->MainVoxel.HVAData;
                    return true;
                }
                if (shareTurret) {
                    MainVoxel.unknown_00 = source->TurretVoxel.unknown_00;
                    MainVoxel.HVAData = source->TurretVoxel.HVAData;
                    return true;
                }
                if (shareBarrel) {
                    MainVoxel.unknown_00 = source->BarrelVoxel.unknown_00;
                    MainVoxel.HVAData = source->BarrelVoxel.HVAData;
                    return true;
                }
            } else {
                MainVoxel.unknown_00 = 0;
                MainVoxel.HVAData = 0;
                return true;
            }
        } else {
            // STRING: GAMEMD 0x8194AC
            _makepath(path, 0, 0, ImageFile, ".VXL");
            CCFileClass file(path);
            delete MainVoxel.unknown_00;
            MainVoxel.unknown_00 = new Obj_00755D10(&file, 0);
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x74B690
void VoxelAnimTypeClass::vf_13(Obj_004A1D30* crc)
{
    ObjectTypeClass::vf_13(crc);
    crc->FUN_004A1CA0(Normalized);
    crc->FUN_004A1CA0(Translucent);
    crc->FUN_004A1CA0(unknown_296);
    crc->FUN_004A1D50(VoxelIndex);
    crc->FUN_004A1D50(Duration);
    crc->FUN_004A1D90(Elasticity);
    crc->FUN_004A1D90(MinAngularVelocity);
    crc->FUN_004A1D90(MaxAngularVelocity);
    crc->FUN_004A1D90(MinZVel);
    crc->FUN_004A1D90(MaxZVel);
    crc->FUN_004A1D90(MaxXYVel);
    crc->FUN_004A1CA0(IsMeteor);
    crc->FUN_004A1D50(SpawnCount);
    crc->FUN_004A1D50(StartSound);
    crc->FUN_004A1D50(StopSound);
    crc->FUN_004A1D50(Damage);
    crc->FUN_004A1D50(DamageRadius);
    crc->FUN_004A1CA0(IsTiberium);
}

// FUNCTION: GAMEMD 0x74B810
// Reads the stream, rebuilds the object in place and re-registers its pointers.
HRESULT __stdcall VoxelAnimTypeClass::Load(IStream* pStm)
{
    HRESULT hr = ObjectTypeClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) VoxelAnimTypeClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Warhead);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&BounceAnim);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&ExpireAnim);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&TrailerAnim);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Spawns);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&AttachedSystem);
    FUN_005F8110();
    return 0;
}

// FUNCTION: GAMEMD 0x74B9F0
int VoxelAnimTypeClass::vf_11()
{
    return 0x2A;
}

// FUNCTION: GAMEMD 0x74BA00
int VoxelAnimTypeClass::vf_12()
{
    return 0x308;
}

// FUNCTION: GAMEMD 0x74BA10
bool VoxelAnimTypeClass::vf_32(const CellStruct* cell, HouseClass* house)
{
    return false;
}

// FUNCTION: GAMEMD 0x74BA20
ObjectClass* VoxelAnimTypeClass::vf_35(HouseClass* house)
{
    return 0;
}

// SYNTHETIC: GAMEMD 0x74BA30
// VoxelAnimTypeClass scalar deleting destructor (primary slot 8), the destructor expanded in place.
