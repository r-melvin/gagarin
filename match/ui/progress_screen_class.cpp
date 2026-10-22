// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x642B10/0x642B20 (Ghidra
//   disasm). Names cross-checked against YRpp (consult-
//   only, no LICENSE; the +0x80 offset reconfirmed against the user's binary).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x642B10   ProgressScreenClass::SetSide   (__thiscall)
//   FUNCTION: GAMEMD 0x642B20   ProgressScreenClass::GetSide   (__thiscall)

#include "progress_screen_class.h"

// FUNCTION: GAMEMD 0x642B10  (__thiscall)
// MOV EAX,[ESP+4]; MOV [ECX+0x80],EAX; RET 4
void ProgressScreenClass::SetSide(int idx)
{
    this->PlayerSide = idx;
}

// FUNCTION: GAMEMD 0x642B20  (__thiscall)
// MOV EAX,[ECX+0x80]; RET
int ProgressScreenClass::GetSide()
{
    return this->PlayerSide;
}
