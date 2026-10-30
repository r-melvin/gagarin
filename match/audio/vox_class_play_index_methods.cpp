// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x752480.

#include "vox_class_play_index_methods.h"

// FUNCTION: GAMEMD 0x752480
//
// Speak one entry of the speech table. Nothing happens without an engine,
// for an index out of range, while speech is suppressed, or when the entry
// is already the one speaking; -1 for either setting means the entry's own
// default. An interrupt-type line first empties the pending queue and stops
// whatever is playing, and the entry is started unless its live node
// already runs with the same type.
void VoxClass::PlayIndex(int index, int type, int priority)
{
    if (DAT_00B1D4CC != 0 && index >= 0 && index < DAT_00B1D4B0
        && DAT_00B1D3D8 == 0) {
        VoxClass* entry = DAT_00B1D4A4[index];
        VoxClass* speaking = DAT_00B1D4C4;
        if (entry != speaking) {
            if (type == -1) {
                type = entry->Type;
            }
            if (priority == -1) {
                priority = entry->Priority;
            }

            if (speaking != 0 && type == 2) {
                VoxNode* node = DAT_00B1D3C8.FUN_004073C0();
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

            VoxNode* live = entry->GetActiveVoice();
            if (live == 0 || live->Type != type) {
                FUN_00752590(entry, type, priority);
            }
            FUN_00752760();
        }
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB1D3D8
int DAT_00B1D3D8;
// GLOBAL: GAMEMD 0xB1D4D0
int DAT_00B1D4D0;
// GLOBAL: GAMEMD 0xB1D4D4
int DAT_00B1D4D4;
// END defined globals
