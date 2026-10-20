// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4C9220.

#include <stdlib.h>   // abs (the /O2 intrinsic: CDQ; XOR; SUB)
#include "facing_set_desired_methods.h"

// FUNCTION: GAMEMD 0x4C9220
//
// Start turning towards a new facing. A request for the facing already wanted
// is refused. Otherwise the rotation restarts from wherever the previous one
// had got to (Current() becomes StartFacing), the new target is recorded, and
// when a rate of turn is set the timer is restarted with the number of ROT
// steps between the two facings.
bool Facing_004C9220::SetDesired(const Dir_004C9220& facing)
{
    if (this->DesiredFacing.Raw != facing.Raw) {
        this->StartFacing = this->Current();
        this->DesiredFacing = facing;

        if ((short)this->ROT.Raw > 0) {
            short diff = (short)(this->DesiredFacing.Raw - this->StartFacing.Raw);
            this->RotationTimer = Timer_004C9220(abs(diff) / (short)this->ROT.Raw);
        }
        return true;
    }
    return false;
}
