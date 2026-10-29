// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x70E4B0 (name from
//   the YRpp method map).

#include "techno_class_airstrike_tint_methods.h"

// FUNCTION: GAMEMD 0x70E4B0  TechnoView_0070E4B0::GetAirstrikeTintIntensity (__thiscall, ret 0x4)
//
// Scale a tint intensity by the airstrike-target flash. The timer's remaining
// frames drive a per-stage ramp (a 256-based fixed-point factor: fading in,
// holding, fading out for the two shapes), the product is scaled back down
// and capped at 2000. Stages outside 1..9 pass the intensity through.
int TechnoView_0070E4B0::GetAirstrikeTintIntensity(int currentIntensity)
{
    int left = this->AirstrikeTintTimer.GetTimeLeft();
    int factor;

    switch (this->AirstrikeTintStage) {
    case 1:
    case 7:
        factor = ((12 - left) * 256) / 6;
        break;
    case 2:
    case 8:
        factor = 0x200;
        break;
    case 4:
        factor = ((128 - left) * 256) / 64;
        break;
    case 5:
        factor = ((left + 64) * 256) / 64;
        break;
    case 6:
        factor = 0x100;
        break;
    case 3:
    case 9:
        factor = ((left + 20) * 256) / 20;
        break;
    default:
        return currentIntensity;
    }

    int result = (factor * currentIntensity) >> 8;
    if (result > 2000) {
        result = 2000;
    }
    return result;
}
