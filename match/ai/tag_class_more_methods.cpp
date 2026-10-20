// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x6E5380,
//   0x6E5570). Every offset/global reconfirmed numerically; names cross-checked
//   against YRpp TagClass.h / TriggerClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6E5380  TagClass::ContainsTrigger (__thiscall)
//   FUNCTION: GAMEMD 0x6E5570  TagClass::DeleteAll       (__stdcall, static)
//   GLOBAL:   GAMEMD 0xB0E720  TagClass::Array           (DynamicVectorClass<TagClass*>)

#include "tag_class_more_methods.h"

// GLOBAL: GAMEMD 0xB0E720 — the engine's global list of live TagClass instances
// (YRpp: TagClass::Array). vptr @0xB0E720, Items @0xB0E724, Count @0xB0E730 —
// reconfirmed from the absolute loads in DeleteAll.
extern DynamicVectorClass TagClass_Array;

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6E5380  (__thiscall)
// Walk the tag's TriggerClass next-list; report whether pTrigger is present.
// ---------------------------------------------------------------------------
bool TagClass::ContainsTrigger(TriggerClass* pTrigger) const
{
    for (TriggerClass* pNext = this->FirstTrigger; pNext; pNext = pNext->NextTrigger)
    {
        if (pNext == pTrigger)
        {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6E5570  (__stdcall, static)
// Destroy every live tag: repeatedly take the head of the global Array and
// delete it (each tag's destructor removes itself from the Array, shrinking
// Count) until the Array is empty. `delete` dispatches the COM scalar deleting
// destructor through primary vtable slot 8 (+0x20) with flag 1.
// ---------------------------------------------------------------------------
void __stdcall TagClass::DeleteAll()
{
    while (TagClass_Array.Count > 0)
    {
        TagClass* pTag = ((TagClass**)TagClass_Array.Items)[0];
        delete pTag;
    }
}
