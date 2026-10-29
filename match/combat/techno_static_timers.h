// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Existing Techno.CPP static timer provider; offsets from 0x6F2AF0 and 0x70F120.
#ifndef GG_MATCH_COMBAT_TECHNO_STATIC_TIMERS_H
#define GG_MATCH_COMBAT_TECHNO_STATIC_TIMERS_H
#include "../_layout/elapsed_timer.h"
#include "../_layout/frame_timer.h"
struct TechnoStaticFrameTimer : CDTimerClass
{
    TechnoStaticFrameTimer() { StartTime = CurrentFrame; TimeLeft = 0; }
    ~TechnoStaticFrameTimer() {}
};
struct TechnoStaticClockTimer : ScenarioElapsedTimer
{
    TechnoStaticClockTimer() {}
    explicit TechnoStaticClockTimer(int ticks) : ScenarioElapsedTimer(ticks) {}
    ~TechnoStaticClockTimer() {}
};
struct TechnoStatics
{
    // GLOBAL: GAMEMD 0xB0EA80
    static TechnoStaticFrameTimer FrameTimer;
    // GLOBAL: GAMEMD 0xB0EA70
    static TechnoStaticClockTimer ClockTimer;
};
GG_STATIC_ASSERT(sizeof(TechnoStaticClockTimer) == 12);
#endif
