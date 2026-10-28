// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at 0x4F1B00 and 0x4F1B20; the layout
//   (start tick +0, clock +4, duration +8) is in _layout/elapsed_timer.h.
//
//   0x4F1B00  ScenarioElapsedTimer::FUN_004F1B00  out-of-line duration constructor
//   0x4F1B20  ScenarioElapsedTimer::FUN_004F1B20  ticks left

#include "../_layout/elapsed_timer.h"

// FUNCTION: GAMEMD 0x4F1B00
// Out-of-line copy of the duration constructor: stamp the start tick and
// store the duration.
ScenarioElapsedTimer* ScenarioElapsedTimer::FUN_004F1B00(int ticks)
{
    unknown_00 = unknown_04.GetTime();
    unknown_08 = ticks;
    return this;
}

// FUNCTION: GAMEMD 0x4F1B20
// Ticks remaining: the stored duration, less the time elapsed since the start
// tick unless the timer is paused (start tick -1).
int ScenarioElapsedTimer::FUN_004F1B20()
{
    int left = unknown_08;
    if (unknown_00 != -1) {
        int elapsed = unknown_04.GetTime();
        elapsed -= unknown_00;
        if (elapsed < left) {
            return left - elapsed;
        }
        return 0;
    }
    return left;
}
