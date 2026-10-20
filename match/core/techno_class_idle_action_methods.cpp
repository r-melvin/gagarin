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
// RESIDUAL 5.0%, and the percentage is not the story: the instruction multiset
// is retail-only {mov: 2}, 20 against 18, and every branch, every displacement
// and every constant is retail's. Retail keeps the running duration in EAX and
// borrows ECX to build the boolean (`XOR ECX,ECX; TEST EAX,EAX; SETZ CL;
// MOV AL,CL`, twice); cl keeps it in EDX and so can zero EAX up front and
// `SETE AL` directly, which is the same computation two instructions shorter.
// This is the register-colouring class of docs/residual_census.md. Three
// materially different spellings — `return GetTimeLeft() == 0;`, an
// if/else GetTimeLeft, and an early-return GetTimeLeft plus a named local and
// an explicit `if` — all emitted BYTE-IDENTICAL output, so cl never saw a
// choice here and the expression level is retired for this body.
bool TechnoClass::IsTimeForIdleAction()
{
    int remaining = this->IdleActionTimer.GetTimeLeft();

    if (remaining == 0) {
        return true;
    }
    return false;
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
