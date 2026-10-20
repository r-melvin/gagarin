// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x629720.

#include "parasite_class_grapple_methods.h"

// FUNCTION: GAMEMD 0x629720
//
// One tick of the grapple animation. The grapple state picks a base frame and
// a per-frame delay (states 0 and 1: base 0, delay 3; state 2: base 80, delay
// 4; anything else: base 160, delay 4). Every `delay` ticks the frame counter
// advances; once it reaches 10 the grapple is over (true). Otherwise the
// grapple anim, if any, is pointed at the frame for the victim's current
// facing and re-timed.
bool ParasiteClass_00629720::UpdateGrapple()
{
    Dir_00629720 dir = this->Victim->PrimaryFacing.Current();
    int base;
    int delay;

    switch (this->GrappleState) {
    case 0:
    case 1:
        base = 0;
        delay = 3;
        break;
    case 2:
        base = 80;
        delay = 4;
        break;
    default:
        base = 160;
        delay = 4;
        break;
    }

    if (++this->GrappleAnimDelay >= delay) {
        this->GrappleAnimDelay = 0;
        if (++this->GrappleAnimFrame >= 10) {
            return true;
        }
        Anim_00629720* anim = this->GrappleAnim;
        if (anim != 0) {
            anim->Timer = CDTimer_00629720(0x80);
            anim->At_C0 = 0x80;
            this->GrappleAnim->At_AC =
                this->GrappleAnimFrame + (int)(((dir.Raw >> 12) + 1 >> 1) & 7) * 10 + base;
        }
    }
    return false;
}
