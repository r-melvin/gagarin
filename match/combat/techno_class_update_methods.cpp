// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x70ED10.

#include "techno_class_update_methods.h"

// FUNCTION: GAMEMD 0x70ED10
//
// One frame of turret/barrel recoil. While a recoil is in progress the travel
// accumulates by the per-frame step and the frame countdown ticks; when it
// expires the state machine advances Compressing(1) -> Holding(2) ->
// Recovering(3) -> Inactive(0). Entering Holding zeroes the step and loads the
// hold count (a hold of <= 1 frame drops straight into Recovering); entering
// Recovering loads the recover count (clamped to at least 1) and sets the step
// to walk the full travel back over that many frames.
void RecoilData_0070ED10::Update()
{
    unsigned int state = this->State;

    if (state != 0) {
        this->TravelSoFar = this->TravelPerFrame + this->TravelSoFar;
        this->TravelFramesLeft = this->TravelFramesLeft - 1;

        if (this->TravelFramesLeft <= 0) {
            switch (state) {
            case 1:
                this->State = 2;
                this->TravelFramesLeft = this->Turret.HoldFrames;
                this->TravelPerFrame = 0.0f;
                if (this->TravelFramesLeft > 1) {
                    break;
                }
                // fall through
            case 2:
                this->State = 3;
                this->TravelFramesLeft = this->Turret.RecoverFrames;
                if (this->TravelFramesLeft < 1) {
                    this->TravelFramesLeft = 1;
                }
                this->TravelPerFrame = -((float)this->Turret.Travel / (float)this->TravelFramesLeft);
                break;
            case 3:
                this->State = 0;
                this->TravelSoFar = 0.0f;
                break;
            }
        }
    }
}
