// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x752680 in the user's gamemd.exe v1.001.
//
// Address index: 0x752680
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

#include "vox_class_play_index_methods.h"

// GLOBAL: GAMEMD 0xB1D3F0 -- list of nodes searched first.
extern VoxQueue_00752480 DAT_00B1D3F0;
// GLOBAL: GAMEMD 0xB1D4B8 -- the node currently speaking.
extern VoxNode* DAT_00B1D4B8;
// GLOBAL: GAMEMD 0xB1D450 -- the four priority lists (0xC bytes each).
struct VoxQueueSlot_00B1D450 {
    VoxQueue_00752480 List;   // +0x00
    char unknown_04[8];
};
GG_STATIC_ASSERT(sizeof(VoxQueueSlot_00B1D450) == 0xC);
extern VoxQueueSlot_00B1D450 DAT_00B1D450[4];

// FUNCTION: GAMEMD 0x752680
// Find the live node of an entry: search the first list, the speaking node, the four priority
// lists from the last, then the pending list.
VoxNode* VoxClass::GetActiveVoice()
{
    VoxNode* node;
    for (node = DAT_00B1D3F0.FUN_004073C0(); node != 0; node = node->FUN_004073E0()) {
        if (node->Event == this)
            return node;
    }
    if (DAT_00B1D4B8 != 0 && DAT_00B1D4B8->Event == this)
        return DAT_00B1D4B8;
    for (int i = 3; i >= 0; i--) {
        for (node = DAT_00B1D450[i].List.FUN_004073C0(); node != 0; node = node->FUN_004073E0()) {
            if (node->Event == this)
                return node;
        }
    }
    for (node = DAT_00B1D3C8.FUN_004073C0(); node != 0; node = node->FUN_004073E0()) {
        if (node->Event == this)
            return node;
    }
    return 0;
}
