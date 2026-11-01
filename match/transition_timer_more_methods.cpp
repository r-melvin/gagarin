// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Byte-for-byte matching decomp of TransitionTimer::IsTimerFinished /
//   Update / PercentageDone against retail gamemd.exe v1.001. Every offset,
//   constant and control-flow edge reconfirmed from the local Ghidra disasm.
//
//   0x007E1718 holds the double 1.0 (PercentageDone's "complete" value and the
//   FCOMP target in IsTimerFinished).
//   0x00A8ED84 is Unsorted::CurrentFrame.
//
// All three share the inlined CDTimerClass::GetTimeLeft from the header; the
// shapes that matter (TimeLeft read first with an early in-range return, the
// zero-rate early return in GetRatePassed, the TimeLeft store through an
// inline setter in Update, and PercentageDone as `if (State1) return ...;
// return 1.0;` so the ESI save is deferred past the guard) are documented at
// each definition.
#include "transition_timer_more_methods.h"

// FUNCTION: GAMEMD 0x4A5150  TransitionTimer::IsTimerFinished (__thiscall)
bool TransitionTimer::IsTimerFinished()
{
    if (this->State1) {
        int rate = this->ActionTimer.Rate;
        if (rate != 0) {
            double pct = (double)(rate - this->ActionTimer.GetTimeLeft()) / rate;
            if (pct != 1.0)
                return false;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x4A5290  TransitionTimer::Update (__thiscall)
// Rewrite TimeLeft as Rate minus the frames still pending, then flip State2.
// The store goes through CDTimerClass::SetTimeLeft: with a direct member
// assignment cl hoists the State2 byte load (and its SETZ) above the TimeLeft
// dword store (83.3%); `!State2`, `? false : true`, `== false`, a toggle
// inline and the whole block as an inline all keep that hoist.
void TransitionTimer::Update()
{
    if (this->State1) {
        this->ActionTimer.SetTimeLeft(this->ActionTimer.Rate - this->ActionTimer.GetTimeLeft());
        this->State2 = (this->State2 == 0);
    }
}

// FUNCTION: GAMEMD 0x4A52F0  TransitionTimer::PercentageDone (__thiscall)
// Fraction of the transition elapsed; 1.0 when not running. Written as the
// positive `if` with a trailing `return 1.0` so the inlined GetRatePassed body
// (which needs ESI) sits after the State1 guard and brings its own `PUSH ESI`;
// the ternary and the inverted early return both push in the prologue and
// merge the two 1.0 tails (20.0% / 12.5%).
double TransitionTimer::PercentageDone()
{
    if (this->State1)
        return this->ActionTimer.GetRatePassed();
    return 1.0;
}
