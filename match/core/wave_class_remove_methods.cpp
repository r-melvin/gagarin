// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x75F980 (same removal sequence as ObjectClass slot 53, 0x5F4D30, without the alpha-image step).
//
// WaveClass slot 53: take the wave off the map and the logic list.
// Address index: 0x75F980 vf_53.

#include "../_layout/wave_class.h"


// The logic object list at 0x87F778.
#include "logicview_87f778.h"
#include "../_layout/map_0087f7e8.h"
// GLOBAL: GAMEMD 0x87F778
extern LogicView_87F778 DAT_0087F778;

// GLOBAL: GAMEMD 0xA8E9A0
extern bool DAT_00A8E9A0;

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
