// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x50E0E0.

#include "house_class_lost_powered_center_methods.h"

// FUNCTION: GAMEMD 0x50E0E0
//
// One powering centre of this house has gone. Once the count reaches zero
// every live techno of this house whose type is the powered one is
// deactivated, walking the techno array from the top; if any was, and the
// house is the local player's, the "robot tanks offline" EVA line plays.
void House_0050E0E0::LostPoweredCenter(Type_0050E0E0* type)
{
    if (--this->PoweredCenterCount == 0 && type != 0) {
        bool found = false;
        for (int i = DAT_00A8EC78.Count - 1; i >= 0; i--) {
            Techno_0050E0E0* techno = DAT_00A8EC78.Items[i];
            if (techno->Owner == this
                && (techno->*techno->Vtbl->GetTechnoType)() == type
                && !techno->InLimbo) {
                techno->Deactivate();
                found = true;
            }
        }
        if (found && DAT_00A8E9A0 && this->IsControlledByCurrentPlayer()
            && DAT_00A8E7AC == 0) {
            Vox_0050E0E0::Play(STR_00824E4C, -1, -1);
        }
    }
}
