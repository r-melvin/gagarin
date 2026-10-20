// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x41F0D0 / 0x41F180.

#include "ai_trigger_charged_methods.h"

// FUNCTION: GAMEMD 0x41F0D0
//
// AI trigger condition: is the calling house's Iron Curtain nearly charged?
// Walks the house's superweapon list for the first one whose type is
// IronCurtain (1); it must exist and be present, and the fraction of its
// recharge still outstanding must be no more than 1 - AIMinorSuperReadyPercent.
// The target house is ignored.
//
// Retail converts both integers after the GetRechargeTime call (`FILD total;
// FILD left; FDIV ST0,ST1`, the divisor left on the stack and dropped by the
// trailing `FSTP ST0`): that is the float-typed `total` local divided into a
// cast `left`. An all-int `(float)left / (float)total` folds to `FIDIV`, and
// nesting the call inside the expression converts `left` before the call.
// The timer read is the inlined CDTimerClass::GetTimeLeft in the header; its
// `else return 0` arm is what makes the paused path share the single spill
// store and the expired path store its zero out of line.
bool AITriggerTypeClass::IronCurtainCharged(HouseClass* callingHouse, HouseClass* targetHouse) const
{
    if (callingHouse == 0) {
        return false;
    }
    for (int i = 0; i < callingHouse->SupersCount; i++) {
        if (callingHouse->SupersItems[i]->Type->Type == 1) {
            SuperClass* sw = callingHouse->SupersItems[i];
            if (sw == 0) {
                return false;
            }
            if (!sw->IsPresent) {
                return false;
            }
            int left = sw->RechargeTimer.GetTimeLeft();
            float total = (float)sw->GetRechargeTime();
            if ((float)left / total > 1.0f - Rules->AIMinorSuperReadyPercent) {
                return false;
            }
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x41F180
//
// Same test for the Chronosphere (type 3).
bool AITriggerTypeClass::ChronoSphereCharged(HouseClass* callingHouse, HouseClass* targetHouse) const
{
    if (callingHouse == 0) {
        return false;
    }
    for (int i = 0; i < callingHouse->SupersCount; i++) {
        if (callingHouse->SupersItems[i]->Type->Type == 3) {
            SuperClass* sw = callingHouse->SupersItems[i];
            if (sw == 0) {
                return false;
            }
            if (!sw->IsPresent) {
                return false;
            }
            int left = sw->RechargeTimer.GetTimeLeft();
            float total = (float)sw->GetRechargeTime();
            if ((float)left / total > 1.0f - Rules->AIMinorSuperReadyPercent) {
                return false;
            }
            return true;
        }
    }
    return false;
}
