// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x727010,
//   0x727050). Every offset reconfirmed numerically; names cross-checked
//   against YRpp TriggerTypeClass.h / TEventClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x727010  TriggerTypeClass::HasGlobalSetOrClearedEvent (__thiscall)
//   FUNCTION: GAMEMD 0x727050  TriggerTypeClass::HasLocalSetOrClearedEvent  (__thiscall)

#include "trigger_type_class_more_methods.h"

// FUNCTION: GAMEMD 0x727010  (__thiscall)
// True if any event sets/clears global variable `value`
// (kind 0x1b = set, 0x1c = clear) with matching Value.
bool TriggerTypeClass::HasGlobalSetOrClearedEvent(int value) const
{
    bool result = false;
    TTriggerListNode* node = FirstEvent;
    while (node) {
        if ((node->Kind == 0x1b || node->Kind == 0x1c) && node->Value == value) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}

// FUNCTION: GAMEMD 0x727050  (__thiscall)
// True if any event sets/clears local variable `value`
// (kind 0x24 = set, 0x25 = clear) with matching Value.
bool TriggerTypeClass::HasLocalSetOrClearedEvent(int value) const
{
    bool result = false;
    TTriggerListNode* node = FirstEvent;
    while (node) {
        if ((node->Kind == 0x24 || node->Kind == 0x25) && node->Value == value) {
            result = true;
            break;
        }
        node = node->Next;
    }
    return result;
}
