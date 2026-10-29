// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the address below.

#include "../_layout/elapsed_timer.h"

// FUNCTION: GAMEMD 0x4A50A0
// Busy-waits for the given number of clock ticks on a local interval timer.
void __fastcall FUN_004A50A0(int ticks)
{
    ScenarioElapsedTimer timer(ticks);
    while (timer.GetTimeLeft()) {
    }
}
