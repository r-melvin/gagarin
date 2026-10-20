// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7091D0.

#include "techno_class_passive_acquire_methods.h"

// FUNCTION: GAMEMD 0x7091D0
//
// Whether this object may pick up targets of its own accord. A chain of
// rejections: while warping something out, while enslaved, when the type
// forbids it, when an occupiable building has no occupants, when a human-owned
// object of the kind that defers to the player, when captured beyond control;
// then only an armed object says yes.
//
// Written as one &&-chained precondition with the ||-chained building exemption
// nested inside and a single trailing `return false`: that is what gives retail
// its one shared `XOR AL,AL` tail. A ladder of `if (...) return false;` gives
// every rejection its own pop/xor/ret block (7.3%). The captured flag is a
// named bool (BL) computed before the ownership test.
bool Obj_007091D0::CanPassiveAcquireTargets()
{
    if (!(this->*this->Vtbl->At_1DC)()
        && this->SlaveOwner == 0
        && (this->*this->Vtbl->GetTechnoType)()->At_D99 != 0
        && ((this->*this->Vtbl->WhatAmI)() != 6
            || this->BuildingType->At_157B == 0
            || (this->*this->Vtbl->At_408)() != 0))
    {
        bool captured = this->CaptureManager != 0
                        && this->CaptureManager->CannotControlAnyMore();

        if ((!(this->*this->Vtbl->At_330)() || !this->Owner->IsControlledByHuman())
            && !captured
            && (this->*this->Vtbl->At_2AC)())
        {
            return true;
        }
    }
    return false;
}
