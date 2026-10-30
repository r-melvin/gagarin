// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 (Ghidra disasm)
//   at each address below. Globals and callees reuse the placeholder names of
//   the neighbouring audio sources so their bindings resolve.
//
// Address index:
//   0x7515C0  FUN_007515C0
//   0x7529A0  FUN_007529A0
//   0x752340  FUN_00752340
//   0x752B40  FUN_00752B40
//   0x7532A0  FUN_007532A0

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vox_class_play_index_methods.h"

class StreamView_00752B40
{
public:
    char opaque[4];
    // FUNCTION: GAMEMD 0x407F40 (decl; reloc)
    void FUN_00407F40();
    // FUNCTION: GAMEMD 0x407A90 (decl; reloc)
    void FUN_00407A90();
};
// GLOBAL: GAMEMD 0xB1D4D8
extern StreamView_00752B40* DAT_00B1D4D8;

// GLOBAL: GAMEMD 0x00B1D37C
extern "C" void** DAT_00B1D37C;
// GLOBAL: GAMEMD 0x00B1D388
extern "C" int DAT_00B1D388;


// FUNCTION: GAMEMD 0x7515C0
//
// Index of the pointer in the vector at 0xB1D378, or -1.
int __fastcall FUN_007515C0(void* item)
{
    int n = DAT_00B1D388;
    for (int i = 0; i < n; i++) {
        if (DAT_00B1D37C[i] == item) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x752340
//
// Reset the voice state, then stop, release and clear the engine handle.
void FUN_00752340()
{
    FUN_00752370();
    if (DAT_00B1D4CC != 0) {
        DAT_00B1D4CC->FUN_00407F40();
        DAT_00B1D4CC->FUN_00407A90();
        DAT_00B1D4CC = 0;
    }
}

// FUNCTION: GAMEMD 0x7529A0
//
// Mark the speaking entry finished and forget it, stop the engine, and drop
// the queue too when asked.
void __fastcall FUN_007529A0(bool dropQueue)
{
    if (DAT_00B1D4C4 != 0) {
        DAT_00B1D4C4->State = 2;
        DAT_00B1D4C4 = 0;
    }
    if (DAT_00B1D4CC != 0) {
        DAT_00B1D4CC->FUN_00407F40();
    }
    if (dropQueue) {
        FUN_00752370();
    }
}

// FUNCTION: GAMEMD 0x752B40
//
// Stop, release and clear the second stream handle.
void FUN_00752B40()
{
    if (DAT_00B1D4D8 != 0) {
        DAT_00B1D4D8->FUN_00407F40();
        DAT_00B1D4D8->FUN_00407A90();
        DAT_00B1D4D8 = 0;
    }
}

// FUNCTION: GAMEMD 0x7532A0
//
// True when the speech entry is finished; an index out of range counts as
// finished.
bool __fastcall FUN_007532A0(int index)
{
    if (index >= 0 && index < DAT_00B1D4B0) {
        return DAT_00B1D4A4[index]->State == 2;
    }
    return true;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB1D4A4
VoxClass** DAT_00B1D4A4;
// GLOBAL: GAMEMD 0xB1D4B0
int DAT_00B1D4B0;
// GLOBAL: GAMEMD 0xB1D4C4
VoxClass* DAT_00B1D4C4;
// GLOBAL: GAMEMD 0xB1D4D8
StreamView_00752B40* DAT_00B1D4D8;
// END defined globals
