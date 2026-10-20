// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp TagClass.h / TagTypeClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6E5300  TagClass::HasCrossesVerticalLineEvent   (__thiscall)
//   FUNCTION: GAMEMD 0x6E5320  TagClass::HasCrossesHorizontalLineEvent (__thiscall)
//   FUNCTION: GAMEMD 0x6E5340  TagClass::HasZoneEntryByEvent           (__thiscall)

#include "tag_class_methods.h"

// FUNCTION: GAMEMD 0x6E5300  (__thiscall)
// True iff the tag has a type whose event list contains a Crosses-Vertical-Line
// event. Retail loads Type into ECX, guards it null, then tail-tests the type
// query's AL result. The bare `&&` return makes cl materialise the bool via the
// 32-bit `mov eax,1` / `xor eax,eax` tail that retail uses (binding to a bool
// local would instead give the 8-bit `mov al,1` / `xor al,al` form, which here
// shortens the function and shifts the JZ displacements off retail).
bool TagClass::HasCrossesVerticalLineEvent() const
{
    return Type && Type->HasCrossesVerticalLineEvent();
}

// FUNCTION: GAMEMD 0x6E5320  (__thiscall)
bool TagClass::HasCrossesHorizontalLineEvent() const
{
    return Type && Type->HasCrossesHorizontalLineEvent();
}

// FUNCTION: GAMEMD 0x6E5340  (__thiscall)
bool TagClass::HasZoneEntryByEvent() const
{
    return Type && Type->HasZoneEntryByEvent();
}

// FUNCTION: GAMEMD 0x6E57C0  TagClass::ShouldReplace (__thiscall)
// True when any attached trigger's type carries the "survives an owner change"
// flag — the tag then transfers with the object (e.g. a vehicle thief taking
// over a tank) instead of being dropped.
bool TagClass::ShouldReplace() const
{
    for (TriggerClass* trigger = FirstTrigger; trigger != 0; trigger = trigger->NextTrigger) {
        if (trigger->Type->unknown_A0)
            return true;
    }
    return false;
}
