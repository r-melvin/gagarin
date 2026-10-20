// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4575B0.

#include "unload_all_methods.h"

// FUNCTION: GAMEMD 0x4575B0
//
// Drain the whole array, last entry first, then run the finishing slot.
//
// The loop's index is the count itself and nothing here decrements it — the call
// through 0x451690 is what shortens the array, so the loop terminates through a
// side effect. That is why the count is re-read at the bottom rather than cached.
//
// The target pointer is re-read on each of its four uses; retail reloads
// `[ESI+0x21C]` every time rather than holding it.
void Obj_004575B0::FUN_004575B0()
{
    int one = 1;

    while (this->Count > 0) {
        Item_004575B0* item = this->Items[this->Count];
        int taken = (item->*item->Vptr->At_B8)(this->Target, one);
        this->Target->FUN_004F9950(taken);
        this->FUN_00451690();
        this->Target->At_5778 = (char)one;
        this->Target->At_5779 = (char)one;
    }

    (this->*this->Vptr->At_1A0)(one);
}
