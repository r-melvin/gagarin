// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// GX adds new-expression exception cleanup absent from retail GetInstance;
// the no-GX probe reproduces the complete native constructor-call path.
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x6E5230,
//   0x6E52A0). Every offset, global address and vtable slot reconfirmed
//   numerically; names cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6E5230  TagClass::Destroy     (__thiscall)
//   FUNCTION: GAMEMD 0x6E52A0  TagClass::GetInstance (__fastcall, static)
//   GLOBAL:   GAMEMD 0xB0E720  TagClass::Array       (DynamicVectorClass<TagClass*>)
//   GLOBAL:   GAMEMD 0xB0F698  shared pending-delete list (vector-shaped)

#include "tag_class_destroy_methods.h"
#include "../core/abstract_registry.h"

// Registry accesses use the shared TagClass::Array storage at 0xB0E720.

// The deferred list is shared with other object classes; its owner is unknown.

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
    TagPtrVector_AddItem(reinterpret_cast<TagPtrVector*>(&DAT_00B0F698), this);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6E52A0  (__fastcall, static)
// Return the existing tag whose Type matches pType, or construct a fresh one.
// The scan reads Array.Count once into ESI. The native new-expression emits
// operator new(0x38), a null guard, and the constructor call at 0x6E4DE0.
// ---------------------------------------------------------------------------
TagClass* __fastcall TagClass::GetInstance(TagTypeClass* pType)
{
    for (int i = 0; i < TagClass::Array.Count; ++i)
    {
        TagClass* pTag = ((TagClass**)TagClass::Array.Items)[i];
        if (pTag->Type == pType)
            return pTag;
    }

    return new TagClass(pType);
}
