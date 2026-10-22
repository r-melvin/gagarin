// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against the
//   YRpp (reconfirmed here).
//
// TransitionTimer — a small two-bit state machine driving a timed transition
// (used by the in-game transition/fade overlay). It owns a RateTimer plus two
// boolean state flags.
//
// Confirmed layout (from 0x4A5240 / 0x4A51F0 / 0x4A5360):
//   +0x00  double     Rate1          (FST [ESI], FMUL 900.0)
//   +0x08  RateTimer  ActionTimer    (4 dwords written at +0x08..+0x14)
//   +0x18  bool       State1         ([ESI+0x18])
//   +0x19  bool       State2         ([ESI+0x19])
//
// ActionTimer is a RateTimer (CDTimerClass + int Rate). StartTimer1x build it
// as `ActionTimer = RateTimer((int)Rate1)`: the inlined RateTimer::Start writes
//   StartTime = CurrentTime(=Unsorted::CurrentFrame), TimeLeft = rate,
//   Rate = rate, leaving CurrentTime uninitialised — exactly the four stores
// MOV [ESI+8]=CurrentFrame / MOV [ESI+0xc]=<garbage> / MOV [ESI+0x10]=rate /
// MOV [ESI+0x14]=rate seen in the disassembly (the trivial 16-byte copy of the
// temporary carries the uninitialised CurrentTime slot through).
#ifndef GG_MATCH_UI_TRANSITION_TIMER_METHODS_H
#define GG_MATCH_UI_TRANSITION_TIMER_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84 (read by the
// inlined FrameTimer when stamping ActionTimer.StartTime).
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

    void Start(int duration)
    {
        this->StartTime = this->CurrentTime;
        this->TimeLeft = duration;
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

    RateTimer(int rate)
    {
        this->Rate = rate;
        this->CDTimerClass::Start(rate);
    }
};

GG_STATIC_ASSERT(offsetof(RateTimer, Rate) == 0xC);

// ---------------------------------------------------------------------------
// TransitionTimer
// ---------------------------------------------------------------------------
struct TransitionTimer
{
    void StartTimer11(double time);   // GAMEMD 0x4A51F0 __thiscall
    void StartTimer10(double time);   // GAMEMD 0x4A5240 __thiscall
    void SetToDone();                 // GAMEMD 0x4A5360 __thiscall

    double    Rate1;        // +0x00
    RateTimer ActionTimer;  // +0x08
    bool      State1;       // +0x18
    bool      State2;       // +0x19
};

GG_STATIC_ASSERT(offsetof(TransitionTimer, Rate1) == 0x00);
GG_STATIC_ASSERT(offsetof(TransitionTimer, ActionTimer) == 0x08);
GG_STATIC_ASSERT(offsetof(TransitionTimer, State1) == 0x18);
GG_STATIC_ASSERT(offsetof(TransitionTimer, State2) == 0x19);

#endif  // GG_MATCH_UI_TRANSITION_TIMER_METHODS_H
