// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x75F610 and 0x75F7D0.
//
// WaveClass slot 10 (pointer expiry) and slot 6 (Save).
// Address index: 0x75F610 vf_10, 0x75F7D0 Save.

#include <objidl.h>
#include "../_layout/wave_class.h"

// FUNCTION: GAMEMD 0x75F610
void WaveClass::vf_10(void* target, bool removed)
{
    ObjectClass::vf_10(target, removed);
    if (unknown_1D4 == target)
        unknown_1D4 = 0;
    if (unknown_AC == target)
        unknown_AC = 0;
}

// FUNCTION: GAMEMD 0x75F7D0
HRESULT __stdcall WaveClass::Save(IStream* pStm, BOOL fClearDirty)
{
    AbstractClass::Save(pStm, fClearDirty);
    int count = unknown_1F0.Count;
    HRESULT hr = pStm->Write(&count, 4, 0);
    if (hr >= 0) {
        for (int i = 0; i < count; i++) {
            hr = pStm->Write(&unknown_1F0.Items[i], 4, 0);
            if (hr < 0)
                break;
        }
    }
    return hr;
}
