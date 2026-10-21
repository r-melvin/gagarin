// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x53D310 and 0x5FFFA0.
//
// Global effect-array sweeps, ordered ascending by retail address.

#include "effect_array_update_methods.h"

// FUNCTION: GAMEMD 0x53D310  IonBlastClass::UpdateAll (__fastcall, static)
// Descending walk so an element that removes itself does not skip its
// neighbour.
void __fastcall IonBlastClass::UpdateAll()
{
    for (int i = IonBlastArray.Count - 1; i >= 0; i--) {
        ((IonBlastClass**)IonBlastArray.Items)[i]->Update();
    }
}

// FUNCTION: GAMEMD 0x5FFFA0  SpotLightClass::DrawAll (__fastcall, static)
void __fastcall SpotLightClass::DrawAll()
{
    for (int i = SpotlightArray.Count - 1; i >= 0; i--) {
        ((SpotLightClass**)SpotlightArray.Items)[i]->Draw();
    }
}
