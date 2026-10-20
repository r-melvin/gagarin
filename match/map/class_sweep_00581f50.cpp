// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001. Full entry body and
// instruction flow are recorded in class_sweep_00581F50.h's Evidence ID.
#include "class_sweep_00581f50.h"

// FUNCTION: GAMEMD 0x581F50
void ClassSweepPrefix_00581F50::FUN_00581F50()
{
    int index = 2;
    CallbackView_00581F50* callback = &callbacks[2];
    do {
        callback->unknown_slot_0C();
        FUN_00581F90(index);
        --index;
        --callback;
    } while (index >= 0);
    DAT_0087E8B8.FUN_0042C1C0();
}
