// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entry 0x004B4D70 reads timer StartTime at +0 and TimeLeft at +8, compares
//   StartTime with -1, then computes signed CurrentFrame - StartTime from global
//   0x00A8ED84. If StartTime is -1 it returns TimeLeft unchanged; otherwise
//   it returns max(TimeLeft - elapsed, 0). The caller at 0x004B020D
//   invokes it with ECX holding the timer address and consumes EAX; other direct
//   callers do the same. The two accessed offsets and CDTimerClass size are
//   asserted by the retail-backed layout.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/locomotion_class.h"

// GLOBAL: GAMEMD 0x00A8ED84 -- frame count read by the timer helper.
#include "../core/frame_counter.h"

GG_STATIC_ASSERT(offsetof(CDTimerClass, StartTime) == 0x00);
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimerClass) == 0x0C);

// FUNCTION: GAMEMD 0x004B4D70
int __fastcall FUN_004B4D70(CDTimerClass* timer)
{
    int startTime = timer->StartTime;
    int timeLeft = timer->TimeLeft;
    if (startTime != -1) {
        int elapsed = CurrentFrame - startTime;
        if (elapsed < timeLeft)
            return timeLeft - elapsed;
        return 0;
    }
    return timeLeft;
}
