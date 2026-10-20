// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Layout and vtable constants re-derived numerically from the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI. The member displacements come
//   straight off 0x512960's own instructions: `MOV [EAX+4],ECX` Items,
//   `MOV [EAX+8],ECX` Capacity, `MOV byte ptr [EAX+0xC],1` IsInitialized,
//   `MOV [EAX+0xD],CL` IsAllocated, `MOV dword ptr [EAX+0x14],0xA`
//   CapacityIncrement and `MOV [EAX+0x10],ECX` Count; the single
//   `MOV dword ptr [EAX],imm32` gives the leaf vtable. The same base/derived
//   layout is already pinned by the copy-constructor family in
//   dynamic_vector_copy_ctor_family_methods.h, which shares these vtables.
//
// Shape: the default constructor of a leaf class derived from a growable
//   vector of pointers (a DynamicVectorClass-shaped middle class over a
//   VectorClass-shaped base). Nine instantiations differ only in the leaf
//   vtable address; every other byte is identical.
//
// Phrasing note (the lever): retail stores CapacityIncrement (+0x14) BEFORE
//   Count (+0x10) and seats a single vtable last. Neither order is reachable
//   from a two-level hierarchy: a member-initializer list is normalised to
//   declaration order (0x10 then 0x14, 80.0%) and body assignments sink below
//   the vptr seat (70.0%). The retail order falls out of a THREE-level
//   hierarchy — the middle class's constructor assigns CapacityIncrement then
//   Count in its body, and the leaf constructor is empty. cl inlines the
//   middle constructor, its vptr seat becomes a dead store killed by the leaf
//   seat, and what survives is exactly retail's base inits, the two body
//   assignments in source order, and one trailing vptr store. 100% first try.
#ifndef GG_MATCH_CORE_DYNAMIC_VECTOR_DEFAULT_CTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_DYNAMIC_VECTOR_DEFAULT_CTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The vector-of-pointers base: four members at +4/+8/+0xC/+0xD and a
// seven-slot vtable. Its own vptr store is dead in every member of this
// family, so the base vtable address never reaches the code and one shared
// declaration serves all nine instantiations.
class GgVecBase
{
public:
    GgVecBase() : Items(0), Capacity(0), IsInitialized(true), IsAllocated(false) {}
    virtual ~GgVecBase();
    virtual bool Slot1(const GgVecBase& other) const;
    virtual bool Slot2(int capacity, void** pMem);
    virtual void Clear();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    void** Items;
    int    Capacity;
    bool   IsInitialized;
    bool   IsAllocated;
};

GG_STATIC_ASSERT(offsetof(GgVecBase, Items) == 0x4 &&
                 offsetof(GgVecBase, Capacity) == 0x8 &&
                 offsetof(GgVecBase, IsInitialized) == 0xC &&
                 offsetof(GgVecBase, IsAllocated) == 0xD &&
                 sizeof(GgVecBase) == 0x10);

// The growable middle class: Count at +0x10, CapacityIncrement at +0x14, and
// the constructor body that supplies retail's store order. Inlined into every
// leaf constructor below; its own vptr store is always dead.
class GgDynVec : public GgVecBase
{
public:
    GgDynVec() { CapacityIncrement = 10; Count = 0; }
    virtual ~GgDynVec();
    virtual bool Slot2(int capacity, void** pMem);
    virtual void Clear();
    virtual void Slot4();
    virtual void Slot5();
    int Count;
    int CapacityIncrement;
};

GG_STATIC_ASSERT(offsetof(GgDynVec, Count) == 0x10 &&
                 offsetof(GgDynVec, CapacityIncrement) == 0x14 &&
                 sizeof(GgDynVec) == 0x18);

// One leaf class per retail vtable. The leaf adds no members: it exists only
// to carry its own vtable, which is the single byte-level difference between
// the nine instantiations.
#define GG_DYNVEC_LEAF_DECL(TAG)                                          \
class DynVecLeaf_##TAG : public GgDynVec                                  \
{                                                                         \
public:                                                                   \
    DynVecLeaf_##TAG();                                                   \
    virtual ~DynVecLeaf_##TAG();                                          \
    virtual bool Slot2(int capacity, void** pMem);                        \
    virtual void Clear();                                                 \
    virtual void Slot4();                                                 \
    virtual void Slot5();                                                 \
}

// The whole family body: the leaf constructor is empty and every retail
// instruction comes from the inlined middle constructor.
#define GG_DYNVEC_DEFAULT_CTOR_BODY(TAG)                                  \
    DynVecLeaf_##TAG::DynVecLeaf_##TAG() {}

// VTABLE: GAMEMD 0x007E4DD8
GG_DYNVEC_LEAF_DECL(007E4DD8);
GG_STATIC_ASSERT(sizeof(DynVecLeaf_007E4DD8) == 0x18);

// VTABLE: GAMEMD 0x007EABC8
GG_DYNVEC_LEAF_DECL(007EABC8);
GG_STATIC_ASSERT(sizeof(DynVecLeaf_007EABC8) == 0x18);

// VTABLE: GAMEMD 0x007EAC08
GG_DYNVEC_LEAF_DECL(007EAC08);
GG_STATIC_ASSERT(sizeof(DynVecLeaf_007EAC08) == 0x18);

// VTABLE: GAMEMD 0x007EB6D4
GG_DYNVEC_LEAF_DECL(007EB6D4);
GG_STATIC_ASSERT(sizeof(DynVecLeaf_007EB6D4) == 0x18);

// VTABLE: GAMEMD 0x007ED90C
GG_DYNVEC_LEAF_DECL(007ED90C);
GG_STATIC_ASSERT(sizeof(DynVecLeaf_007ED90C) == 0x18);

// VTABLE: GAMEMD 0x007F0CFC
GG_DYNVEC_LEAF_DECL(007F0CFC);
GG_STATIC_ASSERT(sizeof(DynVecLeaf_007F0CFC) == 0x18);

// VTABLE: GAMEMD 0x007F0D1C
GG_DYNVEC_LEAF_DECL(007F0D1C);
GG_STATIC_ASSERT(sizeof(DynVecLeaf_007F0D1C) == 0x18);

// VTABLE: GAMEMD 0x007F0D3C
GG_DYNVEC_LEAF_DECL(007F0D3C);
GG_STATIC_ASSERT(sizeof(DynVecLeaf_007F0D3C) == 0x18);

// VTABLE: GAMEMD 0x007F4F9C
GG_DYNVEC_LEAF_DECL(007F4F9C);
GG_STATIC_ASSERT(sizeof(DynVecLeaf_007F4F9C) == 0x18);

// Address -> class map for the nine instantiations. A constructor cannot be
// redeclared at namespace scope, so the reccmp `// FUNCTION:` annotations live
// on the bodies in the .cpp; this is the index.
//   0x00512960  ->  DynVecLeaf_007EABC8
//   0x005AC400  ->  DynVecLeaf_007ED90C
//   0x0067A390  ->  DynVecLeaf_007F0D3C
//   0x0067A470  ->  DynVecLeaf_007EB6D4
//   0x0067A4F0  ->  DynVecLeaf_007E4DD8
//   0x0067A600  ->  DynVecLeaf_007F0D1C
//   0x0067A820  ->  DynVecLeaf_007EAC08
//   0x0067A8B0  ->  DynVecLeaf_007F0CFC
//   0x00717AF0  ->  DynVecLeaf_007F4F9C

#endif  // GG_MATCH_CORE_DYNAMIC_VECTOR_DEFAULT_CTOR_FAMILY_METHODS_H
