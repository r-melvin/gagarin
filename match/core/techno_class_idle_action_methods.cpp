// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm
//   0x7099E0 len 0x35, 0x709A30 len 0x3, 0x709A40 len 0x42).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x7099E0  TechnoClass::IsTimeForIdleAction (__thiscall)
//   FUNCTION: GAMEMD 0x709A30  TechnoClass::SetDestination      (__thiscall)
//   FUNCTION: GAMEMD 0x709A40  TechnoClass::EnterIdleMode       (__thiscall)
//   GLOBAL:   GAMEMD 0xA8ED84  Unsorted::CurrentFrame

#include "techno_class_idle_action_methods.h"

// FUNCTION: GAMEMD 0x7099E0  (__thiscall)
// Has the idle-action countdown run out? The timer read is CDTimerClass's
// ordinary GetTimeLeft, inlined: retail loads TimeLeft *before* testing
// StartTime, which is what writing the duration into a local first produces,
// and the `== 0` tail is emitted twice because cl duplicates it into the
// expired arm.
//
// The exit is `MOV AL,CL`, so the return type is bool, not int.
//
// PARTIAL 35.0% (7/20, was 5.0%). Written as the explicit inline countdown
// (the same shape as 0x70F7E0), the control flow, displacements and the shared
// long-form tail (`XOR ECX,ECX; TEST EAX,EAX; SETZ CL; MOV AL,CL`) are
// retail's. The one residual is the live-subtraction tail: retail repeats the
// long-form tail after the `SUB`, we emit `NEG EAX; SBB EAX,EAX; INC EAX`.
// Tried against it: `(timeLeft - elapsed) == 0`, `!(...)`, a ternary clamp
// (`SETE AL` right after the SUB, 5.0%), a bound bool local, a switch, and
// `if (x == 0) return true; return false;` - all 35.0% or worse. Earlier
// GetTimeLeft()-based spellings were byte-identical to each other at 5.0%.
bool TechnoClass::IsTimeForIdleAction()
{
    int timeLeft = this->IdleActionTimer.TimeLeft;
    if (this->IdleActionTimer.StartTime != -1) {
        int elapsed = CurrentFrame - this->IdleActionTimer.StartTime;
        if (elapsed < timeLeft)
            return (timeLeft - elapsed) == 0;
        timeLeft = 0;
    }
    return timeLeft == 0;
}

// FUNCTION: GAMEMD 0x709A30  (__thiscall)
// The TechnoClass base of the destination virtual does nothing: a plain
// `RET 8`, i.e. two stack arguments accepted and discarded. Only the movement
// leaves override it.
void TechnoClass::SetDestination(AbstractClass* dest, bool now)
{
}

// FUNCTION: GAMEMD 0x709A40  (__thiscall)
// The TechnoClass base of "settle into idle". It releases any Chrono-legionnaire
// erase currently pointed at a target, then — only when the object is not
// already busy (slot +0x4D0) and is eligible (slot +0x430) — advances the
// planning-token walk. It always reports false; the movement leaves override it
// to say otherwise.
//
// Both arguments are unused, which is why they never appear: the `RET 8` alone
// records them.
bool TechnoClass::EnterIdleMode(bool initial, bool unused)
{
    TemporalClass* temporal = this->TemporalImUsing;

    if (temporal != 0 && temporal->Target != 0) {
        temporal->LetGo();
    }
    if (!(this->*this->Vfptr->At_4D0)()) {
        if ((this->*this->Vfptr->At_430)()) {
            this->TryNextPlanningTokenNode();
        }
    }
    return false;
}
