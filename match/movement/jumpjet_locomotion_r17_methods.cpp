// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x54B7E0 in the user's retail gamemd.exe v1.001; layout and
//   tables in _layout/jumpjet_locomotion_class.h.
//
// JumpjetLocomotionClass persistence. Address index: 0x54B7E0.

#include "../_layout/jumpjet_locomotion_class.h"

// FUNCTION: GAMEMD 0x54B7E0
// Saves the base locomotor, then a flag byte and, when a locomotor is piggybacked,
// that locomotor as an OLE persistent stream.
HRESULT __stdcall JumpjetLocomotionClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = LocomotionClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        bool hasPiggyback;
        if (Piggybackee != 0) {
            hasPiggyback = true;
            pStm->Write(&hasPiggyback, 1, 0);
            IPersistStreamPtr persist(Piggybackee);
            return OleSaveToStream(persist, pStm);
        }
        hasPiggyback = false;
        pStm->Write(&hasPiggyback, 1, 0);
    }
    return hr;
}
