// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x555AC0 (name from
//   the YRpp method map).

#include "scenario_class_lighting_methods.h"

// FUNCTION: GAMEMD 0x555AC0  ScenarioClass::ScenarioLighting (__fastcall, ret 0x4)
//
// Normalise a lighting triple in place: each channel is clamped to 1000 and
// floored at zero, then rounded down to the channel granularity the current
// colour depth can show (steps of 128, 64 or 32 for selector 0, 1, 2; other
// selectors leave the values as they are).
void __fastcall ScenarioClass::ScenarioLighting(int* red, int* green, int* blue)
{
    *red = GG_MIN(*red, 1000);
    *green = GG_MIN(*green, 1000);
    *blue = GG_MIN(*blue, 1000);

    *red = GG_MAX(*red, 0);
    *green = GG_MAX(*green, 0);
    *blue = GG_MAX(*blue, 0);

    switch (DAT_00A8EB78) {
    case 0:
        *red &= ~0x7F;
        *green &= ~0x7F;
        *blue &= ~0x7F;
        break;
    case 1:
        *red &= ~0x3F;
        *green &= ~0x3F;
        *blue &= ~0x3F;
        break;
    case 2:
        *red &= ~0x1F;
        *green &= ~0x1F;
        *blue &= ~0x1F;
        break;
    }
}
