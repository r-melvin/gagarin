// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6E5380 / 0x6E5570), cross-checked
//   against YRpp TagClass.h / TriggerClass.h (consult-only; reconfirmed
//   numerically here).
//
// TagClass — runtime instance attached to map objects that fires a TriggerClass
// linked list. This TU matches two members beyond the core accessors:
//   ContainsTrigger — walks the TriggerClass next-list (TriggerClass::NextTrigger
//                     @0x28) looking for a given trigger.
//   DeleteAll       — destroys every live tag in the global Array via the COM
//                     scalar-deleting-destructor (primary vtable slot 8, +0x20).
#ifndef GG_MATCH_AI_TAG_CLASS_MORE_METHODS_H
#define GG_MATCH_AI_TAG_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// ---------------------------------------------------------------------------
// TriggerClass — only the next-list link is touched here. AbstractClass base
// occupies [0x00..0x23]; Type @0x24; NextTrigger @0x28 (confirmed from the
// `[EAX+0x28]` list-walk in ContainsTrigger and YRpp TriggerClass.h).
// ---------------------------------------------------------------------------
struct TriggerClass
{
    char          _base[0x28];   // +0x00  AbstractClass(0x24) + Type(0x24)
    TriggerClass* NextTrigger;   // +0x28
};

GG_STATIC_ASSERT(offsetof(TriggerClass, NextTrigger) == 0x28);

// ---------------------------------------------------------------------------
// TagClass — modelled with its primary COM vtable so `delete` dispatches the
// scalar deleting destructor at slot 8 (+0x20). MSVC lays the single vptr at
// +0x00; retail's three further COM vptrs and the AbstractClass bookkeeping
// fill [0x04..0x23] (modelled as padding — full COM base is P2). Members then
// land at their retail offsets: Type @0x24, FirstTrigger @0x28 (both confirmed
// from `[EBP+0x24]`/`[EBP+0x28]` in RaiseEvent and the `[ECX+0x28]` head load
// in ContainsTrigger).
// ---------------------------------------------------------------------------
struct TagTypeClass;

struct TagClass
{
    // Primary IPersistStream vtable: 8 COM slots (0..7) precede the destructor,
    // putting the scalar deleting destructor at slot 8 = +0x20. Declared (no
    // bodies) — the only use is the virtual dispatch in DeleteAll; no vtable is
    // emitted in this TU because no TagClass is constructed here.
    virtual long  QueryInterface(const void* iid, void** ppv);  // slot 0 (+0x00)
    virtual unsigned long AddRef();                             // slot 1 (+0x04)
    virtual unsigned long Release();                            // slot 2 (+0x08)
    virtual long  GetClassID(void* pClassID);                   // slot 3 (+0x0C)
    virtual long  IsDirty();                                    // slot 4 (+0x10)
    virtual long  Load(void* pStm);                            // slot 5 (+0x14)
    virtual long  Save(void* pStm, int fClearDirty);           // slot 6 (+0x18)
    virtual long  GetSizeMax(void* pcbSize);                   // slot 7 (+0x1C)
    virtual ~TagClass();                                       // slot 8 (+0x20)

    bool ContainsTrigger(TriggerClass* pTrigger) const;        // GAMEMD 0x6E5380 __thiscall
    static void __stdcall DeleteAll();                          // GAMEMD 0x6E5570 __stdcall

    // Single vptr (+0x00) is implicit; pad over the 3 further COM vptrs and the
    // AbstractClass members up to the first modelled field.
    char          _base_rest[0x24 - 0x04];   // +0x04 .. +0x23
    TagTypeClass* Type;                       // +0x24
    TriggerClass* FirstTrigger;               // +0x28
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TagClass, Type)         == 0x24);
GG_STATIC_ASSERT(offsetof(TagClass, FirstTrigger) == 0x28);
#endif

#endif  // GG_MATCH_AI_TAG_CLASS_MORE_METHODS_H
