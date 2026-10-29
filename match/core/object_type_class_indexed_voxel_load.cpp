// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// /Ob0 gives 11.2% / 5.5%; /Ob1 and /Ob2 reproduce both native bodies.
// Indexed resource loaders, validated from 0x5F7A90 and 0x5F7DB0 entries.
// Each function retains its own native replacement/failure semantics.
#include "../_layout/object_type_class.h"
#include "../platform/ccfile_class.h"
#include <stdio.h>
#include <stdlib.h>

// FUNCTION: GAMEMD 0x5F7A90
bool ObjectTypeClass::FUN_005F7A90(const char* image, int index)
{
    char name[256];
    char path[260];
    // STRING: GAMEMD 0x832ABC
    // STRING: GAMEMD 0x832AB4
    if (index == 0) sprintf(name, "%sTUR", image);
    else sprintf(name, "%sTUR%d", image, index);
    // STRING: GAMEMD 0x8194AC
    _makepath(path, 0, 0, name, ".VXL");
    CCFileClass modelFile(path);
    if (!modelFile.Exists(0)) return false;
    if (ChargerTurrets[index].unknown_00) {
        delete ChargerTurrets[index].unknown_00;
        ChargerTurrets[index].unknown_00 = 0;
    }
    bool modelLoaded = false;
    ChargerTurrets[index].unknown_00 = new Obj_00755D10(&modelFile, 0);
    if (ChargerTurrets[index].unknown_00 && !ChargerTurrets[index].unknown_00->unknown_00)
        modelLoaded = true;
    if (index == 0) sprintf(name, "%sTUR", image);
    else sprintf(name, "%sTUR%d", image, index);
    // STRING: GAMEMD 0x8194A0
    _makepath(path, 0, 0, name, ".HVA");
    CCFileClass animationFile(path);
    if (ChargerTurrets[index].HVAData) {
        delete ChargerTurrets[index].HVAData;
        ChargerTurrets[index].HVAData = 0;
    }
    bool animationLoaded = false;
    ChargerTurrets[index].HVAData = new Obj_005BD5A0(&animationFile);
    if (ChargerTurrets[index].HVAData && !ChargerTurrets[index].HVAData->unknown_00)
        animationLoaded = true;
    if (modelLoaded && animationLoaded) {
        ChargerTurrets[index].HVAData->FUN_005BD730(
            ChargerTurrets[index].unknown_00->FUN_007564b0(0, 0)->unknown_0C);
        return true;
    }
    if (ChargerTurrets[index].unknown_00) {
        delete ChargerTurrets[index].unknown_00;
        ChargerTurrets[index].unknown_00 = 0;
    }
    if (ChargerTurrets[index].HVAData) {
        delete ChargerTurrets[index].HVAData;
        ChargerTurrets[index].HVAData = 0;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5F7DB0
bool ObjectTypeClass::FUN_005F7DB0(const char* image, int index)
{
    char name[256];
    char path[260];
    // STRING: GAMEMD 0x832AD0
    // STRING: GAMEMD 0x832AC4
    if (index == 0) sprintf(name, "%sBARL", image);
    else sprintf(name, "%sBARL%d", image, index);
    _makepath(path, 0, 0, name, ".VXL");
    CCFileClass modelFile(path);
    if (!modelFile.Exists(0)) return true;
    bool modelLoaded = false;
    ChargerBarrels[index].unknown_00 = new Obj_00755D10(&modelFile, 0);
    if (ChargerBarrels[index].unknown_00 && !ChargerBarrels[index].unknown_00->unknown_00)
        modelLoaded = true;
    if (index == 0) sprintf(name, "%sBARL", image);
    else sprintf(name, "%sBARL%d", image, index);
    _makepath(path, 0, 0, name, ".HVA");
    CCFileClass animationFile(path);
    bool animationLoaded = false;
    ChargerBarrels[index].HVAData = new Obj_005BD5A0(&animationFile);
    if (ChargerBarrels[index].HVAData && !ChargerBarrels[index].HVAData->unknown_00)
        animationLoaded = true;
    if (modelLoaded && animationLoaded) {
        ChargerBarrels[index].HVAData->FUN_005BD730(
            ChargerBarrels[index].unknown_00->FUN_007564b0(0, 0)->unknown_0C);
        return true;
    }
    // Native 0x5F7FD0 onward releases failed resources without clearing slots.
    if (ChargerBarrels[index].unknown_00) delete ChargerBarrels[index].unknown_00;
    if (ChargerBarrels[index].HVAData) delete ChargerBarrels[index].HVAData;
    return false;
}
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerTurrets) == 0xC8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerBarrels) == 0x158);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ChargerTurrets) == 0x90);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ChargerBarrels) == 0x90);
