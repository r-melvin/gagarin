// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Wall-clock timer expanded at 0x686443/0x686475 and 0x68650B/0x686534.
// Default and duration constructors are expanded at 0x68647A/0x686493.
// Start tick +0, empty GameClockClass member +4, duration +8.
// GetTime at 0x6C8C40 uses the multimedia clock; this is not a frame timer.
// Inline operations have no separately claimed retail entry point.
#ifndef GG_MATCH_LAYOUT_ELAPSED_TIMER_H
#define GG_MATCH_LAYOUT_ELAPSED_TIMER_H
#include "../core/game_timing_methods.h"

// Existing opaque no-initialization tag; its retail identity is not asserted.
struct AbstractNoInit;

struct ScenarioElapsedTimer
{
    int unknown_00;
    GameClockClass unknown_04;
    int unknown_08;
    ScenarioElapsedTimer()
    {
        unknown_00 = unknown_04.GetTime();
        unknown_08 = 0;
    }
    // 0x683560 preserves the timer at +0x614 while constructing +0x620.
    explicit ScenarioElapsedTimer(const AbstractNoInit&) {}
    // Declaration: GAMEMD 0x4F1B20 -- caller648D08, clock6C8C40.
    int FUN_004F1B20();
    // Declaration: GAMEMD 0x4F1B00 -- out-of-line duration constructor, returns this.
    ScenarioElapsedTimer* FUN_004F1B00(int ticks);
    int GetTimeLeft()
    {
        int left = unknown_08;
        if (unknown_00 != -1) {
            int elapsed = unknown_04.GetTime() - unknown_00;
            return elapsed < left ? left - elapsed : 0;
        }
        return left;
    }
    explicit ScenarioElapsedTimer(int ticks)
    {
        unknown_00 = unknown_04.GetTime();
        unknown_08 = ticks;
    }
    void Pause()
    {
        if (unknown_00 != -1) {
            unknown_08 += unknown_04.GetTime() - unknown_00;
            unknown_00 = -1;
        }
    }
    void Resume()
    {
        if (unknown_00 == -1) unknown_00 = unknown_04.GetTime();
    }
};
GG_STATIC_ASSERT(offsetof(ScenarioElapsedTimer, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(ScenarioElapsedTimer, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(ScenarioElapsedTimer, unknown_08) == 8);
GG_STATIC_ASSERT(sizeof(ScenarioElapsedTimer) == 12);


#endif // GG_MATCH_LAYOUT_ELAPSED_TIMER_H
