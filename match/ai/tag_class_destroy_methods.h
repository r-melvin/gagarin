// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6E5230 / 0x6E52A0), cross-checked
//   against YRpp TagClass.h / ArrayClasses.h (consult-only; every offset and
//   vtable slot reconfirmed numerically here).
//
// TagClass — two lifecycle members:
//   Destroy     — sets Destroyed @0x34 and appends `this` to the global
//                 DynamicVectorClass<TagClass*> @0xB0F698 (inlined AddItem,
//                 result discarded; the grow path issues the virtual SetCapacity
//                 through vtable slot 2 = [vptr+0x8]).
//   GetInstance — static __fastcall: scans TagClass::Array @0xB0E720 for a tag
//                 whose Type @0x24 matches pType, else `new TagClass(pType)`
//                 (raw operator new(0x38) + null guard + ctor @0x6E4DE0).
#ifndef GG_MATCH_AI_TAG_CLASS_DESTROY_METHODS_H
#define GG_MATCH_AI_TAG_CLASS_DESTROY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// The tag's type pointer target. Only used as the element identity key (Type
// @0x24) and the ctor argument; no members of it are touched here.
struct TagTypeClass;

// ---------------------------------------------------------------------------
// TagClass — modelled as a plain struct (neither method dispatches virtually on
// a TagClass, and the ctor is external), padded so the touched members land at
// their retail offsets and sizeof() drives the exact `push 0x38` allocation:
//   Type      @0x24  (`cmp [eax+0x24], edi` element key in GetInstance; ctor arg)
//   Destroyed @0x34  (`mov byte [esi+0x34], 1` first store in Destroy)
//   sizeof    0x38   (`push 0x38` before operator new in GetInstance)
// ---------------------------------------------------------------------------
struct TagClass
{
    // GLOBAL: GAMEMD 0xB0E720 -- same registry as the shared TagClass layout.
    static DynamicVectorClassLayout Array;

    char          _base[0x24];          // +0x00  AbstractClass + 4 COM vptrs
    TagTypeClass* Type;                 // +0x24
    char          _mid[0x34 - 0x28];    // +0x28  FirstTrigger / InstanceCount /
                                        //        DefaultCoords
    unsigned char Destroyed;            // +0x34
    char          _tail[0x38 - 0x35];   // +0x35  IsExecuting + 2 pad

    void Destroy();
    static TagClass* __fastcall GetInstance(TagTypeClass* pType);

    // Constructor stand-in (GAMEMD 0x6E4DE0, __thiscall, returns `this` in EAX).
    // Declared (no body) so GetInstance emits the construct call with a
    // normalised relocation.
    TagClass* Construct(TagTypeClass* pType);
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TagClass, Type)      == 0x24);
GG_STATIC_ASSERT(offsetof(TagClass, Destroyed) == 0x34);
GG_STATIC_ASSERT(sizeof(TagClass)              == 0x38);
#endif

// ---------------------------------------------------------------------------
// TagPtrVector — the engine's DynamicVectorClass<TagClass*> as seen by Destroy's
// inlined AddItem. Identical storage shape to the committed DynamicVectorClass
// but with the YR two-bool header (IsInitialized @0x0C, IsAllocated @0x0D) made
// explicit, because AddItem reads the IsAllocated *byte* at +0x0D
// (`mov cl, byte [+0xD]`). The three leading virtuals reproduce the VectorClass
// vtable so the grow path's `SetCapacity` dispatches through slot 2 = [vptr+0x8].
// Declared (no bodies) — the global is extern and never constructed here, so no
// vtable is emitted; the dispatch uses the runtime vptr.
// ---------------------------------------------------------------------------
struct TagPtrVector
{
    virtual ~TagPtrVector();                                 // slot 0  +0x00
    virtual bool Equals(const TagPtrVector& other) const;    // slot 1  +0x04
    virtual bool SetCapacity(int capacity, void* pMem);      // slot 2  +0x08

    void*         Items;              // +0x04
    int           Capacity;          // +0x08
    unsigned char IsInitialized;     // +0x0C
    unsigned char IsAllocated;       // +0x0D
    int           Count;             // +0x10
    int           CapacityIncrement; // +0x14

};

// Inlined into Destroy (YRpp DynamicVectorClass::AddItem). Result discarded at
// the call site, so no boolean is materialised.
//
// Written as a FREE function taking the vector as its first pointer parameter
// rather than as a TagPtrVector member, which is what takes Destroy from 86.7%
// to 100%. As a member, cl accumulated the grow size into the capacity's own
// register (`ADD EAX,ECX`) and loaded the receiver's vptr after the two
// argument pushes; as a free function it accumulates into the increment's
// register (retail's `ADD ECX,EAX`) and hoists the vptr load above the pushes.
// Nothing in the body changes — only where the function's edge sits.
inline bool TagPtrVector_AddItem(TagPtrVector* v, TagClass* item)
{
    if (v->Count >= v->Capacity)
    {
        if (!v->IsAllocated && v->Capacity != 0)
            return false;
        if (v->CapacityIncrement <= 0)
            return false;
        if (!v->SetCapacity(v->Capacity + v->CapacityIncrement, 0))
            return false;
    }
    int i = v->Count++;
    ((TagClass**)v->Items)[i] = item;
    return true;
}

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TagPtrVector, Items)             == 0x04);
GG_STATIC_ASSERT(offsetof(TagPtrVector, Capacity)          == 0x08);
GG_STATIC_ASSERT(offsetof(TagPtrVector, IsAllocated)       == 0x0D);
GG_STATIC_ASSERT(offsetof(TagPtrVector, Count)             == 0x10);
GG_STATIC_ASSERT(offsetof(TagPtrVector, CapacityIncrement) == 0x14);
#endif

#endif  // GG_MATCH_AI_TAG_CLASS_DESTROY_METHODS_H
