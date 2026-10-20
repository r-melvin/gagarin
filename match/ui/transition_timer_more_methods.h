// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against the
//   consult-only YRpp TransitionTimer.h / Timer.h (reconfirmed here).
//
// This header reuses the binding proven in transition_timer_methods.h (same
// FrameTimer / CDTimerClass / RateTimer / TransitionTimer layout) and adds the
// three read/Update accessors decompiled here:
//   0x4A5150  IsTimerFinished  (__thiscall) -> bool
//   0x4A5290  Update           (__thiscall) -> void
//   0x4A52F0  PercentageDone   (__thiscall) -> double
//
// Confirmed layout (re-derived from 0x4A5150 / 0x4A5290 / 0x4A52F0):
//   +0x00  double     Rate1
//   +0x08  RateTimer  ActionTimer   (CDTimerClass + int Rate)
//          +0x08 StartTime  [ECX+8]
//          +0x0C CurrentTime(FrameTimer, 1+3 pad)
//          +0x10 TimeLeft   [ECX+0x10]
//          +0x14 Rate       [ECX+0x14]
//   +0x18  bool       State1        ([ECX+0x18])
//   +0x19  bool       State2        ([ECX+0x19])
#ifndef GG_MATCH_UI_TRANSITION_TIMER_MORE_METHODS_H
#define GG_MATCH_UI_TRANSITION_TIMER_MORE_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84, read by the
// inlined CDTimerClass::GetTimeLeft when measuring elapsed frames.
#include "../core/frame_counter.h"

// ---------------------------------------------------------------------------
// FrameTimer — empty clock policy whose value is Unsorted::CurrentFrame. As a
// member it occupies a 1-byte slot (4 after alignment) inside CDTimerClass.
// ---------------------------------------------------------------------------
struct FrameTimer
{
    operator int() const { return CurrentFrame; }
};

// ---------------------------------------------------------------------------
// CDTimerClass = TimerStruct<FrameTimer>  (sizeof = 0x0C)
//   +0x00 int        StartTime
//   +0x04 FrameTimer CurrentTime   (1 byte + 3 pad)
//   +0x08 int        TimeLeft
// ---------------------------------------------------------------------------
struct CDTimerClass
{
    int        StartTime;
    FrameTimer CurrentTime;
    int        TimeLeft;

    // GetTimeLeft: frames remaining (clamped to 0), or TimeLeft verbatim when
    // the timer is unstamped (StartTime == -1). Inlined into every accessor.
    // The shape is load-bearing: TimeLeft is read first (it is the value that
    // flows out, so cl keeps it in EAX and loads Unsorted::CurrentFrame into
    // ECX/EDX with the 6-byte `8B 0D` form), the in-range case returns early
    // (its continuation gets its own copy in the callers), and the clamp
    // joins the unstamped path through the trailing `return left`.
    int GetTimeLeft() const
    {
        int left  = this->TimeLeft;
        int start = this->StartTime;
        if (start != -1) {
            int elapsed = CurrentFrame - start;
            if (elapsed < left)
                return left - elapsed;
            left = 0;
        }
        return left;
    }

    // SetTimeLeft: the plain store, as an inline. Update stores through this
    // rather than assigning the member directly so that cl does not hoist the
    // following State2 byte load above the TimeLeft dword store.
    void SetTimeLeft(int value)
    {
        this->TimeLeft = value;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x8);

// ---------------------------------------------------------------------------
// RateTimer : CDTimerClass  (sizeof = 0x10)
//   +0x0C int Rate
// ---------------------------------------------------------------------------
struct RateTimer : public CDTimerClass
{
    int Rate;

    // GetRatePassed: fraction of Rate elapsed, 1.0 for a zero rate. The zero
    // case is an early `return 1.0` (fall-through `FLD 1.0` right after the
    // `TEST ESI,ESI`); a ternary puts it at the end and merges it with the
    // caller's other 1.0 tail.
    double GetRatePassed()
    {
        int rate = this->Rate;
        if (rate == 0)
            return 1.0;
        return (double)(rate - this->GetTimeLeft()) / (double)rate;
    }
};
GG_STATIC_ASSERT(offsetof(RateTimer, Rate) == 0xC);

// ---------------------------------------------------------------------------
// TransitionTimer
// ---------------------------------------------------------------------------
struct TransitionTimer
{
    bool   IsTimerFinished();   // GAMEMD 0x4A5150 __thiscall
    void   Update();            // GAMEMD 0x4A5290 __thiscall
    double PercentageDone();    // GAMEMD 0x4A52F0 __thiscall

    double    Rate1;        // +0x00
    RateTimer ActionTimer;  // +0x08
    bool      State1;       // +0x18
    bool      State2;       // +0x19
};

GG_STATIC_ASSERT(offsetof(TransitionTimer, Rate1) == 0x00);
GG_STATIC_ASSERT(offsetof(TransitionTimer, ActionTimer) == 0x08);
GG_STATIC_ASSERT(offsetof(TransitionTimer, State1) == 0x18);
GG_STATIC_ASSERT(offsetof(TransitionTimer, State2) == 0x19);

#endif  // GG_MATCH_UI_TRANSITION_TIMER_MORE_METHODS_H
