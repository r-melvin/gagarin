// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x674240.

#include "rules_class_iq_methods.h"

// FUNCTION: GAMEMD 0x674240
//
// Read the [IQ] section: eleven integer thresholds, each defaulting to its
// current value. The section probe is CCINIClass::Exists in flag form.
bool Rules_00674240::Read_IQ(CCINI_00674240* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(IQSection_00674240) != 0;
    } else {
        ok = pINI->GetEntry(IQSection_00674240, key) != 0;
    }
    if (ok) {
        MaxIQLevels = pINI->ReadInteger(IQSection_00674240, "MaxIQLevels", MaxIQLevels);
        SuperWeapons = pINI->ReadInteger(IQSection_00674240, "SuperWeapons", SuperWeapons);
        Production = pINI->ReadInteger(IQSection_00674240, "Production", Production);
        GuardArea = pINI->ReadInteger(IQSection_00674240, "GuardArea", GuardArea);
        RepairSell = pINI->ReadInteger(IQSection_00674240, "RepairSell", RepairSell);
        AutoCrush = pINI->ReadInteger(IQSection_00674240, "AutoCrush", AutoCrush);
        Scatter = pINI->ReadInteger(IQSection_00674240, "Scatter", Scatter);
        ContentScan = pINI->ReadInteger(IQSection_00674240, "ContentScan", ContentScan);
        Aircraft = pINI->ReadInteger(IQSection_00674240, "Aircraft", Aircraft);
        Harvester = pINI->ReadInteger(IQSection_00674240, "Harvester", Harvester);
        SellBack = pINI->ReadInteger(IQSection_00674240, "SellBack", SellBack);
        return true;
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x824DD8
extern const char STR_00824DD8[] = "IQ";
// GLOBAL: GAMEMD 0x824DD8
extern const char STR_00824DD8[];
// END defined globals
