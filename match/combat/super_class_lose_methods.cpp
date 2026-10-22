// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6CB7B0.

#include "super_class_lose_methods.h"

// FUNCTION: GAMEMD 0x6CB7B0  SuperClass::Lose (__thiscall)
// Take a superweapon away from its house: clear both state flags and pull it
// off the sidebar timer list. Losing one the house never had is a no-op.
// The list removal is the inline DynamicVectorClass::RemoveItem. Its
// FindItemIndex call goes through `this` inside the inlined member, so cl
// keeps retail's indirect dispatch (`MOV EDX,[0xA83D50]; CALL [EDX+0x10]`).
bool SuperClass::Lose()
{
    if (IsPresent)
    {
        IsReady = false;
        IsPresent = false;

        ShowTimers.RemoveItem(this);

        return true;
    }

    return false;
}
