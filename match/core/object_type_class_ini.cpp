// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native entry 0x5F92D0..0x5F96A9 reads rules and art keys into the shared
// ObjectType layout. Key addresses, field widths and both return paths were
// checked from entry-point disassembly; sound and RGB readers use shared APIs.
#include "../_layout/object_type_class.h"
#include "../platform/ccini_class_methods.h"
#include "../audio/voc_class_methods.h"
#include <string.h>
#include <stdlib.h>

// GLOBAL: GAMEMD 0x887180 -- art INI receiver in the native read calls.
extern CCINIClass DAT_00887180;
// STRING: GAMEMD 0x889F64 -- shared empty default text.
extern const char DAT_00889F64[];
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc), ECX=path, DL=force.
void* __fastcall MixFileClass_Retrieve(char* path, bool force);

GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ID) == 0x24);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ID) == 0x19);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageFile) == 0x1F8);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ImageFile) == 0x19);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlphaImageFile) == 0x213);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AlphaImageFile) == 0x19);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, CrushSound) == 0x1F0);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->CrushSound) == 0x4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AmbientSound) == 0x1F4);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AmbientSound) == 0x4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Crushable) == 0x22D);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Crushable) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Bombable) == 0x22E);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Bombable) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, NoSpawnAlt) == 0x1E8);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->NoSpawnAlt) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlternateArcticArt) == 0x211);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AlternateArcticArt) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, RadarInvisible) == 0x22F);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->RadarInvisible) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Selectable) == 0x230);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Selectable) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LegalTarget) == 0x231);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->LegalTarget) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Armor) == 0x9C);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Armor) == 0x4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Strength) == 0xA0);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Strength) == 0x4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Immune) == 0x233);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Immune) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Insignificant) == 0x232);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Insignificant) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, HasRadialIndicator) == 0x238);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->HasRadialIndicator) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, RadialColor) == 0x98);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->RadialColor) == 0x3);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, IgnoresFirestorm) == 0x239);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->IgnoresFirestorm) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, UseLineTrail) == 0x23A);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->UseLineTrail) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LineTrailColor) == 0x23B);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->LineTrailColor) == 0x3);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LineTrailColorDecrement) == 0x240);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->LineTrailColorDecrement) == 0x4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Theater) == 0x22C);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Theater) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, NewTheater) == 0x237);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->NewTheater) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Voxel) == 0x236);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Voxel) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlphaImage) == 0xAC);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AlphaImage) == 0x4);

// FUNCTION: GAMEMD 0x5F92D0
bool ObjectTypeClass::vf_25(CCINIClass* ini)
{
    ini->Reset();
    if (AbstractTypeClass::vf_25(ini))
    {
        char previous[25];
        char soundName[128];
        char path[260];
        strcpy(previous, ImageFile);
        // STRING: GAMEMD 0x819420
        ini->FUN_00528A10(ID, "Image", previous, ImageFile, 25);
        strcpy(previous, AlphaImageFile);
        // STRING: GAMEMD 0x832C00
        ini->FUN_00528A10(ID, "AlphaImage", previous, AlphaImageFile, 25);

        int sound = CrushSound;
        // STRING: GAMEMD 0x832BF4
        if (ini->FUN_00528A10(ID, "CrushSound", DAT_00889F64, soundName, 128))
        {
            int found = VocClass::FindIndex(soundName);
            if (found != -1)
                sound = found;
        }
        CrushSound = sound;
        sound = AmbientSound;
        int ambient = -1;
        // STRING: GAMEMD 0x832BE4
        if (ini->FUN_00528A10(ID, "AmbientSound", DAT_00889F64, soundName, 128))
            ambient = VocClass::FindIndex(soundName);
        AmbientSound = ambient != -1 ? ambient : sound;
        // STRING: GAMEMD 0x832BD8
        Crushable = ini->FUN_005295F0(ID, "Crushable", Crushable);
        // STRING: GAMEMD 0x832BCC
        Bombable = ini->FUN_005295F0(ID, "Bombable", Bombable);
        // STRING: GAMEMD 0x832BC0
        NoSpawnAlt = ini->FUN_005295F0(ID, "NoSpawnAlt", NoSpawnAlt);
        // STRING: GAMEMD 0x832BAC
        AlternateArcticArt = ini->FUN_005295F0(ID, "AlternateArcticArt", AlternateArcticArt);
        // STRING: GAMEMD 0x832B9C
        RadarInvisible = ini->FUN_005295F0(ID, "RadarInvisible", RadarInvisible);
        // STRING: GAMEMD 0x832B90
        Selectable = ini->FUN_005295F0(ID, "Selectable", Selectable);
        // STRING: GAMEMD 0x832B84
        LegalTarget = ini->FUN_005295F0(ID, "LegalTarget", LegalTarget);
        // STRING: GAMEMD 0x81D9D4
        Armor = ini->ReadArmor(ID, "Armor", Armor);
        // STRING: GAMEMD 0x832B78
        Strength = ini->FUN_005276D0(ID, "Strength", Strength);
        // STRING: GAMEMD 0x832B70
        Immune = ini->FUN_005295F0(ID, "Immune", Immune);
        // STRING: GAMEMD 0x832B60
        Insignificant = ini->FUN_005295F0(ID, "Insignificant", Insignificant);
        // STRING: GAMEMD 0x832B4C
        HasRadialIndicator = ini->FUN_005295F0(ID, "HasRadialIndicator", HasRadialIndicator);
        // STRING: GAMEMD 0x832B40
        RadialColor = ini->Read3Bytes(ID, "RadialColor", RadialColor);
        // STRING: GAMEMD 0x832B2C
        IgnoresFirestorm = ini->FUN_005295F0(ID, "IgnoresFirestorm", IgnoresFirestorm);
        // STRING: GAMEMD 0x832B1C
        UseLineTrail = DAT_00887180.FUN_005295F0(ImageFile, "UseLineTrail", UseLineTrail);
        // STRING: GAMEMD 0x832B0C
        LineTrailColor = DAT_00887180.Read3Bytes(ImageFile, "LineTrailColor", LineTrailColor);
        // STRING: GAMEMD 0x832AF4
        LineTrailColorDecrement = DAT_00887180.FUN_005276D0(ImageFile, "LineTrailColorDecrement", LineTrailColorDecrement);
        // STRING: GAMEMD 0x818658
        Theater = DAT_00887180.FUN_005295F0(ImageFile, "Theater", Theater);
        // STRING: GAMEMD 0x81864C
        NewTheater = DAT_00887180.FUN_005295F0(ImageFile, "NewTheater", NewTheater);
        // STRING: GAMEMD 0x832AEC
        Voxel = DAT_00887180.FUN_005295F0(ImageFile, "Voxel", Voxel);
        if (!Voxel && vf_11() != 5)
            FUN_005F9070();
        if (AlphaImageFile[0])
        {
            // STRING: GAMEMD 0x81834C
            _makepath(path, 0, 0, AlphaImageFile, ".SHP");
            AlphaImage = MixFileClass_Retrieve(path, false);
        }
        return true;
    }
    return false;
}
