// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x672280 / 0x672360 /
//   0x6723D0 (Ghidra disasm). Names cross-checked against YRpp RulesClass.h
//   (consult-only, no LICENSE); each address/convention reconfirmed below.
//
// Translation unit: the three RulesClass *Types INI list-parsers.
//
// Shape (identical across all three, confirmed from the disasm):
//   int n = pINI->GetKeyCount(SectionName);
//   for (i = 0; i < n; ++i)
//       if (pINI->ReadString(SectionName, pINI->GetKeyName(SectionName, i),
//                            "", buffer, 0x20) != 0)
//           <Type>_FindOrAllocate(buffer);
//   return n > 0;
//
// The nested ReadString(..., GetKeyName(...), "", buf, 0x20) call is what
// reproduces retail's shared/overlapping argument pushes: cl pushes ReadString's
// trailing args (0x20, buffer, ""), then evaluates GetKeyName (push index, push
// section, call), then pushes its result + the section, then calls ReadString
// — both callees being __thiscall (callee-clean) keeps the lower pushes alive
// exactly as the disassembly shows.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x672280  RulesClass::Read_InfantryTypes  (__thiscall)
//   FUNCTION: GAMEMD 0x672360  RulesClass::Read_VehicleTypes   (__thiscall)
//   FUNCTION: GAMEMD 0x6723D0  RulesClass::Read_AircraftTypes  (__thiscall)
//   GLOBAL:   GAMEMD 0x7F0CA8  char* InfantryTypesSection  (-> "InfantryTypes")
//   GLOBAL:   GAMEMD 0x7F0CB0  char* VehicleTypesSection   (-> "VehicleTypes")
//   GLOBAL:   GAMEMD 0x7F0CB4  char* AircraftTypesSection  (-> "AircraftTypes")

#include "rules_class_readtypes_methods.h"

// Section-name globals. Each holds a `char*` (the .data slot at the address
// dereferenced by `mov eax,[0x7F0Cxx]`); relocation-normalised by the differ.
extern char* InfantryTypesSection;  // GAMEMD 0x7F0CA8
extern char* VehicleTypesSection;   // GAMEMD 0x7F0CB0
extern char* AircraftTypesSection;  // GAMEMD 0x7F0CB4

// FUNCTION: GAMEMD 0x672280  RulesClass::Read_InfantryTypes  (__thiscall)
bool RulesClass::Read_InfantryTypes(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(InfantryTypesSection);
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->ReadString(InfantryTypesSection,
                             pINI->GetKeyName(InfantryTypesSection, i),
                             "", buffer, 0x20) != 0)
        {
            InfantryType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x672360  RulesClass::Read_VehicleTypes  (__thiscall)
bool RulesClass::Read_VehicleTypes(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(VehicleTypesSection);
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->ReadString(VehicleTypesSection,
                             pINI->GetKeyName(VehicleTypesSection, i),
                             "", buffer, 0x20) != 0)
        {
            UnitType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}

// FUNCTION: GAMEMD 0x6723D0  RulesClass::Read_AircraftTypes  (__thiscall)
bool RulesClass::Read_AircraftTypes(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount(AircraftTypesSection);
    char buffer[0x20];
    for (int i = 0; i < count; ++i)
    {
        if (pINI->ReadString(AircraftTypesSection,
                             pINI->GetKeyName(AircraftTypesSection, i),
                             "", buffer, 0x20) != 0)
        {
            AircraftType_FindOrAllocate(buffer);
        }
    }
    return count > 0;
}
