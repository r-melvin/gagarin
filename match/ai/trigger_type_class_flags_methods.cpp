// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (reconfirmed).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x727120  TriggerTypeClass::FindByNameOrID  (__fastcall)
//   FUNCTION: GAMEMD 0x7271E0  TriggerTypeClass::GetFlags        (__thiscall)
//   GLOBAL:   GAMEMD 0x8B4178  TriggerTypeClass::Array  (accessed 0x18-byte vector prefix)
//   LIBRARY:  GAMEMD 0x7C8D20  _strcmpi  (CRT; excluded from match target)

#include "trigger_type_class_flags_methods.h"

// --- referenced retail callees (declared, no body => reloc-normalised CALLs) ---
extern "C" int __cdecl _strcmpi(const char*, const char*);

// Event-kind -> flag bits (GAMEMD 0x71F680) and action-kind -> flag bits
// (GAMEMD 0x6E3EE0). Both take the kind in ECX and return the bits in EAX.
int EventKindToFlags(int kind);   // 0x71F680
int ActionKindToFlags(int kind);  // 0x6E3EE0


// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x727120  (__fastcall — name in ECX)
//
// Linear case-insensitive lookup of `name` in TriggerTypeClass::Array, matching
// either the entry's ID (+0x24) or its Name (+0x64). Returns the entry pointer,
// or null. Count/Items are reloaded from the global each iteration.
// ---------------------------------------------------------------------------
TriggerTypeClass* TriggerTypeClass::FindByNameOrID(const char* name)
{
    if (name)
    {
        for (int i = 0; i < TriggerTypeClass::Array.Count; ++i)
        {
            if (_strcmpi(((TriggerTypeClass**)TriggerTypeClass::Array.Items)[i]->ID, name) == 0 ||
                _strcmpi(((TriggerTypeClass**)TriggerTypeClass::Array.Items)[i]->Name, name) == 0)
                return ((TriggerTypeClass**)TriggerTypeClass::Array.Items)[i];
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x7271E0  (__thiscall)
//
// Accumulate the flag bits contributed by every event (FirstEvent list) and
// every action (FirstAction list) of this trigger, then OR in the flags of the
// chained NextTrigger recursively.
// ---------------------------------------------------------------------------
unsigned int TriggerTypeClass::GetFlags()
{
    unsigned int flags = 0;
    TTriggerListNode* node;

    for (node = FirstEvent; node != 0; node = node->Next)
        flags |= EventKindToFlags(node->Kind);

    for (node = FirstAction; node != 0; node = node->Next)
        flags |= ActionKindToFlags(node->Kind);

    if (NextTrigger != 0)
        return NextTrigger->GetFlags() | flags;

    return flags;
}
