// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6E5E70), cross-checked against
//   YRpp TagTypeClass.h (consult-only; reconfirmed numerically here).
//
//   TagTypeClass derives the committed AbstractTypeClass layout spine. The only
//   members FindByNameOrID touches are ID (+0x24) and Name (+0x64) — both from
//   AbstractTypeClass — and the static lookup array TagTypeClass::Array.
#ifndef GG_MATCH_AI_TAG_TYPE_CLASS_METHODS_H
#define GG_MATCH_AI_TAG_TYPE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_type_class.h"

struct TagTypeClass : AbstractTypeClass
{
    // Static lookup: case-insensitive find by ID (+0x24) or Name (+0x64).
    static TagTypeClass* __fastcall FindByNameOrID(const char* name); // 0x6E5E70
};

// DynamicVectorClass<TagTypeClass*> — the global TagTypeClass::Array.
// Base @0xB0E780 (vtable). Confirmed from the disasm:
//   +0x04 Items (DAT_00B0E784), +0x10 Count (DAT_00B0E790).
struct TagTypeVectorClass
{
    void*          vtable;             // +0x00
    TagTypeClass** Items;             // +0x04
    int            Capacity;          // +0x08
    char           IsInitialized;     // +0x0C
    char           IsAllocated;       // +0x0D
    char           _pad_0E[2];        // +0x0E
    int            Count;             // +0x10
    int            CapacityIncrement; // +0x14
};

GG_STATIC_ASSERT(offsetof(TagTypeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TagTypeVectorClass, Count) == 0x10);

#endif  // GG_MATCH_AI_TAG_TYPE_CLASS_METHODS_H
