// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x6E5230,
//   0x6E52A0). Every offset, global address and vtable slot reconfirmed
//   numerically; names cross-checked against YRpp TagClass.h / ArrayClasses.h
//   (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6E5230  TagClass::Destroy     (__thiscall)
//   FUNCTION: GAMEMD 0x6E52A0  TagClass::GetInstance (__fastcall, static)
//   GLOBAL:   GAMEMD 0xB0E720  TagClass::Array       (DynamicVectorClass<TagClass*>)
//   GLOBAL:   GAMEMD 0xB0F698  destroyed-tag list    (DynamicVectorClass<TagClass*>)

#include "tag_class_destroy_methods.h"

// GLOBAL: GAMEMD 0xB0E720 — the engine's global list of live TagClass instances
// (YRpp: TagClass::Array). vptr @0xB0E720, Items @0xB0E724, Count @0xB0E730 —
// reconfirmed from the absolute loads in GetInstance.
extern DynamicVectorClassLayout TagClass_Array;

// GLOBAL: GAMEMD 0xB0F698 — the global DynamicVectorClass<TagClass*> that Destroy
// appends each destroyed tag to (a deferred pointer/cleanup list). vptr
// @0xB0F698, Items @0xB0F69C, Capacity @0xB0F6A0, IsAllocated @0xB0F6A5,
// Count @0xB0F6A8, CapacityIncrement @0xB0F6AC — all reconfirmed from Destroy.
extern TagPtrVector TagClass_DestroyedList;

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6E5230  (__thiscall)
// MATCHED 100%.
// Flag the tag destroyed, then append it to the global destroyed-tag vector.
// AddItem inlines: its grow path issues the virtual SetCapacity via [vptr+0x8],
// and its bool result is discarded here (no setcc tail materialises).
//
// The append is spelled as the free `TagPtrVector_AddItem(&vector, item)`, not
// as `vector.AddItem(item)`. That is the whole difference between the earlier
// 86.7% and 100%: as a member the inlined grow path accumulated into the
// capacity's register (`ADD EAX,ECX` against retail's `ADD ECX,EAX`) and loaded
// the receiver's vptr after `PUSH 0; PUSH size` instead of before them — four
// instructions, all of them ordering. Variants measured in one match_all batch:
// the member form 86.7%, the free form with the grow size written
// `Capacity + CapacityIncrement` 100%, the same with the operands swapped
// 100%, and the free form with the increment hoisted into a named local 70.0%
// (the local defeats the accumulate).
// ---------------------------------------------------------------------------
void TagClass::Destroy()
{
    this->Destroyed = 1;
    TagPtrVector_AddItem(&TagClass_DestroyedList, this);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6E52A0  (__fastcall, static)
// Return the existing tag whose Type matches pType, or construct a fresh one.
// The scan reads Array.Count once into ESI; the allocate path is a hand-rolled
// `new TagClass(pType)`: raw operator new(0x38) + null guard + ctor @0x6E4DE0
// (Construct returns `this` in EAX).
// ---------------------------------------------------------------------------
TagClass* __fastcall TagClass::GetInstance(TagTypeClass* pType)
{
    for (int i = 0; i < TagClass_Array.Count; ++i)
    {
        TagClass* pTag = ((TagClass**)TagClass_Array.Items)[i];
        if (pTag->Type == pType)
            return pTag;
    }

    TagClass* pTag = (TagClass*)::operator new(sizeof(TagClass));
    if (pTag)
        return pTag->Construct(pType);
    return 0;
}
