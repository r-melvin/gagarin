// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4DA0E0.

#include "foot_class_nav_list_methods.h"

// FUNCTION: GAMEMD 0x4DA0E0
//
// Append a waypoint to the navigation queue. Queueing the object itself onto a
// non-empty queue only raises the +0x6B1 flag (a "loop" marker); otherwise the
// flag is dropped when the queue was empty and the target is appended via the
// inlined DynamicVectorClass::AddItem. With no destination and the object in
// mission 5, it is kicked into idle unless its first radio link is a building
// whose type byte at +0x16BD is set.
void FootNav::QueueNavigationList(AbstractClass* target)
{
    if (target == 0) {
        return;
    }

    if (target == (AbstractClass*)this && this->NavQueue.Count > 0) {
        this->unknown_bool_6B1 = 1;
    } else {
        if (this->NavQueue.Count == 0) {
            this->unknown_bool_6B1 = 0;
        }
        ((NavVector_004DA0E0*)&this->NavQueue)->AddItem(target);
    }

    if (this->Destination == 0
        && (this->*(*(NavVtbl_004DA0E0**)this)->GetCurrentMission)() == 5) {
        Link_004DA0E0* link = this->FUN_0065AD30(0);
        if (link == 0
            || (link->*link->Vtbl->WhatAmI)() != 6
            || link->Type->At_16BD == 0) {
            (this->*(*(NavVtbl_004DA0E0**)this)->EnterIdleMode)(0, 1);
        }
    }
}
