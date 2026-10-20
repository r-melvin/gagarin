// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp ScriptClass.h (consult-only, no LICENSE; each
//   offset reconfirmed against the user's binary).
//
// Translation unit: ScriptClass action-fetch accessors.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x691500   ScriptClass::GetCurrentAction (__thiscall)
//   FUNCTION: GAMEMD 0x691540   ScriptClass::GetNextAction    (__thiscall)

#include "script_class_action_methods.h"

// FUNCTION: GAMEMD 0x691500  (__thiscall)
// Copy the action at the current cursor into *buffer; return buffer.
// CurrentMission == -1 means "no action": writes {-1, 0}. The -1 sentinel is
// materialised from the just-compared register (OR ECX,EDX with EDX == -1).
ScriptActionNode* ScriptClass::GetCurrentAction(ScriptActionNode* buffer) const
{
    int mission = this->CurrentMission;
    if (mission == -1)
    {
        ScriptActionNode none;
        none.Action = -1;
        none.Argument = 0;
        *buffer = none;
    }
    else
    {
        *buffer = this->Type->ScriptActions[mission];
    }
    return buffer;
}

// FUNCTION: GAMEMD 0x691540  (__thiscall)
// Copy the action AFTER the cursor into *buffer; return buffer. If there is no
// next action (CurrentMission+1 >= ActionsCount, signed) writes the {-1, 0}
// sentinel. The +1 is folded into the +0x8 element-stride displacement (index
// register stays CurrentMission -> base 0xAC/0xB0).
ScriptActionNode* ScriptClass::GetNextAction(ScriptActionNode* buffer) const
{
    if (this->CurrentMission + 1 >= this->Type->ActionsCount)
    {
        ScriptActionNode none;
        none.Action = -1;
        none.Argument = 0;
        *buffer = none;
    }
    else
    {
        *buffer = this->Type->ScriptActions[this->CurrentMission + 1];
    }
    return buffer;
}
