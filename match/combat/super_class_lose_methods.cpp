// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6CB7B0.

#include "super_class_lose_methods.h"

// FUNCTION: GAMEMD 0x6CB7B0  SuperClass::Lose (__thiscall)
// Take a superweapon away from its house: clear both state flags and pull it
// off the sidebar timer list. Losing one the house never had is a no-op.
// The list removal is DynamicVectorClass::RemoveItem written out inline.
// The whole body is guarded positively so the `return false` lands in the
// trailing block, matching retail's layout; an early `if (!IsPresent) return
// false;` inverts the branch and scores 11.4%.
bool SuperClass::Lose()
{
    if (IsPresent)
    {
        IsReady = false;
        IsPresent = false;

        // Through a pointer, not the object: calling `ShowTimers.FindItemIndex`
        // directly lets VC6 devirtualise (a direct CALL), while retail loads the
        // vptr and dispatches indirectly (`MOV EDX,[0xA83D50]; CALL [EDX+0x10]`).
        // Taking the address first keeps the dispatch indirect and still emits
        // the object address as an immediate.
        SuperTimerVectorClass* timers = &ShowTimers;
        SuperClass* self = this;
        int idx = timers->FindItemIndex(self);
        if (idx != -1 && idx < timers->Count)
        {
            timers->Count--;
            for (int j = idx; j < timers->Count; j++)
                timers->Items[j] = timers->Items[j + 1];
        }

        return true;
    }

    return false;
}
