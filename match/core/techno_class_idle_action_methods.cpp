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
// Has the idle-action countdown run out? CDTimerClass::GetTimeLeft is
// inlined (TimeLeft read once, a return per arm) and the `== 0` test is
// duplicated into each return, giving retail's two `setz cl; mov al,cl` tails.
// The exit is `MOV AL,CL`, so the return type is bool, not int.
bool TechnoClass::IsTimeForIdleAction()
{
    return this->IdleActionTimer.GetTimeLeft() == 0;
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
        temporal->FUN_0071ABC0();
    }
    if (!(this->*this->Vfptr->At_4D0)()) {
        if ((this->*this->Vfptr->At_430)()) {
            this->TryNextPlanningTokenNode();
        }
    }
    return false;
}
