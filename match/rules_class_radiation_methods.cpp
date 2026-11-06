// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Compared against retail gamemd.exe v1.001 at 0x66CF70.

#include "rules_class_ini_support.h"

// FUNCTION: GAMEMD 0x66CF70
//
// Read the [Radiation] section into the rules object. Reports whether the section exists.
bool RulesClass::Read_Radiation(CCINIClass* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(RadiationSection) != 0;
    } else {
        ok = pINI->GetEntry(RadiationSection, key) != 0;
    }
    if (ok) {
        char buffer[0x80];

        RadDurationMultiple = pINI->ReadInteger(RadiationSection, "RadDurationMultiple", RadDurationMultiple);
        RadApplicationDelay = pINI->ReadInteger(RadiationSection, "RadApplicationDelay", RadApplicationDelay);
        RadLevelMax = pINI->ReadInteger(RadiationSection, "RadLevelMax", RadLevelMax);
        RadLevelDelay = pINI->ReadInteger(RadiationSection, "RadLevelDelay", RadLevelDelay);
        RadLightDelay = pINI->ReadInteger(RadiationSection, "RadLightDelay", RadLightDelay);
        RadLevelFactor = pINI->ReadDouble(RadiationSection, "RadLevelFactor", RadLevelFactor);
        RadLightFactor = pINI->ReadDouble(RadiationSection, "RadLightFactor", RadLightFactor);
        RadTintFactor = pINI->ReadDouble(RadiationSection, "RadTintFactor", RadTintFactor);
        // RadColorR/G/B are the three bytes of one colour: retail passes their address as the default
        // and copies the 3-byte result back over them (word + byte at 0x66D0CF..0x66D0E1).
        // Layout cast: a real ColorStruct member at +0x1830 moves the TypeList<int> inline sites of the constructor
        // 0x665650 (retail stores the three bytes one by one at 0x6677EF, as for any ColorStruct): 99.8% falls to
        // 79.0%, and to 99.3% at best with the ColorAdd reset built through RulesColor_004B9BD0.
        *(ColorStruct*)&RadColorR = pINI->Read3Bytes(RadiationSection, "RadColor", *(ColorStruct*)&RadColorR);
        { WarheadTypeClass* t0 = RadSiteWarhead; RadSiteWarhead = pINI->ReadString(RadiationSection, "RadSiteWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t0; }
        return true;
    }
    return false;
}
