// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Compared against retail gamemd.exe v1.001 at 0x674000.

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "rules_class_ini_support.h"
#include "scenario_class_lighting_methods.h"

// One entry of the twelve-entry ground type table at 0x89EA40: a movement cost per speed class
// (the winged slot is a constant 1.0 that this reader stores) and the buildable flag.
struct GroundTypeEntry_00674000
{
    float Cost[8];     // +0x00 Foot, Track, Wheel, Hover, (winged), Float, Amphibious, FloatBeach
    bool  Buildable;   // +0x20
    char  unknown_21[3];
};
GG_STATIC_ASSERT(offsetof(GroundTypeEntry_00674000, Buildable) == 0x20);
GG_STATIC_ASSERT(sizeof(GroundTypeEntry_00674000) == 0x24);

// GLOBAL: GAMEMD 0x89EA40
extern GroundTypeEntry_00674000 DAT_0089EA40[12];
// GLOBAL: GAMEMD 0x839D68 -- the section name of each ground type.
extern char* DAT_00839D68[12];

// FUNCTION: GAMEMD 0x674000
//
// Read the per-ground-type movement costs. Each cost is capped at 1.0.
bool RulesClass::Read_GroundTypes(CCINIClass* pINI)
{
    for (int i = 0; i < 12; i++) {
        bool        ok  = false;
        const char* key = 0;

        if (key == 0) {
            ok = pINI->GetSection(DAT_00839D68[i]) != 0;
        } else {
            ok = pINI->GetEntry(DAT_00839D68[i], key) != 0;
        }
        if (ok) {
            GroundTypeEntry_00674000* e = &DAT_0089EA40[i];
            e->Cost[3] = (float)GG_MIN(pINI->ReadDouble(DAT_00839D68[i], "Hover", 1.0), 1.0);
            e->Cost[0] = (float)GG_MIN(pINI->ReadDouble(DAT_00839D68[i], "Foot", 1.0), 1.0);
            e->Cost[1] = (float)GG_MIN(pINI->ReadDouble(DAT_00839D68[i], "Track", 1.0), 1.0);
            e->Cost[2] = (float)GG_MIN(pINI->ReadDouble(DAT_00839D68[i], "Wheel", 1.0), 1.0);
            e->Cost[4] = 1.0f;
            e->Cost[5] = (float)GG_MIN(pINI->ReadDouble(DAT_00839D68[i], "Float", 1.0), 1.0);
            e->Cost[6] = (float)GG_MIN(pINI->ReadDouble(DAT_00839D68[i], "Amphibious", 1.0), 1.0);
            e->Cost[7] = (float)GG_MIN(pINI->ReadDouble(DAT_00839D68[i], "FloatBeach", 1.0), 1.0);
            e->Buildable = pINI->ReadBool(DAT_00839D68[i], "Buildable", false);
        }
    }
    return true;
}
