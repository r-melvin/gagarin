// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x75F610 and 0x75F7D0.
//
// WaveClass slot 10 (pointer expiry) and slot 6 (Save).
// Address index: 0x75F610 vf_10, 0x75F7D0 Save.

#include <objidl.h>
#include "../_layout/wave_class.h"
#include "logicview_87f778.h"
#include "../_layout/map_0087f7e8.h"

// GLOBAL: GAMEMD 0x87F778
extern LogicView_87F778 DAT_0087F778;
// GLOBAL: GAMEMD 0xA8E9A0
extern bool DAT_00A8E9A0;

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

// FUNCTION: GAMEMD 0x75F880
// Returns a constant. Vtable slot 12 of WaveClass (RTTI).
int WaveClass::vf_12()
{
    return 0x240;
}

// FUNCTION: GAMEMD 0x75F890
// Returns a constant. Vtable slot 30 of WaveClass (RTTI).
int WaveClass::vf_30()
{
    return 3;
}

// FUNCTION: GAMEMD 0x75F8A0
// Returns zero. Vtable slot 34 of WaveClass (RTTI).
ObjectTypeClass* WaveClass::vf_34()
{
    return 0;
}

// FUNCTION: GAMEMD 0x75F980
bool WaveClass::vf_53()
{
    if (!DAT_00A8E9A0 || InLimbo)
        return false;
    vf_55(1);
    vf_73(0);
    DAT_0087F7E8.FUN_004A9770(this);
    DAT_0087F778.FUN_0055BAE0(this);
    vf_71();
    InLimbo = true;
    NeedsRedraw = false;
    return true;
}

// FUNCTION: GAMEMD 0x7631F0
// Returns a constant. Vtable slot 11 of WaveClass (RTTI).
int WaveClass::vf_11()
{
    return 0x2B;
}
