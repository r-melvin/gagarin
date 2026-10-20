// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x41FD60 and 0x41FE20.

#include "ai_trigger_register_methods.h"

// FUNCTION: GAMEMD 0x41FD60
//
// Record a successful firing. A track-record bonus is computed once the
// trigger has any attempts behind it: the success ratio less one half, scaled
// back up by the attempt count, floored at zero. The rules-supplied success
// delta plus that bonus is added to the current weight, which is then clamped
// into [minimum, maximum]. Both counters are bumped.
void AITriggerTypeClass::RegisterSuccess()
{
    int attempts = this->Attempts;
    double bonus = 0.0;

    if (attempts > 0) {
        bonus = ((double)this->Successes / (double)attempts - 0.5) * (double)attempts;
        if (bonus < 0.0) {
            bonus = 0.0;
        }
    }

    this->Weight_Current = Rules->AITriggerSuccessWeightDelta + this->Weight_Current + bonus;
    if (this->Weight_Current < this->Weight_Minimum) {
        this->Weight_Current = this->Weight_Minimum;
    }
    if (this->Weight_Current > this->Weight_Maximum) {
        this->Weight_Current = this->Weight_Maximum;
    }

    this->Successes = this->Successes + 1;
    this->Attempts = attempts + 1;
}

// FUNCTION: GAMEMD 0x41FE20
//
// Record a failed firing. The same track-record term, additionally scaled by
// the rules coefficient and capped at zero (so it can only penalise), is added
// together with the failure delta; the weight is clamped the same way. Only the
// attempt counter is bumped.
void AITriggerTypeClass::RegisterFailure()
{
    int attempts = this->Attempts;
    double penalty = 0.0;

    if (attempts > 0) {
        penalty = ((double)this->Successes / (double)attempts - 0.5)
                  * Rules->AITriggerTrackRecordCoefficient * (double)attempts;
        if (penalty > 0.0) {
            penalty = 0.0;
        }
    }

    this->Weight_Current = Rules->AITriggerFailureWeightDelta + this->Weight_Current + penalty;
    if (this->Weight_Current < this->Weight_Minimum) {
        this->Weight_Current = this->Weight_Minimum;
    }
    if (this->Weight_Current > this->Weight_Maximum) {
        this->Weight_Current = this->Weight_Maximum;
    }

    this->Attempts = attempts + 1;
}
