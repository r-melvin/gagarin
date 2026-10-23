// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6728B0 / 0x672920 /
//   0x672A00 / 0x672A70.
//
// Shape (identical across all four, confirmed from the disasm):
//   int n = pINI->GetKeyCount(Section);
//   for (i = 0; i < n; ++i)
//       if (pINI->ReadString(Section, pINI->GetKeyName(Section, i),
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

// FUNCTION: GAMEMD 0x6722F0  RulesClass::Read_Countries  (__thiscall)
bool RulesClass::Read_Countries(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(CountriesSection);
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->ReadString(CountriesSection, pINI->GetKeyName(CountriesSection, i),
                             "", buffer, 0x20) != 0)
        {
            HouseType_FindOrAllocate(buffer);
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
        if (pINI->ReadString(SuperWeaponTypesSection, pINI->GetKeyName(SuperWeaponTypesSection, i),
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
        if (pINI->ReadString(BuildingTypesSection, pINI->GetKeyName(BuildingTypesSection, i),
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
        if (pINI->ReadString(TerrainTypesSection, pINI->GetKeyName(TerrainTypesSection, i),
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
        if (pINI->ReadString(SmudgeTypesSection, pINI->GetKeyName(SmudgeTypesSection, i),
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
        if (pINI->ReadString(OverlayTypesSection, pINI->GetKeyName(OverlayTypesSection, i),
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
        if (pINI->ReadString("Animations", pINI->GetKeyName("Animations", i),
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
        if (pINI->ReadString("VoxelAnims", pINI->GetKeyName("VoxelAnims", i),
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
        if (pINI->ReadString("Warheads", pINI->GetKeyName("Warheads", i),
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
        if (pINI->ReadString("Particles", pINI->GetKeyName("Particles", i),
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
        if (pINI->ReadString("ParticleSystems", pINI->GetKeyName("ParticleSystems", i),
                             "", buffer, 0x20) != 0)
        {
            ParticleSystemType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}
