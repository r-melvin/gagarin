// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry-point disassembly 0x46BEE0..0x46C435 establishes calls, field offsets,
// key addresses and both return paths. Names are native INI key strings.
#include "bullet_type_class.h"
#include "weapon_type_class.h"
#include "_layout/anim_type_class.h"
#include "ccini_class_methods.h"

// GLOBAL: GAMEMD 0x887180 -- art INI selected by native immediate receivers.
extern CCINIClass DAT_00887180;
// STRING: GAMEMD 0x889F64 -- shared empty default text.
extern const char DAT_00889F64[];

// FUNCTION: GAMEMD 0x46BEE0
bool BulletTypeClass::vf_25(CCINIClass* ini)
{
    ini->Reset();
    if (ObjectTypeClass::vf_25(ini))
    {
        char buffer[128];
        // STRING: GAMEMD 0x81B168
        Arm = ini->FUN_005276D0(ID, "Arm", Arm);
        // STRING: GAMEMD 0x81B164
        ROT = ini->FUN_005276D0(ID, "ROT", ROT);
        // STRING: GAMEMD 0x81B150
        CourseLockDuration = ini->FUN_005276D0(ID, "CourseLockDuration", CourseLockDuration);
        // STRING: GAMEMD 0x8184F4
        Elasticity = ini->FUN_005283D0(ID, "Elasticity", Elasticity);
        // STRING: GAMEMD 0x81B140
        Acceleration = ini->FUN_005276D0(ID, "Acceleration", Acceleration);
        // STRING: GAMEMD 0x81B138
        Color = ini->ReadColorScheme(ID, "Color", Color);
        // STRING: GAMEMD 0x81B130
        Arcing = ini->FUN_005295F0(ID, "Arcing", Arcing);
        // STRING: GAMEMD 0x81B128
        Floater = ini->FUN_005295F0(ID, "Floater", Floater);
        // STRING: GAMEMD 0x81B118
        SubjectToCliffs = ini->FUN_005295F0(ID, "SubjectToCliffs", SubjectToCliffs);
        // STRING: GAMEMD 0x81B104
        SubjectToElevation = ini->FUN_005295F0(ID, "SubjectToElevation", SubjectToElevation);
        // STRING: GAMEMD 0x81B0F4
        SubjectToWalls = ini->FUN_005295F0(ID, "SubjectToWalls", SubjectToWalls);
        // STRING: GAMEMD 0x81B0E8
        VeryHigh = ini->FUN_005295F0(ID, "VeryHigh", VeryHigh);
        // STRING: GAMEMD 0x818660
        Shadow = ini->FUN_005295F0(ID, "Shadow", Shadow);
        // STRING: GAMEMD 0x81B0DC
        Dropping = ini->FUN_005295F0(ID, "Dropping", Dropping);
        // STRING: GAMEMD 0x81B0D4
        Level = ini->FUN_005295F0(ID, "Level", Level);
        // STRING: GAMEMD 0x81B0CC
        Inviso = ini->FUN_005295F0(ID, "Inviso", Inviso);
        // STRING: GAMEMD 0x81B0C0
        Proximity = ini->FUN_005295F0(ID, "Proximity", Proximity);
        // STRING: GAMEMD 0x81B0B8
        Ranged = ini->FUN_005295F0(ID, "Ranged", Ranged);
        // STRING: GAMEMD 0x81B0AC
        Inaccurate = ini->FUN_005295F0(ID, "Inaccurate", Inaccurate);
        // STRING: GAMEMD 0x81B0A0
        FlakScatter = ini->FUN_005295F0(ID, "FlakScatter", FlakScatter);
        // STRING: GAMEMD 0x81B09C
        AA = ini->FUN_005295F0(ID, "AA", AA);
        // STRING: GAMEMD 0x81B098
        AG = ini->FUN_005295F0(ID, "AG", AG);
        // STRING: GAMEMD 0x81B08C
        Degenerates = ini->FUN_005295F0(ID, "Degenerates", Degenerates);
        // STRING: GAMEMD 0x81B084
        Bouncy = ini->FUN_005295F0(ID, "Bouncy", Bouncy);
        // STRING: GAMEMD 0x81B078
        Airburst = ini->FUN_005295F0(ID, "Airburst", Airburst);
        // STRING: GAMEMD 0x81B070
        Cluster = ini->FUN_005276D0(ID, "Cluster", Cluster);
        // STRING: GAMEMD 0x81B064
        Scalable = ini->FUN_005295F0(ID, "Scalable", Scalable);
        // STRING: GAMEMD 0x819420
        if (ini->FUN_00528A10(ID, "Image", DAT_00889F64, ImageFile, 25) > 0)
        {
            AnimTypeClass* trailer = Trailer;
            // STRING: GAMEMD 0x81800C
            if (DAT_00887180.FUN_00528A10(ImageFile, "Trailer", DAT_00889F64, buffer, 128))
                trailer = AnimTypeClass::FindOrAllocate(buffer);
            Trailer = trailer;
            // STRING: GAMEMD 0x818000
            SpawnDelay = DAT_00887180.FUN_005276D0(ImageFile, "SpawnDelay", SpawnDelay);
            // STRING: GAMEMD 0x81B05C
            Rotates = !DAT_00887180.FUN_005295F0(ImageFile, "Rotates", !Rotates);
            // STRING: GAMEMD 0x818624
            Flat = DAT_00887180.FUN_005295F0(ImageFile, "Flat", Flat);
        }
        WeaponTypeClass* airburst = AirburstWeapon;
        // STRING: GAMEMD 0x81B04C
        if (ini->FUN_00528A10(ID, "AirburstWeapon", DAT_00889F64, buffer, 128))
            airburst = WeaponTypeClass::FindOrAllocate(buffer);
        AirburstWeapon = airburst;
        WeaponTypeClass* shrapnel = ShrapnelWeapon;
        // STRING: GAMEMD 0x81B03C
        if (ini->FUN_00528A10(ID, "ShrapnelWeapon", DAT_00889F64, buffer, 128))
            shrapnel = WeaponTypeClass::FindOrAllocate(buffer);
        ShrapnelWeapon = shrapnel;
        // STRING: GAMEMD 0x81B02C
        ShrapnelCount = ini->FUN_005276D0(ID, "ShrapnelCount", ShrapnelCount);
        // STRING: GAMEMD 0x81B018
        DetonationAltitude = ini->FUN_005276D0(ID, "DetonationAltitude", DetonationAltitude);
        // STRING: GAMEMD 0x81B00C
        Vertical = ini->FUN_005295F0(ID, "Vertical", Vertical);
        // STRING: GAMEMD 0x81AFFC
        FirersPalette = ini->FUN_005295F0(ID, "FirersPalette", FirersPalette);
        // STRING: GAMEMD 0x81AFF4
        AnimLow = DAT_00887180.FUN_005276D0(ImageFile, "AnimLow", AnimLow);
        // STRING: GAMEMD 0x81AFE8
        AnimHigh = DAT_00887180.FUN_005276D0(ImageFile, "AnimHigh", AnimHigh);
        // STRING: GAMEMD 0x81AFDC
        AnimRate = DAT_00887180.FUN_005276D0(ImageFile, "AnimRate", AnimRate);
        // STRING: GAMEMD 0x81AFD0
        AnimPalette = DAT_00887180.FUN_005295F0(ImageFile, "AnimPalette", AnimPalette);
        if (!Inviso)
            FUN_005F9070();
        if (Voxel)
            FUN_005F8110();
        return true;
    }
    return false;
}
