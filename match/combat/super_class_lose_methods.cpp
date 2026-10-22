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
//
// PARTIAL, 17.1% (6/35). Called on the object, `ShowTimers.FindItemIndex` is
// devirtualised by cl into a direct CALL; retail loads the vptr and dispatches
// indirectly (`MOV EDX,[0xA83D50]; CALL [EDX+0x10]`), so the body from the call
// on is shifted.
bool SuperClass::Lose()
{
    if (IsPresent)
    {
        IsReady = false;
        IsPresent = false;

        int idx = ShowTimers.FindItemIndex(this);
        if (idx != -1 && idx < ShowTimers.Count)
        {
            ShowTimers.Count--;
            for (int j = idx; j < ShowTimers.Count; j++)
                ShowTimers.Items[j] = ShowTimers.Items[j + 1];
        }

        return true;
    }

    return false;
}
