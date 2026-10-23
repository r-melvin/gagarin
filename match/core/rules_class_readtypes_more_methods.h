// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x6728B0 / 0x672920 /
//   0x672A00 / 0x672A70 (Ghidra disasm). Names cross-checked against YRpp
//  ; every address reconfirmed here.
//
// Four more RulesClass INI list-parsers, the effect-type half of the family
// whose *Types half lives in rules_class_readtypes_methods.cpp.
//
// The family splits on how the section name is supplied, and the bytes show it
// directly. Read_Animations and its three neighbours push the name as an
// *immediate* string address (`PUSH 0x83D0DC`), so those sections are string
// literals in the source. Read_Countries and Read_BuildingTypes instead load a
// `char*` global (`MOV EAX,[0x7F0CAC]`), like the trio in the sibling TU. The
// default value is the shared empty-string literal at 0x00889F64 throughout.
#ifndef GG_MATCH_CORE_RULES_CLASS_READTYPES_MORE_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_READTYPES_MORE_METHODS_H

// INI reader helpers (declared only; relocation-normalised against retail).
//   GetKeyCount @0x526960  __thiscall(const char* section)               -> int
//   GetKeyName  @0x526CC0  __thiscall(const char* section, int index)    -> char*
//   ReadString  @0x528A10  __thiscall(sec, key, def, char* buf, int len) -> int
class CCINIClass
{
public:
    int         GetKeyCount(const char* pSection);
    const char* GetKeyName(const char* pSection, int index);
    int         ReadString(const char* pSection, const char* pKey,
                           const char* pDefault, char* pBuffer, int size);
};

// Per-type allocator callees (declared only). Each takes the freshly-read key
// in ECX — retail compiles them as single-pointer __fastcall
// (`LEA ECX,[buffer]; CALL rel32`).
//   AnimTypeClass::FindOrAllocate           @0x428B80
//   VoxelAnimTypeClass::FindOrAllocate      @0x74B960
//   ParticleTypeClass::FindOrAllocate       @0x645820
//   ParticleSystemTypeClass::FindOrAllocate @0x644890
//   HouseTypeClass::FindOrAllocate          @0x512680
//   BuildingTypeClass::FindOrAllocate       @0x4653C0
int HouseType_FindOrAllocate(const char* pID);
int WarheadType_FindOrAllocate(const char* pID);       // GAMEMD 0x75E3B0
int SuperWeaponType_FindOrAllocate(const char* pID);   // GAMEMD 0x6CEEF0
int TerrainType_FindOrAllocate(const char* pID);       // GAMEMD 0x71E2A0
int SmudgeType_FindOrAllocate(const char* pID);        // GAMEMD 0x6B5910
int OverlayType_FindOrAllocate(const char* pID);       // GAMEMD 0x5FEC70
int BuildingType_FindOrAllocate(const char* pID);
int AnimType_FindOrAllocate(const char* pID);
int VoxelAnimType_FindOrAllocate(const char* pID);
int ParticleType_FindOrAllocate(const char* pID);
int ParticleSystemType_FindOrAllocate(const char* pID);

// RulesClass: `this` is only forwarded, so no members or base are needed.
// Section-name globals for the two parsers that load a `char*` rather than
// pushing a literal. Each holds the pointer the retail code dereferences with
// `MOV EAX,[0x7F0Cxx]`; the strings behind them are "Countries" (0x839E28) and
// "BuildingTypes" (0x839DDC).
extern char* CountriesSection;      // GLOBAL: GAMEMD 0x7F0CAC
extern char* SuperWeaponTypesSection;  // GLOBAL: GAMEMD 0x7F0CBC
extern char* BuildingTypesSection;  // GLOBAL: GAMEMD 0x7F0CC0
extern char* TerrainTypesSection;   // GLOBAL: GAMEMD 0x7F0CC4
extern char* SmudgeTypesSection;    // GLOBAL: GAMEMD 0x7F0CCC
extern char* OverlayTypesSection;   // GLOBAL: GAMEMD 0x7F0CD0

struct RulesClass
{
    // Declared ascending by retail address.
    bool Read_Countries(CCINIClass* pINI);        // GAMEMD 0x6722F0 __thiscall
    bool Read_SuperWeaponTypes(CCINIClass* pINI); // GAMEMD 0x6725F0 __thiscall
    bool Read_BuildingTypes(CCINIClass* pINI);    // GAMEMD 0x672660 __thiscall
    bool Read_TerrainTypes(CCINIClass* pINI);     // GAMEMD 0x6726D0 __thiscall
    bool Read_SmudgeTypes(CCINIClass* pINI);      // GAMEMD 0x6727D0 __thiscall
    bool Read_OverlayTypes(CCINIClass* pINI);     // GAMEMD 0x672840 __thiscall
    bool Read_Animations(CCINIClass* pINI);       // GAMEMD 0x6728B0 __thiscall
    bool Read_VoxelAnims(CCINIClass* pINI);       // GAMEMD 0x672920 __thiscall
    bool Read_Warheads(CCINIClass* pINI);         // GAMEMD 0x672990 __thiscall
    bool Read_Particles(CCINIClass* pINI);        // GAMEMD 0x672A00 __thiscall
    bool Read_ParticleSystems(CCINIClass* pINI);  // GAMEMD 0x672A70 __thiscall
};

#endif  // GG_MATCH_CORE_RULES_CLASS_READTYPES_MORE_METHODS_H
