// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5FF320 -- the single-entry form of the
//   sweep body in shadow_block_list_methods.cpp (FUN_005FF390).
//
// Address index: 0x5FF320

#include "shadow_block_list_methods.h"

// FUNCTION: GAMEMD 0x5FF320
// Age this entry by one sweep step; once it has reached 0x50, unregister and free it.
void SpotLightClass::AgeStep()
{
    Age += 8;
    if (Age >= 0x50 && this != 0) {
        SpotlightArray_RemoveItem(this);
        operator delete(this);
    }
}
