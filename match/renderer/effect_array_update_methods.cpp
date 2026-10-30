// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x53D310.
//
// Ion blast effect-array sweep.

#include "effect_array_update_methods.h"

// FUNCTION: GAMEMD 0x53D310  IonBlastClass::UpdateAll (__fastcall, static)
// Descending walk so an element that removes itself does not skip its
// neighbour.
void IonBlastClass::UpdateAll()
{
    for (int i = IonBlastArray.Count - 1; i >= 0; i--) {
        ((IonBlastClass**)IonBlastArray.Items)[i]->Update();
    }
}


// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAC1678
DynamicVectorClassLayout SpotlightArray;
// END defined globals
