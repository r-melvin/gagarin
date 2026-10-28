// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry-point disassembly 0x46BEE0..0x46C435 establishes calls, field offsets,
// key addresses and both return paths. Names are native INI key strings.
#include "bullet_type_class.h"
#include "weapon_type_class.h"
#include "../_layout/anim_type_class.h"
#include "../platform/ccini_class_methods.h"

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
        unknown_2F0 = ini->FUN_005276D0(ID, "Arm", unknown_2F0);
        // STRING: GAMEMD 0x81B164
        unknown_2DC = ini->FUN_005276D0(ID, "ROT", unknown_2DC);
        // STRING: GAMEMD 0x81B150
        unknown_2E0 = ini->FUN_005276D0(ID, "CourseLockDuration", unknown_2E0);
        // STRING: GAMEMD 0x8184F4
        unknown_2C8 = ini->FUN_005283D0(ID, "Elasticity", unknown_2C8);
        // STRING: GAMEMD 0x81B140
        unknown_2D0 = ini->FUN_005276D0(ID, "Acceleration", unknown_2D0);
        // STRING: GAMEMD 0x81B138
        unknown_2D4 = ini->ReadColorScheme(ID, "Color", unknown_2D4);
        // STRING: GAMEMD 0x81B130
        unknown_29B = ini->FUN_005295F0(ID, "Arcing", unknown_29B);
        // STRING: GAMEMD 0x81B128
        unknown_295 = ini->FUN_005295F0(ID, "Floater", unknown_295);
        // STRING: GAMEMD 0x81B118
        unknown_296 = ini->FUN_005295F0(ID, "SubjectToCliffs", unknown_296);
        // STRING: GAMEMD 0x81B104
        unknown_297 = ini->FUN_005295F0(ID, "SubjectToElevation", unknown_297);
        // STRING: GAMEMD 0x81B0F4
        unknown_298 = ini->FUN_005295F0(ID, "SubjectToWalls", unknown_298);
        // STRING: GAMEMD 0x81B0E8
        unknown_299 = ini->FUN_005295F0(ID, "VeryHigh", unknown_299);
        // STRING: GAMEMD 0x818660
        unknown_29A = ini->FUN_005295F0(ID, "Shadow", unknown_29A);
        // STRING: GAMEMD 0x81B0DC
        unknown_29C = ini->FUN_005295F0(ID, "Dropping", unknown_29C);
        // STRING: GAMEMD 0x81B0D4
        unknown_29D = ini->FUN_005295F0(ID, "Level", unknown_29D);
        // STRING: GAMEMD 0x81B0CC
        unknown_29E = ini->FUN_005295F0(ID, "Inviso", unknown_29E);
        // STRING: GAMEMD 0x81B0C0
        unknown_29F = ini->FUN_005295F0(ID, "Proximity", unknown_29F);
        // STRING: GAMEMD 0x81B0B8
        unknown_2A0 = ini->FUN_005295F0(ID, "Ranged", unknown_2A0);
        // STRING: GAMEMD 0x81B0AC
        unknown_2A2 = ini->FUN_005295F0(ID, "Inaccurate", unknown_2A2);
        // STRING: GAMEMD 0x81B0A0
        unknown_2A3 = ini->FUN_005295F0(ID, "FlakScatter", unknown_2A3);
        // STRING: GAMEMD 0x81B09C
        unknown_2A4 = ini->FUN_005295F0(ID, "AA", unknown_2A4);
        // STRING: GAMEMD 0x81B098
        unknown_2A5 = ini->FUN_005295F0(ID, "AG", unknown_2A5);
        // STRING: GAMEMD 0x81B08C
        unknown_2A6 = ini->FUN_005295F0(ID, "Degenerates", unknown_2A6);
        // STRING: GAMEMD 0x81B084
        unknown_2A7 = ini->FUN_005295F0(ID, "Bouncy", unknown_2A7);
        // STRING: GAMEMD 0x81B078
        unknown_294 = ini->FUN_005295F0(ID, "Airburst", unknown_294);
        // STRING: GAMEMD 0x81B070
        unknown_2AC = ini->FUN_005276D0(ID, "Cluster", unknown_2AC);
        // STRING: GAMEMD 0x81B064
        unknown_2EC = ini->FUN_005295F0(ID, "Scalable", unknown_2EC);
        // STRING: GAMEMD 0x819420
        if (ini->FUN_00528A10(ID, "Image", DAT_00889F64, ImageFile, 25) > 0)
        {
            AnimTypeClass* trailer = unknown_2D8;
            // STRING: GAMEMD 0x81800C
            if (DAT_00887180.FUN_00528A10(ImageFile, "Trailer", DAT_00889F64, buffer, 128))
                trailer = AnimTypeClass::FindOrAllocate(buffer);
            unknown_2D8 = trailer;
            // STRING: GAMEMD 0x818000
            unknown_2E4 = DAT_00887180.FUN_005276D0(ImageFile, "SpawnDelay", unknown_2E4);
            // STRING: GAMEMD 0x81B05C
            unknown_2A1 = !DAT_00887180.FUN_005295F0(ImageFile, "Rotates", !unknown_2A1);
            // STRING: GAMEMD 0x818624
            unknown_2F7 = DAT_00887180.FUN_005295F0(ImageFile, "Flat", unknown_2F7);
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
        unknown_2BC = ini->FUN_005276D0(ID, "DetonationAltitude", unknown_2BC);
        // STRING: GAMEMD 0x81B00C
        unknown_2C0 = ini->FUN_005295F0(ID, "Vertical", unknown_2C0);
        // STRING: GAMEMD 0x81AFFC
        unknown_2A9 = ini->FUN_005295F0(ID, "FirersPalette", unknown_2A9);
        // STRING: GAMEMD 0x81AFF4
        unknown_2F4 = DAT_00887180.FUN_005276D0(ImageFile, "AnimLow", unknown_2F4);
        // STRING: GAMEMD 0x81AFE8
        unknown_2F5 = DAT_00887180.FUN_005276D0(ImageFile, "AnimHigh", unknown_2F5);
        // STRING: GAMEMD 0x81AFDC
        unknown_2F6 = DAT_00887180.FUN_005276D0(ImageFile, "AnimRate", unknown_2F6);
        // STRING: GAMEMD 0x81AFD0
        unknown_2A8 = DAT_00887180.FUN_005295F0(ImageFile, "AnimPalette", unknown_2A8);
        if (!unknown_29E)
            FUN_005F9070();
        if (Voxel)
            FUN_005F8110();
        return true;
    }
    return false;
}
