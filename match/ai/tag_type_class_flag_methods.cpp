// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6E61F0 / 0x6E6220 /
//   0x6E6250 / 0x6E6280 / 0x6E62B0 via the local Ghidra disassembly. Offsets
//   confirmed numerically (see the header).
//
// TagTypeClass trigger-list folds. All five share one shape: walk the tag's
// TriggerTypeClass list and delegate to the same-named predicate on each
// trigger. GetFlags accumulates; the four Has* short-circuit on the first hit.
// Functions ordered ascending by retail address.

#include "tag_type_class_flag_methods.h"

// FUNCTION: GAMEMD 0x6E61F0  TagTypeClass::GetFlags (__thiscall)
// Retail keeps the accumulator in EDI and returns it through EAX, so this is a
// full int fold rather than the BYTE YRpp's `using Flags = BYTE` suggests.
int TagTypeClass::GetFlags() const
{
    int flags = 0;
    for (TriggerTypeClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        flags |= trigger->GetFlags();
    }
    return flags;
}

// FUNCTION: GAMEMD 0x6E6220  TagTypeClass::HasAllowWinAction (__thiscall)
bool TagTypeClass::HasAllowWinAction() const
{
    for (TriggerTypeClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        if (trigger->HasAllowWinAction()) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6E6250  TagTypeClass::HasCrossesHorizontalLineEvent (__thiscall)
bool TagTypeClass::HasCrossesHorizontalLineEvent() const
{
    for (TriggerTypeClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        if (trigger->HasCrossesHorizontalLineEvent()) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6E6280  TagTypeClass::HasCrossesVerticalLineEvent (__thiscall)
bool TagTypeClass::HasCrossesVerticalLineEvent() const
{
    for (TriggerTypeClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        if (trigger->HasCrossesVerticalLineEvent()) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6E62B0  TagTypeClass::HasZoneEntryByEvent (__thiscall)
bool TagTypeClass::HasZoneEntryByEvent() const
{
    for (TriggerTypeClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        if (trigger->HasZoneEntryByEvent()) {
            return true;
        }
    }
    return false;
}
