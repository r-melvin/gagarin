// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// CDTimerClass: the frame-clock countdown timer (sizeof 0xC). The wall-clock
// ScenarioElapsedTimer (elapsed_timer.h) is a distinct type and stays there.
#ifndef GG_MATCH_LAYOUT_FRAME_TIMER_H
#define GG_MATCH_LAYOUT_FRAME_TIMER_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 -- the engine frame counter.
#include "../core/frame_counter.h"

// FrameTimer: empty clock policy whose value is CurrentFrame; it occupies the
// middle slot of CDTimerClass.
struct FrameTimer
{
    operator int() const { return CurrentFrame; }
};

//   +0x00 int        StartTime
//   +0x04 FrameTimer CurrentTime   (never written by the duration ctor)
//   +0x08 int        TimeLeft
// The duration ctor leaves CurrentTime uninitialised; copying the temporary
// carries that slot through verbatim: FactoryClass::CompletedProduction
// 0x4CA1A0 (`MOV ESI,[ESP+0xC]; MOV [EDI+4],ESI`), and Scenario 0x686890
// storing House+0x5640/0x5644/0x5648.
struct CDTimerClass
{
    int        StartTime;     // +0x00
    FrameTimer CurrentTime;   // +0x04
    int        TimeLeft;      // +0x08

    CDTimerClass() {}
    CDTimerClass(int duration)
    {
        this->StartTime = this->CurrentTime;
        this->TimeLeft = duration;
    }

    void Start(int duration)
    {
        this->StartTime = this->CurrentTime;
        this->TimeLeft = duration;
    }

    int GetTimeLeft() const
    {
        int timeLeft = this->TimeLeft;
        if (this->StartTime != -1) {
            int elapsed = CurrentFrame - this->StartTime;
            if (elapsed < timeLeft) {
                return timeLeft - elapsed;
            }
            return 0;
        }
        return timeLeft;
    }

    void SetTimeLeft(int value) { this->TimeLeft = value; }
    // FUNCTION: GAMEMD 0x426630 (decl; reloc) -- frames left, as the out-of-line routine reports them.
    int FUN_00426630() const;
    void Pause();
    void Resume();
};
GG_STATIC_ASSERT(offsetof(CDTimerClass, StartTime) == 0x0);
GG_STATIC_ASSERT(offsetof(CDTimerClass, CurrentTime) == 0x4);
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x8);
GG_STATIC_ASSERT(sizeof(CDTimerClass) == 0xC);

#endif  // GG_MATCH_LAYOUT_FRAME_TIMER_H
