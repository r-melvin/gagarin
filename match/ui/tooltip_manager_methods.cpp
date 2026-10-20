// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Names cross-checked against YRpp ToolTipManager.h (consult-only, no
//   LICENSE; each offset reconfirmed against the user's binary below).
//
// Translation unit: ToolTipManager timer-delay accessors.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x724520   ToolTipManager::SetTimerDelay    (__thiscall)
//   FUNCTION: GAMEMD 0x724530   ToolTipManager::SaveTimerDelay   (__thiscall)
//   FUNCTION: GAMEMD 0x724540   ToolTipManager::RestoreTimeDelay (__thiscall)

#include "tooltip_manager_methods.h"

// FUNCTION: GAMEMD 0x724520  (__thiscall)
// MOV EAX,[ESP+4]; MOV [ECX+0x228],EAX; RET 4
void ToolTipManager::SetTimerDelay(int value)
{
    this->ToolTipDelay = value;
}

// FUNCTION: GAMEMD 0x724530  (__thiscall)
// MOV EAX,[ECX+0x228]; MOV [ECX+0x22c],EAX; RET
void ToolTipManager::SaveTimerDelay()
{
    this->LastToolTipDelay = this->ToolTipDelay;
}

// FUNCTION: GAMEMD 0x724540  (__thiscall)
// MOV EAX,[ECX+0x22c]; MOV [ECX+0x228],EAX; RET
void ToolTipManager::RestoreTimeDelay()
{
    this->ToolTipDelay = this->LastToolTipDelay;
}

// FUNCTION: GAMEMD 0x724C00  ToolTipManager::IsToolTipShowing (__thiscall)
// A tip is on screen exactly while the current-tip pointer is set.
bool ToolTipManager::IsToolTipShowing() const
{
    return CurrentToolTip != 0;
}
