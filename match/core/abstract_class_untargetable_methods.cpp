// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x70D4A0.

#include "abstract_class_untargetable_methods.h"

// FUNCTION: GAMEMD 0x70D4A0  AbstractClass::BecomeUntargetable
//
// Nothing may keep pointing at this object. Every techno targeting it drops
// the target (an infantry mid-mission 0x19 also loses its sub-state), unless
// this is a live techno whose +0x294 link is owned by that techno. Then the
// two references in the second array are cleared. The null-safe techno view
// is an if/else with the null case first (retail's fall-through), then the
// branchless flag mask; `self = 0; if (this) ...` puts the XOR first (1.2%).
void Abstract_0070D4A0::BecomeUntargetable()
{
    Techno_0070D4A0* self;
    if (this == 0)
        self = 0;
    else
        self = (AbstractFlags & 1) ? (Techno_0070D4A0*)this : 0;

    for (int i = DAT_00A8EC88 - 1; i >= 0; --i) {
        Techno_0070D4A0* techno = DAT_00A8EC7C[i];
        bool drop = true;
        if (self != 0 && techno->At_294 != 0 && techno->At_294->At_50 == this
            && self->Health > 0 && self->At_90 != 0)
            drop = false;
        if (techno->Target == this && drop) {
            (techno->*techno->Vptr->At_1F8)();
            if ((techno->*techno->Vptr->WhatAmI)() == 2 && techno->CurrentMission == 0x19) {
                techno->At_BC = 0;
                techno->At_6D2 = 0;
            }
            if (techno->Target == this)
                (techno->*techno->Vptr->At_3C8)(0);
        }
    }

    for (int j = DAT_008B40F8 - 1; j >= 0; --j) {
        Ref_0070D4A0* ref = DAT_008B40EC[j];
        if (ref->At_3C == this)
            ref->At_3C = 0;
        if (ref->At_40 == this)
            ref->At_40 = 0;
    }
}
