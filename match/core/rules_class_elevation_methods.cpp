// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x66D150.

#include "rules_class_elevation_methods.h"

// FUNCTION: GAMEMD 0x66D150  RulesClass::Read_ElevationModel (__thiscall, ret 0x4)
//
// Three scalars out of [ElevationModel], each defaulting to its current value.
// An absent section reads nothing and reports false.
//
// The section test is CCINIClass::Exists (0x679F40) with its key defaulted to
// null, expanded at the call site in flag form: a caller-scope `bool ok =
// false`, assigned in both arms of the constant-folded `key == 0` chain and
// tested after it closes. That keeps EAX occupied across the first argument
// group so the defaults land in ECX/EDX and the later groups in ECX/EAX/EDX
// as retail has them (the header inline form scored 66.7% with an identical
// multiset; see Read_WallModel 0x66D1F0 for the same lift).
bool RulesClass::Read_ElevationModel(CCINIClass* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(ElevationModelSection) != 0;
    } else {
        ok = pINI->GetEntry(ElevationModelSection, key) != 0;
    }

    if (ok) {
        ElevationIncrement      = pINI->ReadInteger(ElevationModelSection,
                                                    "ElevationIncrement",
                                                    ElevationIncrement);
        ElevationIncrementBonus = pINI->ReadDouble(ElevationModelSection,
                                                   "ElevationIncrementBonus",
                                                   ElevationIncrementBonus);
        ElevationBonusCap       = pINI->ReadDouble(ElevationModelSection,
                                                   "ElevationBonusCap",
                                                   ElevationBonusCap);
        return true;
    }

    return false;
}
