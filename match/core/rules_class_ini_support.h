// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Shared declarations for the RulesClass INI reader functions (0x66B900 onwards): the readers
//   not yet declared on CCINIClass, typed type-lookup callees and the section-name globals.
//   Every callee is read off the user's retail gamemd.exe disassembly; declarations only.
#ifndef GG_MATCH_CORE_RULES_CLASS_INI_SUPPORT_H
#define GG_MATCH_CORE_RULES_CLASS_INI_SUPPORT_H

#include <string.h>
#include "../_layout/rules_class.h"
#include "../platform/ccini_class_methods.h"
#include "../audio/voc_class_methods.h"
#include "../_layout/warhead_type_class.h"

void* MapObjLoadShape(const char* path, bool flag);   // GAMEMD 0x5B40B0

extern const char STR_00889F64[];   // STRING: GAMEMD 0x889F64 ""

// The warhead type array (items pointer and live count).
extern WarheadTypeClass** WarheadTypeItems;   // GLOBAL: GAMEMD 0x8874C4
extern int WarheadTypeCount;                  // GLOBAL: GAMEMD 0x8874D0

// Typed lookup-or-create callees (the int-returning spellings live in type_find_or_allocate_family_methods.h).
class AnimTypeClass;
AnimTypeClass* AnimType_FindPtr(const char* id);   // GAMEMD 0x428B80
class BuildingTypeClass;
BuildingTypeClass* BuildingType_FindPtr(const char* id);   // GAMEMD 0x4653C0
class BulletTypeClass;
BulletTypeClass* BulletType_FindPtr(const char* id);   // GAMEMD 0x46C790
class OverlayTypeClass;
OverlayTypeClass* OverlayType_FindPtr(const char* id);   // GAMEMD 0x5FEC70
class ParticleSystemTypeClass;
ParticleSystemTypeClass* ParticleSystemType_FindPtr(const char* id);   // GAMEMD 0x644890
class SmudgeTypeClass;
SmudgeTypeClass* SmudgeType_FindPtr(const char* id);   // GAMEMD 0x6B5910
class UnitTypeClass;
UnitTypeClass* UnitType_FindPtr(const char* id);   // GAMEMD 0x7480D0
class VoxelAnimTypeClass;
VoxelAnimTypeClass* VoxelAnimType_FindPtr(const char* id);   // GAMEMD 0x74B960
class WarheadTypeClass;
WarheadTypeClass* WarheadType_FindPtr(const char* id);   // GAMEMD 0x75E3B0
class WeaponTypeClass;
WeaponTypeClass* WeaponType_FindPtr(const char* id);   // GAMEMD 0x772FA0

// Section-name globals (each holds a char* the reader dereferences).
extern char* SpecialWeaponsSection;   // GLOBAL: GAMEMD 0x7f0c78
extern char* AudioVisualSection;   // GLOBAL: GAMEMD 0x7f0c7c
extern char* CrateRulesSection;   // GLOBAL: GAMEMD 0x7f0c80
extern char* CombatDamageSection;   // GLOBAL: GAMEMD 0x7f0c84
extern char* RadiationSection;   // GLOBAL: GAMEMD 0x7f0c88
extern char* GeneralSection;   // GLOBAL: GAMEMD 0x7f0c9c
extern char* MultiplayerDialogSettingsSection;   // GLOBAL: GAMEMD 0x7f0ca0
extern char* AISection;   // GLOBAL: GAMEMD 0x7f0cd4

extern const char STR_00817F70[];   // STRING: GAMEMD 0x817F70 ","

// The integer list copy constructor is expanded in the readers: the base copy (0x4779E0) stays a call and the
// list's own vptr store follows it inline (e.g. 0x66C7B7).
template<> inline TypeList<int>::TypeList(const TypeList<int>& other) : DynamicVectorClass<int>(other) {}

// Comma-separated list of animation type names, expanded inline in the INI readers (e.g. 0x721A50):
// the names are looked up in turn (unknown names are skipped) and appended to a fresh list. The reader
// calls this only when the key is present; otherwise it returns the caller's list. The two-function split
// (builder inside the key test) is what reproduces retail's mix of inlined and called list destructors.
static inline TypeList<const AnimTypeClass*> BuildAnimTypeList(char* buffer)
{
    TypeList<const AnimTypeClass*> list(0, 0);
    for (char* token = strtok(buffer, STR_00817F70); token && *token; token = strtok(0, STR_00817F70)) {
        const AnimTypeClass* type = AnimType_FindPtr(token);
        if (type)
            list.AddItem(type);
    }
    return list;
}
static inline TypeList<const AnimTypeClass*> ReadAnimTypeList(CCINIClass* ini, const char* section,
    const char* key, const TypeList<const AnimTypeClass*>& defaultValue, char* buffer)
{
    if (ini->ReadString(section, key, STR_00889F64, buffer, 0x80))
        return BuildAnimTypeList(buffer);
    return defaultValue;
}

// The same read for smudge type lists (the [CombatDamage] Scorches keys).
static inline TypeList<const SmudgeTypeClass*> BuildSmudgeTypeList(char* buffer)
{
    TypeList<const SmudgeTypeClass*> list(0, 0);
    for (char* token = strtok(buffer, STR_00817F70); token && *token; token = strtok(0, STR_00817F70)) {
        const SmudgeTypeClass* type = SmudgeType_FindPtr(token);
        if (type)
            list.AddItem(type);
    }
    return list;
}
static inline TypeList<const SmudgeTypeClass*> ReadSmudgeTypeList(CCINIClass* ini, const char* section,
    const char* key, const TypeList<const SmudgeTypeClass*>& defaultValue, char* buffer)
{
    if (ini->ReadString(section, key, STR_00889F64, buffer, 0x80))
        return BuildSmudgeTypeList(buffer);
    return defaultValue;
}

#endif
