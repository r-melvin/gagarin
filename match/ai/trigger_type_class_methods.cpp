// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x726F50  TriggerTypeClass::HasCrossesVerticalLineEvent   (__thiscall)
//   FUNCTION: GAMEMD 0x726F80  TriggerTypeClass::HasCrossesHorizontalLineEvent (__thiscall)
//   FUNCTION: GAMEMD 0x726FB0  TriggerTypeClass::HasZoneEntryByEvent           (__thiscall)
//   FUNCTION: GAMEMD 0x726FE0  TriggerTypeClass::HasAllowWinAction             (__thiscall)

#include "trigger_type_class_methods.h"

// FUNCTION: GAMEMD 0x726F50  (__thiscall)
// True if any event in the list is a Crosses-Vertical-Line event (kind 0x1a).
bool TriggerTypeClass::HasCrossesVerticalLineEvent() const
{
    bool result = false;
    TTriggerListNode* node = FirstEvent;
    while (node) {
        if (node->Kind == 0x1a) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}

// FUNCTION: GAMEMD 0x726F80  (__thiscall)
// True if any event in the list is a Crosses-Horizontal-Line event (kind 0x19).
bool TriggerTypeClass::HasCrossesHorizontalLineEvent() const
{
    TTriggerListNode* node = FirstEvent;
    bool result = false;
    while (node) {
        if (node->Kind == 0x19) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}

// FUNCTION: GAMEMD 0x726FB0  (__thiscall)
// True if any event in the list is a Zone-Entry-By event (kind 0x18).
bool TriggerTypeClass::HasZoneEntryByEvent() const
{
    TTriggerListNode* node = FirstEvent;
    bool result = false;
    while (node) {
        if (node->Kind == 0x18) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}

// FUNCTION: GAMEMD 0x726FE0  (__thiscall)
// True if any action in the list is an Allow-Win action (kind 0xf).
bool TriggerTypeClass::HasAllowWinAction() const
{
    TTriggerListNode* node = FirstAction;
    bool result = false;
    while (node) {
        if (node->Kind == 0xf) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}
