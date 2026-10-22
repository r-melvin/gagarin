// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x6E5380,
//   0x6E5570). Every offset/global reconfirmed numerically; names cross-checked
//   against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6E5380  TagClass::ContainsTrigger (__thiscall)
//   FUNCTION: GAMEMD 0x6E5570  TagClass::DeleteAll       (__stdcall, static)
//   GLOBAL:   GAMEMD 0xB0E720  TagClass::Array           (DynamicVectorClass<TagClass*>)

#include "../_layout/tag_class.h"
#include "trigger_class_methods.h"

// Primary-slot call view, not a second TagClass layout or recovered COM hierarchy.
// DeleteAll reads slot +0x20 and passes the scalar-deleting flag 1.
struct TagPrimaryDeleteCallView
{
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual ~TagPrimaryDeleteCallView();
};
GG_STATIC_ASSERT(sizeof(TagPrimaryDeleteCallView) == 4);

// Registry accesses use the shared TagClass::Array storage at 0xB0E720.

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6E5380  (__thiscall)
// Walk the tag's TriggerClass next-list; report whether pTrigger is present.
// ---------------------------------------------------------------------------
bool TagClass::ContainsTrigger(TriggerClass* pTrigger) const
{
    for (TriggerClass* pNext = static_cast<TriggerClass*>(this->FirstTrigger); pNext; pNext = pNext->NextTrigger)
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
// issue the primary slot +0x20 deleting call with flag 1, then reload Count.
// The call view encodes this observed ABI without claiming the complete COM
// hierarchy or introducing another TagClass definition.
// ---------------------------------------------------------------------------
void __stdcall TagClass::DeleteAll()
{
    while (TagClass::Array.Count > 0)
    {
        TagClass* pTag = ((TagClass**)TagClass::Array.Items)[0];
        delete reinterpret_cast<TagPrimaryDeleteCallView*>(pTag);
    }
}
