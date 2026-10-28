// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
//   WalkLocomotionClass IPiggyback members, read off retail gamemd.exe v1.001
//   (IPiggyback table 0x7F69D4). Same shape as the Drive and DropPod bodies.
//   Address index: 0x75C850 BeginPiggyback, 0x75C8A0 EndPiggyback, 0x75CBA0 IsPiggybacking.

#include <new.h>
#include "walk_locomotion_class.h"

// FUNCTION: GAMEMD 0x75C850
HRESULT __stdcall WalkLocomotionClass::BeginPiggyback(ILocomotion* loco)
{
    if (!loco)
        return E_POINTER;
    if (Piggybackee == 0) {
        Piggybackee = loco;
        return S_OK;
    }
    return E_FAIL;
}

// FUNCTION: GAMEMD 0x75C8A0
HRESULT __stdcall WalkLocomotionClass::EndPiggyback(ILocomotion** out)
{
    if (!out)
        return E_POINTER;
    if (Piggybackee) {
        *out = Piggybackee;
        Piggybackee.Detach();
        return S_OK;
    }
    return S_FALSE;
}

// FUNCTION: GAMEMD 0x75CBA0
bool __stdcall WalkLocomotionClass::IsPiggybacking()
{
    return Piggybackee != 0;
}
