// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Byte-for-byte matching decomp of TransitionTimer::StartTimer11 /
//   StartTimer10 / SetToDone against retail gamemd.exe v1.001. Every offset,
//   constant and control-flow edge reconfirmed from the local Ghidra disasm.
//
//   0x007E27F8 holds the double 900.0 (Rate1 = time * 900.0).
//   0x007C5F00 is the CRT __ftol helper ((int) of a double on the x87 stack).
//   0x00A8ED84 is Unsorted::CurrentFrame.
#include "transition_timer_methods.h"

// FUNCTION: GAMEMD 0x4A51F0  TransitionTimer::StartTimer11 (__thiscall)
void TransitionTimer::StartTimer11(double time)
{
    if (this->State1 || this->State2 != 1) {
        this->Rate1 = time * 900.0;
        this->State1 = true;
        this->ActionTimer = RateTimer((int)this->Rate1);
        this->State2 = true;
    }
}

// FUNCTION: GAMEMD 0x4A5240  TransitionTimer::StartTimer10 (__thiscall)
void TransitionTimer::StartTimer10(double time)
{
    if (this->State1 || this->State2) {
        this->Rate1 = time * 900.0;
        this->State1 = true;
        this->ActionTimer = RateTimer((int)this->Rate1);
        this->State2 = false;
    }
}

// FUNCTION: GAMEMD 0x4A5360  TransitionTimer::SetToDone (__thiscall)
void TransitionTimer::SetToDone()
{
    if (this->State1) {
        if (this->State2) {
            this->State1 = false;
            this->State2 = true;
        }
        if (this->State1 && !this->State2) {
            this->State1 = false;
            this->State2 = false;
        }
    }
}
