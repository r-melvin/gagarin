// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6728B0 / 0x672920 /
//   0x672A00 / 0x672A70.
//
// Shape (identical across all four, confirmed from the disasm):
//   int n = pINI->GetKeyCount(Section);
//   for (i = 0; i < n; ++i)
//       if (pINI->FUN_00528A10(Section, pINI->GetKeyName(Section, i),
//                            "", buffer, 0x20) != 0)
//           <Type>_FindOrAllocate(buffer);
//   return n > 0;
//
// The nested ReadString(..., GetKeyName(...), "", buf, 0x20) call is what
// reproduces retail's overlapping argument pushes: cl pushes ReadString's
// trailing args, evaluates GetKeyName, then pushes its result and the section.
// Both callees are __thiscall (callee-clean), which keeps the lower pushes
// alive exactly as the disassembly shows. The trailing `XOR EAX,EAX` /
// `SETG AL` split across the register pops is cl's own scheduling of
// `return count > 0;`.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6722F0  RulesClass::Read_Countries        (__thiscall)
//   FUNCTION: GAMEMD 0x672660  RulesClass::Read_BuildingTypes    (__thiscall)
//   FUNCTION: GAMEMD 0x6728B0  RulesClass::Read_Animations       (__thiscall)
//   FUNCTION: GAMEMD 0x672920  RulesClass::Read_VoxelAnims       (__thiscall)
//   FUNCTION: GAMEMD 0x672A00  RulesClass::Read_Particles        (__thiscall)
//   FUNCTION: GAMEMD 0x672A70  RulesClass::Read_ParticleSystems  (__thiscall)
//   GLOBAL:   GAMEMD 0x7F0CAC  char* CountriesSection     (-> "Countries")
//   GLOBAL:   GAMEMD 0x7F0CC0  char* BuildingTypesSection (-> "BuildingTypes")
//   STRING:   GAMEMD 0x83D0DC  "Animations"
//   STRING:   GAMEMD 0x83D0E8  "VoxelAnims"
//   STRING:   GAMEMD 0x83D0F4  "Particles"
//   STRING:   GAMEMD 0x83D100  "ParticleSystems"
//   STRING:   GAMEMD 0x889F64  ""   (shared default)

#include "rules_class_readtypes_more_methods.h"
#include "type_find_or_allocate_family_methods.h"
#include "_layout/vector_class.h"

#include "vector_class_dynamic_copy.h"
#include "rules_class_ini_support.h"
#include "_layout/side_class.h"
#include "_layout/house_type_class.h"
#include "building_class_garrison_owner_methods.h"

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// GLOBAL: GAMEMD 0x8B4120 -- the side registry.
extern DynamicVectorClass<SideClass*> DAT_008B4120;
// GLOBAL: GAMEMD 0xA83C98 -- the house type registry.
extern DynamicVectorClass<HouseTypeClass*> DAT_00A83C98;

// Dispatch-only view of a team type's primary vtable: LoadFromINI is slot 25 (offset 0x64).
struct ILoad_00672740 {
    virtual void _s00(); virtual void _s01(); virtual void _s02(); virtual void _s03();
    virtual void _s04(); virtual void _s05(); virtual void _s06(); virtual void _s07();
    virtual void _s08(); virtual void _s09(); virtual void _s10(); virtual void _s11();
    virtual void _s12(); virtual void _s13(); virtual void _s14(); virtual void _s15();
    virtual void _s16(); virtual void _s17(); virtual void _s18(); virtual void _s19();
    virtual void _s20(); virtual void _s21(); virtual void _s22(); virtual void _s23();
    virtual void _s24();
    virtual void LoadFromINI(CCINIClass* ini);
};

