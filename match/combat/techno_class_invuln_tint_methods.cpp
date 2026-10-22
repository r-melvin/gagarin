// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x70E380 (name from
//   the YRpp method map).

#include "techno_class_invuln_tint_methods.h"

// FUNCTION: GAMEMD 0x70E380  TechnoClass::GetInvulnerabilityTintIntensity (__thiscall, ret 0x4)
//
// Scale a tint intensity by the iron-curtain flash. The timer's remaining
// frames drive a per-stage ramp (a 256-based fixed-point factor), the product
// is scaled back down and capped at 2000. Stages outside 1..9 pass the
// intensity through.
int TechnoClass::GetInvulnerabilityTintIntensity(int currentIntensity)
{
    int left = this->IronTintTimer.GetTimeLeft();
    int factor;

    switch (this->IronTintStage) {
    case 1:
        factor = ((12 - left) * 256) / 6;
        break;
    case 2:
    case 8:
        factor = 0x200;
        break;
    case 3:
        factor = (left * 461 + 1020) / 20;
        break;
    case 4:
        factor = (1024 - left * 77) / 8;
        break;
    case 5:
        factor = (left * 77 + 816) / 16;
        break;
    case 6:
        factor = 51;
        break;
    case 7:
        factor = (3072 - left * 461) / 6;
        break;
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
