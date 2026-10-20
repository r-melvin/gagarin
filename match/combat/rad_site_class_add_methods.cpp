// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp RadSiteClass.h / RulesClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x65B530  RadSiteClass::Add  (__thiscall)

#include "rad_site_class_add_methods.h"

// FUNCTION: GAMEMD 0x65B530  (__thiscall)
// Add this RadLevel to the current radiation. The currently-applied level is
// recomputed in double precision (RadLevel * RadTimeLeft / RadDuration) and
// truncated to int (an __ftol call), then the site is rebuilt at the new level.
void RadSiteClass::Add(int nRadLevel)
{
    double level = RadLevel;
    double timeLeft = RadTimeLeft;
    double duration = RadDuration;
    int current = (int)(level * timeLeft / duration);
    Deactivate();
    RadLevel = current + nRadLevel;
    RadDuration = RulesInstance->RadDurationMultiple * RadLevel;
    RadTimeLeft = RadDuration;
    Activate();
}
