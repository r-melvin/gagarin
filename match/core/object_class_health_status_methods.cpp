// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5F5DD0.

#include "object_class_health_status_methods.h"

// FUNCTION: GAMEMD 0x5F5DD0
//
// Health band: 0 (red) when the health fraction is at or below ConditionRed and
// the object is still alive; 1 (yellow) when it is above ConditionRed but at or
// below ConditionYellow; otherwise 2 (green). A dead object (Health <= 0) falls
// through the first test and lands on 2.
//
// The fraction is spelled out three times because GetType() is virtual: each
// band test re-issues the call, exactly as retail does (three `FILD [ESI+0x6C];
// FSTP; CALL [vtbl+0x88]; FILD [EAX+0xA0]; FDIVR` groups).
int ObjectHealthStatus::GetHealthStatus() const
{
    if ((double)this->Health / (double)HEALTH_GET_TYPE(this)->Strength
            <= HealthRulesInstance->ConditionRed
        && this->Health > 0)
    {
        return 0;
    }

    if ((double)this->Health / (double)HEALTH_GET_TYPE(this)->Strength
            > HealthRulesInstance->ConditionRed
        && (double)this->Health / (double)HEALTH_GET_TYPE(this)->Strength
            <= HealthRulesInstance->ConditionYellow)
    {
        return 1;
    }

    return 2;
}
