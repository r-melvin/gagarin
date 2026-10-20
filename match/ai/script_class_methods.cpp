// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp ScriptClass.h (consult-only, no LICENSE; each
//   offset reconfirmed against the user's binary).
//
// Translation unit: ScriptClass mission-cursor accessors.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x691590   ScriptClass::ClearMission   (__thiscall)
//   FUNCTION: GAMEMD 0x6915A0   ScriptClass::SetMission     (__thiscall)
//   FUNCTION: GAMEMD 0x6915B0   ScriptClass::NextMission    (__thiscall)
//
// NOTE on 0x6915B0: YRpp labels 0x6915B0 "HasNextMission", but the retail bytes
// there INCREMENT CurrentMission before the compare (MOV EAX,[ECX+0x2C]; INC
// EAX; MOV [ECX+0x2C],EAX; ...), i.e. they are the `NextMission()` body
// (`++CurrentMission; return HasNextMission();` with HasNextMission inlined).
// The pure const HasNextMission lives at 0x6915D0. This TU matches the bytes
// actually present at 0x6915B0.

#include "script_class_methods.h"

// FUNCTION: GAMEMD 0x691590  (__thiscall)
// CurrentMission = -1; return true.
//   C7 41 2C FFFFFFFF  mov [ecx+0x2C], -1
//   B0 01              mov al, 1
//   C3                 ret
bool ScriptClass::ClearMission()
{
    this->CurrentMission = -1;
    return true;
}

// FUNCTION: GAMEMD 0x6915A0  (__thiscall)
// CurrentMission = nLine; return true.
//   8B 44 24 04  mov eax, [esp+4]
//   89 41 2C     mov [ecx+0x2C], eax
//   B0 01        mov al, 1
//   C2 04 00     ret 4
bool ScriptClass::SetMission(int nLine)
{
    this->CurrentMission = nLine;
    return true;
}

// FUNCTION: GAMEMD 0x6915B0  (__thiscall)  [YRpp label: HasNextMission]
// ++CurrentMission; return CurrentMission < Type->ActionsCount.
// The increment leaves the new value in EAX, reused by the unsigned compare
// (CMP EAX,[ECX+0xA0]; SBB EAX,EAX; NEG EAX) -> bool.
bool ScriptClass::NextMission()
{
    ++this->CurrentMission;
    return this->CurrentMission < this->Type->ActionsCount;
}
