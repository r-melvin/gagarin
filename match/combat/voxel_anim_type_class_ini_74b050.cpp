// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   VoxelAnimTypeClass::vf_25 (retail 0x74B050, 0x5CD bytes): the INI reader of the voxel animation type.
//   Every key string, destination offset, reader call and default was read off the user's retail
//   gamemd.exe v1.001 disassembly; field names are the INI key strings themselves.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../_layout/voxel_anim_type_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/voxel_resource_data.h"
#include "../platform/ccfile_class.h"
#include "../core/rules_class_ini_support.h"

// GLOBAL: GAMEMD 0x7E2800 -- 0.0, read from memory rather than FLDZ.
extern const double DAT_007E2800;
// GLOBAL: GAMEMD 0xA8EB28 -- the voxel animation type registry.
extern DynamicVectorClass<VoxelAnimTypeClass*> DAT_00A8EB28;
// FUNCTION: GAMEMD 0x74BB20 (decl; reloc) -- registry lookup-or-create by name; the registry arrives in EDX.
VoxelAnimTypeClass* __fastcall FUN_0074BB20(const char* id, DynamicVectorClass<VoxelAnimTypeClass*>* registry);

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