// FUNCTION: GAMEMD 0x6722F0  RulesClass::Read_Countries  (__thiscall)
bool RulesClass::Read_Countries(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(CountriesSection);
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10(CountriesSection, pINI->GetKeyName(CountriesSection, i),
                             "", buffer, 0x20) != 0)
        {
            HouseType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// Position of a side in the side registry, or -1.
static inline int IndexOfSide(SideClass* side)
{
    for (int k = 0; k < DAT_008B4120.Count; ++k)
    {
        if (DAT_008B4120.Items[k] == side)
        {
            return k;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x672440
// Read the [Sides] section: each key names a side (created when new) and lists the house types
// that belong to it; every listed house type records the side's index.
bool RulesClass::FUN_00672440(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(SidesSection);
    FUN_004068E0("Processing sides.\n");
    for (int i = 0; i < count; ++i)
    {
        const char* name = pINI->GetKeyName(SidesSection, i);
        int index = FindSideIndex_00458200(name);
        SideClass* side;
        if (index == -1)
        {
            side = new SideClass(name);
        }
        else
        {
            side = DAT_008B4120.Items[index];
        }
        FUN_004068E0("Side %d: %s \n", i, side->ID.Data);
        side->unknown_98 = pINI->ReadIntegerList(SidesSection, name, side->unknown_98);
        for (int j = 0; j < side->unknown_98.Count; ++j)
        {
            int houseType = side->unknown_98.Items[j];
            DAT_00A83C98.Items[houseType]->SideIndex = IndexOfSide(side);
            FUN_004068E0("  %s\n", DAT_00A83C98.Items[houseType]->ID.Data);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x6725F0  RulesClass::Read_SuperWeaponTypes  (__thiscall)
bool RulesClass::Read_SuperWeaponTypes(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(SuperWeaponTypesSection);
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10(SuperWeaponTypesSection, pINI->GetKeyName(SuperWeaponTypesSection, i),
                             "", buffer, 0x20) != 0)
        {
            SuperWeaponType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x672660  RulesClass::Read_BuildingTypes  (__thiscall)
bool RulesClass::Read_BuildingTypes(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(BuildingTypesSection);
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10(BuildingTypesSection, pINI->GetKeyName(BuildingTypesSection, i),
                             "", buffer, 0x20) != 0)
        {
            BuildingType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x6726D0  RulesClass::Read_TerrainTypes  (__thiscall)
bool RulesClass::Read_TerrainTypes(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(TerrainTypesSection);
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10(TerrainTypesSection, pINI->GetKeyName(TerrainTypesSection, i),
                             "", buffer, 0x20) != 0)
        {
            TerrainType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x6727D0  RulesClass::Read_SmudgeTypes  (__thiscall)
bool RulesClass::Read_SmudgeTypes(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(SmudgeTypesSection);
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10(SmudgeTypesSection, pINI->GetKeyName(SmudgeTypesSection, i),
                             "", buffer, 0x20) != 0)
        {
            SmudgeType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x672840  RulesClass::Read_OverlayTypes  (__thiscall)
bool RulesClass::Read_OverlayTypes(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(OverlayTypesSection);
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10(OverlayTypesSection, pINI->GetKeyName(OverlayTypesSection, i),
                             "", buffer, 0x20) != 0)
        {
            OverlayType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x6728B0  RulesClass::Read_Animations  (__thiscall)
bool RulesClass::Read_Animations(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount("Animations");
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10("Animations", pINI->GetKeyName("Animations", i),
                             "", buffer, 0x20) != 0)
        {
            AnimType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x672920  RulesClass::Read_VoxelAnims  (__thiscall)
bool RulesClass::Read_VoxelAnims(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount("VoxelAnims");
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10("VoxelAnims", pINI->GetKeyName("VoxelAnims", i),
                             "", buffer, 0x20) != 0)
        {
            VoxelAnimType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x672990  RulesClass::Read_Warheads  (__thiscall)
bool RulesClass::Read_Warheads(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount("Warheads");
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10("Warheads", pINI->GetKeyName("Warheads", i),
                             "", buffer, 0x20) != 0)
        {
            WarheadType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x672A00  RulesClass::Read_Particles  (__thiscall)
bool RulesClass::Read_Particles(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount("Particles");
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10("Particles", pINI->GetKeyName("Particles", i),
                             "", buffer, 0x20) != 0)
        {
            ParticleType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x672A70  RulesClass::Read_ParticleSystems  (__thiscall)
bool RulesClass::Read_ParticleSystems(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount("ParticleSystems");
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->FUN_00528A10("ParticleSystems", pINI->GetKeyName("ParticleSystems", i),
                             "", buffer, 0x20) != 0)
        {
            ParticleSystemType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x672740  RulesClass::Read_Teams  (__thiscall)
// For every key of the section, finds (or creates) the named team type and has it load itself.
bool RulesClass::Read_Teams(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(TeamsSection);
    char buffer[0x80];
    for (int i = 0; i < count; ++i)
    {
        const char* key = pINI->GetKeyName(TeamsSection, i);
        TypeClass_006F1920* item = pINI->FUN_00528A10(TeamsSection, key, "", buffer, 0x80) != 0
            ? TypeClass_006F1920::FindOrAllocate(buffer) : 0;
        ((ILoad_00672740*)item)->LoadFromINI(pINI);
    }
    return count > 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x839DA8
extern const char STR_00839DA8[] = "OverlayTypes";
// GLOBAL: GAMEMD 0x839DB8
extern const char STR_00839DB8[] = "SmudgeTypes";
// GLOBAL: GAMEMD 0x839DC4
extern const char STR_00839DC4[] = "Teams";
// GLOBAL: GAMEMD 0x839DCC
extern const char STR_00839DCC[] = "TerrainTypes";
// GLOBAL: GAMEMD 0x839DDC
extern const char STR_00839DDC[] = "BuildingTypes";
// GLOBAL: GAMEMD 0x839DEC
extern const char STR_00839DEC[] = "SuperWeaponTypes";
// GLOBAL: GAMEMD 0x839E28
extern const char STR_00839E28[] = "Countries";
// GLOBAL: GAMEMD 0x839DA8
extern const char STR_00839DA8[];
// GLOBAL: GAMEMD 0x839DB8
extern const char STR_00839DB8[];
// GLOBAL: GAMEMD 0x839DC4
extern const char STR_00839DC4[];
// GLOBAL: GAMEMD 0x839DCC
extern const char STR_00839DCC[];
// GLOBAL: GAMEMD 0x839DDC
extern const char STR_00839DDC[];
// GLOBAL: GAMEMD 0x839DEC
extern const char STR_00839DEC[];
// GLOBAL: GAMEMD 0x839E28
extern const char STR_00839E28[];
// END defined globals
