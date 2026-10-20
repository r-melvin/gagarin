// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp TriggerClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x7263A0  TriggerClass::NotifyGlobalChanged (__thiscall)
//   FUNCTION: GAMEMD 0x7263D0  TriggerClass::NotifyLocalChanged  (__thiscall)

#include "trigger_class_methods.h"

// FUNCTION: GAMEMD 0x7263A0  (__thiscall)
// Walk this trigger and its NextTrigger chain; for each trigger whose type has
// a Global Set/Cleared event referencing idxGlobal, reset that trigger's timers.
void TriggerClass::NotifyGlobalChanged(int idxGlobal)
{
    for (TriggerClass* trigger = this; trigger; trigger = trigger->NextTrigger)
    {
        if (trigger->Type->HasGlobalChangedEvent(idxGlobal))
            trigger->ResetTimers();
    }
}

// FUNCTION: GAMEMD 0x7263D0  (__thiscall)
// As NotifyGlobalChanged, but for Local Set/Cleared events.
void TriggerClass::NotifyLocalChanged(int idxLocal)
{
    for (TriggerClass* trigger = this; trigger; trigger = trigger->NextTrigger)
    {
        if (trigger->Type->HasLocalChangedEvent(idxLocal))
            trigger->ResetTimers();
    }
}
