// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x66B900.

#include "rules_class_ini_support.h"

// FUNCTION: GAMEMD 0x66B900
//
// Read the [CrateRules] section: the free-MCV flag, the three crate overlay
// types, the heal-crate sound, the crate count limits, radius and regen rate,
// the solo-crate unit and money, and the three crate weights. Reports whether
// the section exists.
bool RulesClass::Read_CrateRules(CCINIClass* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(CrateRulesSection) != 0;
    } else {
        ok = pINI->GetEntry(CrateRulesSection, key) != 0;
    }
    if (ok) {
        char buffer[0x80];

        FreeMCV = pINI->ReadBool(CrateRulesSection, "FreeMCV", FreeMCV);

        OverlayTypeClass* wood = WoodCrateImg;
        WoodCrateImg = pINI->ReadString(CrateRulesSection, "WoodCrateImg", STR_00889F64, buffer, 0x80) ? OverlayType_FindPtr(buffer) : wood;

        OverlayTypeClass* crate = CrateImg;
        CrateImg = pINI->ReadString(CrateRulesSection, "CrateImg", STR_00889F64, buffer, 0x80) ? OverlayType_FindPtr(buffer) : crate;

        OverlayTypeClass* water = WaterCrateImg;
        WaterCrateImg = pINI->ReadString(CrateRulesSection, "WaterCrateImg", STR_00889F64, buffer, 0x80) ? OverlayType_FindPtr(buffer) : water;

        int sound = HealCrateSound;
        int index;
        HealCrateSound = pINI->ReadString(CrateRulesSection, "HealCrateSound", STR_00889F64, buffer, 0x80)
                         && (index = VocClass::FindIndex(buffer)) != -1 ? index : sound;

        CrateMinimum = pINI->ReadInteger(CrateRulesSection, "CrateMinimum", CrateMinimum);
        CrateMaximum = pINI->ReadInteger(CrateRulesSection, "CrateMaximum", CrateMaximum);
        CrateRadius = pINI->ReadFraction(CrateRulesSection, "CrateRadius", CrateRadius);
        CrateRegen = pINI->ReadDouble(CrateRulesSection, "CrateRegen", CrateRegen);

        UnitTypeClass* unit = UnitCrateType;
        UnitCrateType = pINI->ReadString(CrateRulesSection, "UnitCrateType", STR_00889F64, buffer, 0x80) ? UnitType_FindPtr(buffer) : unit;

        SoloCrateMoney = pINI->ReadInteger(CrateRulesSection, "SoloCrateMoney", SoloCrateMoney);
        SilverCrate = pINI->FUN_004759F0(CrateRulesSection, "SilverCrate", SilverCrate);
        WoodCrate = pINI->FUN_004759F0(CrateRulesSection, "WoodCrate", WoodCrate);
        WaterCrate = pINI->FUN_004759F0(CrateRulesSection, "WaterCrate", WaterCrate);
        return true;
    }
    return false;
}
