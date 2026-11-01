// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6743D0.

#include "rules_class_jumpjet_methods.h"

// FUNCTION: GAMEMD 0x6743D0
//
// Read the [JumpjetControls] section: turn rate, speed, climb, cruise
// height, acceleration, wobbles per second and wobble deviation, each
// defaulting to its current value. The section probe is CCINIClass::Exists
// expanded in call-site flag form (see the banked rule).
bool Rules_006743D0::Read_JumpjetControls(CCINI_006743D0* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(JumpjetSection_006743D0) != 0;
    } else {
        ok = pINI->GetEntry(JumpjetSection_006743D0, key) != 0;
    }

    if (ok) {
        JumpjetTurnRate = pINI->ReadInteger(JumpjetSection_006743D0, "TurnRate", JumpjetTurnRate);
        JumpjetSpeed = pINI->ReadInteger(JumpjetSection_006743D0, "Speed", JumpjetSpeed);
        JumpjetClimb = pINI->ReadDouble(JumpjetSection_006743D0, "Climb", JumpjetClimb);
        JumpjetCruiseHeight = pINI->ReadInteger(JumpjetSection_006743D0, "CruiseHeight", JumpjetCruiseHeight);
        JumpjetAcceleration = pINI->ReadDouble(JumpjetSection_006743D0, "Acceleration", JumpjetAcceleration);
        JumpjetWobblesPerSecond = pINI->ReadDouble(JumpjetSection_006743D0, "WobblesPerSecond", JumpjetWobblesPerSecond);
        JumpjetWobbleDeviation = pINI->ReadInteger(JumpjetSection_006743D0, "WobbleDeviation", JumpjetWobbleDeviation);
        return true;
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x839D58
extern const char STR_00839D58[] = "JumpjetControls";
// GLOBAL: GAMEMD 0x839D58
extern const char STR_00839D58[];
// END defined globals
