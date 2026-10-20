// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x66D270.

#include "rules_class_read_difficulty_methods.h"

// FUNCTION: GAMEMD 0x66D270
//
// Fill one difficulty block ([Easy], [Normal] or [Difficult]) from the given
// section: nine double multipliers defaulting to 1.0 (RepairDelay 0.02,
// BuildDelay 0.03) and three flags. Retail reads BuildSlowdown before
// BuildTime, so the +0x48 byte lands before the +0x30 double. The section
// probe is CCINIClass::Exists expanded in call-site flag form (banked rule).
// No value is reported; an absent section leaves the block untouched.
void __fastcall Read_Difficulty_0066D270(CCINI_0066D270* pINI,
                                         Difficulty_0066D270* pOut,
                                         const char* pSection)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(pSection) != 0;
    } else {
        ok = pINI->GetEntry(pSection, key) != 0;
    }

    if (ok) {
        pOut->FirePower     = pINI->ReadDouble(pSection, "FirePower", 1.0);
        pOut->Groundspeed   = pINI->ReadDouble(pSection, "Groundspeed", 1.0);
        pOut->Airspeed      = pINI->ReadDouble(pSection, "Airspeed", 1.0);
        pOut->Armor         = pINI->ReadDouble(pSection, "Armor", 1.0);
        pOut->ROF           = pINI->ReadDouble(pSection, "ROF", 1.0);
        pOut->Cost          = pINI->ReadDouble(pSection, "Cost", 1.0);
        pOut->RepairDelay   = pINI->ReadDouble(pSection, "RepairDelay", 0.02);
        pOut->BuildDelay    = pINI->ReadDouble(pSection, "BuildDelay", 0.03);
        pOut->BuildSlowdown = pINI->ReadBool(pSection, "BuildSlowdown", false);
        pOut->BuildTime     = pINI->ReadDouble(pSection, "BuildTime", 1.0);
        pOut->DestroyWalls  = pINI->ReadBool(pSection, "DestroyWalls", true);
        pOut->ContentScan   = pINI->ReadBool(pSection, "ContentScan", false);
    }
}
