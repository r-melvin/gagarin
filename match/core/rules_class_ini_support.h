// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Shared declarations for the RulesClass INI reader functions (0x66B900 onwards): the readers
//   not yet declared on CCINIClass, typed type-lookup callees and the section-name globals.
//   Every callee is read off the user's retail gamemd.exe disassembly; declarations only.
#ifndef GG_MATCH_CORE_RULES_CLASS_INI_SUPPORT_H
#define GG_MATCH_CORE_RULES_CLASS_INI_SUPPORT_H

#include "../_layout/rules_class.h"
#include "../platform/ccini_class_methods.h"
#include "../audio/voc_class_methods.h"
#include "../_layout/warhead_type_class.h"

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

#endif
