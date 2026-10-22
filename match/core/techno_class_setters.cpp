// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (each
//   offset reconfirmed against the binary in techno_class_setters.h).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x70C610   TechnoClass::SetArchiveTarget       (__thiscall)
//   FUNCTION: GAMEMD 0x70DDD0   TechnoClass::SetCurrentWeaponStage  (__thiscall)
//   FUNCTION: GAMEMD 0x7104A0   TechnoClass::ExitedOpenTopped       (__thiscall)

#include "techno_class_setters.h"

// FUNCTION: GAMEMD 0x70C610  (__thiscall)
// Store the supplied archive target pointer unconditionally.
//   MOV EAX,[ESP+4]; MOV [ECX+0x218],EAX; RET 4
void TechnoClass::SetArchiveTarget(AbstractClass* pTarget)
{
    this->ArchiveTarget = pTarget;
}

// FUNCTION: GAMEMD 0x70DDD0  (__thiscall)
// Store idx only when non-negative (the JL guards out negatives).
//   MOV EAX,[ESP+4]; TEST EAX,EAX; JL ret; MOV [ECX+0x140],EAX; RET 4
void TechnoClass::SetCurrentWeaponStage(int idx)
{
    if (idx >= 0)
        this->CurrentGattlingStage = idx;
}

// FUNCTION: GAMEMD 0x70DE00  TechnoClass::SetGattlingValue (__thiscall, ret 0x4)
// Guarded setter: a negative value is ignored rather than clamped. The value is
// also the return, which retail gets for free — EAX still holds the argument.
//
// NOTE: the name is descriptive. YRpp carries this address only as
// `sub_70DE00(int State)`; the member it writes is the committed spine's
// GattlingValue @0x144, which is what the name follows.
int TechnoClass::SetGattlingValue(int value)
{
    if (value >= 0)
        GattlingValue = value;

    return value;
}

// FUNCTION: GAMEMD 0x7104A0  (__thiscall)
// Clear the passed object's InOpenToppedTransport flag (this/ECX unused).
//   MOV EAX,[ESP+4]; TEST EAX,EAX; JZ ret; MOV byte [EAX+0x82],0; RET 4
void TechnoClass::ExitedOpenTopped(TechnoClass* pWho)
{
    if (pWho)
        pWho->InOpenToppedTransport = false;
}
