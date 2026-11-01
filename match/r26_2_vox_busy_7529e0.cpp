// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x7529E0 in the user's gamemd.exe v1.001.
//
// Address index: 0x7529E0

#include "vox_class_play_index_methods.h"

// A circular list header: the list is empty while Next points back at the header itself.
struct VoxList_007529E0 {
    int unknown_00;
    VoxList_007529E0* Next;   // +0x04
    int unknown_08;
};
GG_STATIC_ASSERT(offsetof(VoxList_007529E0, Next) == 0x04);
GG_STATIC_ASSERT(sizeof(VoxList_007529E0) == 0xC);

// GLOBAL: GAMEMD 0xB1D3C8 -- pending list.
extern VoxList_007529E0 DAT_00B1D3C8_busy;
// GLOBAL: GAMEMD 0xB1D3F0 -- list searched first.
extern VoxList_007529E0 DAT_00B1D3F0_busy;
// GLOBAL: GAMEMD 0xB1D450 -- the four priority lists.
extern VoxList_007529E0 DAT_00B1D450_busy[4];
// GLOBAL: GAMEMD 0xB1D4B8 -- the node currently speaking.
extern void* DAT_00B1D4B8_busy;

// FUNCTION: GAMEMD 0x7529E0
// Pump the speech queue, then report whether the engine is busy or any list still holds a node.
int FUN_007529E0()
{
    FUN_00752760();
    if (DAT_00B1D4CC != 0) {
        if (DAT_00B1D4CC->FUN_00408070() != 0
            || DAT_00B1D3C8_busy.Next != &DAT_00B1D3C8_busy
            || DAT_00B1D3F0_busy.Next != &DAT_00B1D3F0_busy
            || DAT_00B1D4B8_busy != 0)
            return 1;
        for (int i = 0; i < 4; i++) {
            if (DAT_00B1D450_busy[i].Next != &DAT_00B1D450_busy[i])
                return 1;
        }
    }
    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB1D3C8
VoxList_007529E0 DAT_00B1D3C8_busy;
// GLOBAL: GAMEMD 0xB1D3F0
VoxList_007529E0 DAT_00B1D3F0_busy;
// GLOBAL: GAMEMD 0xB1D450
VoxList_007529E0 DAT_00B1D450_busy[4];
// GLOBAL: GAMEMD 0xB1D4B8
void* DAT_00B1D4B8_busy;
// GLOBAL: GAMEMD 0xB1D4CC
VoxEngine_00752480* DAT_00B1D4CC;
// END defined globals
