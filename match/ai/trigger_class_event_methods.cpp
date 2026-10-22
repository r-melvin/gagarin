// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x726250  TriggerClass::HasCrossesHorizontalLineEvent (__thiscall)
//   FUNCTION: GAMEMD 0x726290  TriggerClass::HasCrossesVerticalLineEvent   (__thiscall)
//   FUNCTION: GAMEMD 0x7262D0  TriggerClass::HasZoneEntryByEvent           (__thiscall)
//   FUNCTION: GAMEMD 0x726310  TriggerClass::HasAllowWinAction             (__thiscall)
//
// Two distinct shapes confirmed from the disasm:
//   * HasCrosses{Horizontal,Vertical}LineEvent recurse on the TriggerClass-level
//     query of AttachedTrigger (call back into self).
//   * HasZoneEntryByEvent / HasAllowWinAction call the TriggerTypeClass-level
//     query directly on AttachedTrigger->Type (no trigger-level recursion).

#include "trigger_class_event_methods.h"

// FUNCTION: GAMEMD 0x726250  (__thiscall)
// True if this trigger (or any attached trigger) holds a Crosses-Horizontal-Line
// event.
bool TriggerClass::HasCrossesHorizontalLineEvent() const
{
    if (this->AttachedTrigger)
        return this->Type->HasCrossesHorizontalLineEvent()
            || this->AttachedTrigger->HasCrossesHorizontalLineEvent();

    return this->Type->HasCrossesHorizontalLineEvent();
}

// FUNCTION: GAMEMD 0x726290  (__thiscall)
// True if this trigger (or any attached trigger) holds a Crosses-Vertical-Line
// event.
bool TriggerClass::HasCrossesVerticalLineEvent() const
{
    if (this->AttachedTrigger)
        return this->Type->HasCrossesVerticalLineEvent()
            || this->AttachedTrigger->HasCrossesVerticalLineEvent();

    return this->Type->HasCrossesVerticalLineEvent();
}

// FUNCTION: GAMEMD 0x7262D0  (__thiscall)
// True if this trigger's type, or the attached trigger's type, holds a
// Zone-Entry-By event.
bool TriggerClass::HasZoneEntryByEvent() const
{
    if (this->AttachedTrigger)
        return this->Type->HasZoneEntryByEvent()
            || this->AttachedTrigger->Type->HasZoneEntryByEvent();

    return this->Type->HasZoneEntryByEvent();
}

// FUNCTION: GAMEMD 0x726310  (__thiscall)
// True if this trigger's type, or the attached trigger's type, holds an
// Allow-Win action.
bool TriggerClass::HasAllowWinAction() const
{
    if (this->AttachedTrigger)
        return this->Type->HasAllowWinAction()
            || this->AttachedTrigger->Type->HasAllowWinAction();

    return this->Type->HasAllowWinAction();
}
