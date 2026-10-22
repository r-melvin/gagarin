// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x752480.

#include "vox_class_play_index_methods.h"

// FUNCTION: GAMEMD 0x752480
//
// Speak one entry of the speech table. Nothing happens without an engine,
// for an index out of range, while speech is suppressed, or when the entry
// is already the one speaking; -1 for either setting means the entry's own
// default. A top-priority line first empties the pending queue and stops
// whatever is playing, and the entry is started unless its live node
// already runs at the same priority.
void VoxClass::PlayIndex(int index, int priority, int volume)
{
    if (DAT_00B1D4CC != 0 && index >= 0 && index < DAT_00B1D4B0
        && DAT_00B1D3D8 == 0) {
        VoxEntry_00752480* entry = DAT_00B1D4A4[index];
        VoxEntry_00752480* speaking = DAT_00B1D4C4;
        if (entry != speaking) {
            if (priority == -1) {
                priority = entry->Priority;
            }
            if (volume == -1) {
                volume = entry->Volume;
            }

            if (speaking != 0 && priority == 2) {
                VoxNode_00752480* node = DAT_00B1D3C8.FUN_004073C0();
                while (node != 0) {
                    FUN_00407450(node);
                    node->Entry->State = 2;
                    gg_free(node);
                    node = DAT_00B1D3C8.FUN_004073C0();
                }
                if (DAT_00B1D4C4 != 0) {
                    DAT_00B1D4C4->State = 2;
                    DAT_00B1D4C4 = 0;
                }
                if (DAT_00B1D4CC != 0) {
                    DAT_00B1D4CC->FUN_00407F40();
                }
                FUN_00752370();
                DAT_00B1D4D0 = 0;
                DAT_00B1D4D4 = 0;
            }

            VoxNode_00752480* live = FUN_00752680(entry);
            if (live == 0 || live->Priority != priority) {
                FUN_00752590(entry, priority, volume);
            }
            FUN_00752760();
        }
    }
}
