// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Layout, vtable addresses and slot index re-derived numerically from the
//   user's retail gamemd.exe v1.001 with the local Ghidra CLI: the member
//   displacements come straight off 0x4777B0's own instructions
//   ([ESI+4] Items, [ESI+8] Capacity, [ESI+0xC]/[ESI+0xD] the two flag bytes,
//   [ESI+0x10] Count, [ESI+0x14] CapacityIncrement), the two vtable constants
//   off its two `MOV dword ptr [ESI],imm32` stores, and the called slot off
//   `CALL dword ptr [vtable+0xC]`. `ghidra memory read 0x7E4DB8 64` shows the
//   base vtable holds seven slots; slot 3 (+0xC) is 0x477D20 for the base and
//   0x477840 for the derived class, and 0x477840 zeroes [ESI+0x10] and frees
//   [ESI+4] when [ESI+0xD] is set, which is what fixes that slot as Clear().
//   The remaining six slots keep placeholder names.
//
// Shape: the copy constructor of a growable four-byte-element array view
//   (DynamicVectorClass-shaped: a VectorClass-shaped base holding
//   Items/Capacity/IsInitialized/IsAllocated plus Count/CapacityIncrement).
//   The base copy constructor and the base assignment operator are both
//   expanded inline, so one body covers the whole family: zero the base
//   members, seat the base vtable, and — unless copying from itself — Clear(),
//   take the source capacity, allocate that many elements, copy them, then
//   copy Count and CapacityIncrement and seat the derived vtable. Eleven remaining
//   layout views differ only in the two vtable addresses.
#ifndef GG_MATCH_CORE_DYNAMIC_VECTOR_COPY_CTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_DYNAMIC_VECTOR_COPY_CTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The base half of the family: a four-byte-element array view with a seven-slot vtable,
// an inline copy constructor that delegates to the inline assignment operator,
// and the four base members at +4/+8/+0xC/+0xD.
#define GG_VECBASE_DECL(TAG)                                              \
class VecBase_##TAG                                                       \
{                                                                         \
public:                                                                   \
    VecBase_##TAG(const VecBase_##TAG& other)                             \
        : Items(0), Capacity(0), IsInitialized(true), IsAllocated(false)  \
    { *this = other; }                                                    \
    virtual ~VecBase_##TAG();                                                     \
    virtual bool Slot1(const VecBase_##TAG& other) const;                         \
    virtual bool Slot2(int capacity, void** pMem);                        \
    virtual void Clear();                                                 \
    virtual void Slot4();                                                 \
    virtual void Slot5();                                                 \
    virtual void Slot6();                                                 \
    VecBase_##TAG& operator=(const VecBase_##TAG& other)                  \
    {                                                                     \
        if (this != &other) {                                             \
            this->Clear();                                                \
            this->Capacity = other.Capacity;                              \
            if (this->Capacity != 0) {                                    \
                this->Items = new void*[this->Capacity];                  \
                if (this->Items != 0) {                                   \
                    this->IsAllocated = true;                             \
                    for (int i = 0; i < this->Capacity; ++i) {            \
                        this->Items[i] = other.Items[i];                  \
                    }                                                     \
                }                                                         \
            } else {                                                      \
                this->Items = 0;                                          \
                this->IsAllocated = false;                                \
            }                                                             \
        }                                                                 \
        return *this;                                                     \
    }                                                                     \
    void** Items;                                                         \
    int    Capacity;                                                      \
    bool   IsInitialized;                                                 \
    bool   IsAllocated;                                                   \
}

// The derived half: adds Count at +0x10 and CapacityIncrement at +0x14 and
// overrides the four middle slots, so it carries its own vtable.
#define GG_DYNVEC_DECL(BASETAG, TAG)                                      \
class DynVec_##TAG : public VecBase_##BASETAG                             \
{                                                                         \
public:                                                                   \
    DynVec_##TAG(const DynVec_##TAG& other);                              \
    virtual ~DynVec_##TAG();                                              \
    virtual bool Slot2(int capacity, void** pMem);                        \
    virtual void Clear();                                                 \
    virtual void Slot4();                                                 \
    virtual void Slot5();                                                 \
    int Count;                                                            \
    int CapacityIncrement;                                                \
}

// VTABLE: GAMEMD 0x007EA9E4
GG_VECBASE_DECL(007EA9E4);
GG_STATIC_ASSERT(offsetof(VecBase_007EA9E4, Items) == 0x4 &&
                 offsetof(VecBase_007EA9E4, Capacity) == 0x8 &&
                 offsetof(VecBase_007EA9E4, IsInitialized) == 0xC &&
                 offsetof(VecBase_007EA9E4, IsAllocated) == 0xD &&
                 sizeof(VecBase_007EA9E4) == 0x10);

// VTABLE: GAMEMD 0x007EAC48
GG_VECBASE_DECL(007EAC48);
GG_STATIC_ASSERT(offsetof(VecBase_007EAC48, Items) == 0x4 &&
                 offsetof(VecBase_007EAC48, Capacity) == 0x8 &&
                 offsetof(VecBase_007EAC48, IsInitialized) == 0xC &&
                 offsetof(VecBase_007EAC48, IsAllocated) == 0xD &&
                 sizeof(VecBase_007EAC48) == 0x10);

// VTABLE: GAMEMD 0x007EAC68
GG_VECBASE_DECL(007EAC68);
GG_STATIC_ASSERT(offsetof(VecBase_007EAC68, Items) == 0x4 &&
                 offsetof(VecBase_007EAC68, Capacity) == 0x8 &&
                 offsetof(VecBase_007EAC68, IsInitialized) == 0xC &&
                 offsetof(VecBase_007EAC68, IsAllocated) == 0xD &&
                 sizeof(VecBase_007EAC68) == 0x10);

// VTABLE: GAMEMD 0x007EAC28
GG_VECBASE_DECL(007EAC28);
GG_STATIC_ASSERT(offsetof(VecBase_007EAC28, Items) == 0x4 &&
                 offsetof(VecBase_007EAC28, Capacity) == 0x8 &&
                 offsetof(VecBase_007EAC28, IsInitialized) == 0xC &&
                 offsetof(VecBase_007EAC28, IsAllocated) == 0xD &&
                 sizeof(VecBase_007EAC28) == 0x10);

// VTABLE: GAMEMD 0x007EB6F4
GG_VECBASE_DECL(007EB6F4);
GG_STATIC_ASSERT(offsetof(VecBase_007EB6F4, Items) == 0x4 &&
                 offsetof(VecBase_007EB6F4, Capacity) == 0x8 &&
                 offsetof(VecBase_007EB6F4, IsInitialized) == 0xC &&
                 offsetof(VecBase_007EB6F4, IsAllocated) == 0xD &&
                 sizeof(VecBase_007EB6F4) == 0x10);

// VTABLE: GAMEMD 0x007EAA08
GG_VECBASE_DECL(007EAA08);
GG_STATIC_ASSERT(offsetof(VecBase_007EAA08, Items) == 0x4 &&
                 offsetof(VecBase_007EAA08, Capacity) == 0x8 &&
                 offsetof(VecBase_007EAA08, IsInitialized) == 0xC &&
                 offsetof(VecBase_007EAA08, IsAllocated) == 0xD &&
                 sizeof(VecBase_007EAA08) == 0x10);

// VTABLE: GAMEMD 0x007EE3D0
GG_VECBASE_DECL(007EE3D0);
GG_STATIC_ASSERT(offsetof(VecBase_007EE3D0, Items) == 0x4 &&
                 offsetof(VecBase_007EE3D0, Capacity) == 0x8 &&
                 offsetof(VecBase_007EE3D0, IsInitialized) == 0xC &&
                 offsetof(VecBase_007EE3D0, IsAllocated) == 0xD &&
                 sizeof(VecBase_007EE3D0) == 0x10);

// VTABLE: GAMEMD 0x007F0D5C
GG_VECBASE_DECL(007F0D5C);
GG_STATIC_ASSERT(offsetof(VecBase_007F0D5C, Items) == 0x4 &&
                 offsetof(VecBase_007F0D5C, Capacity) == 0x8 &&
                 offsetof(VecBase_007F0D5C, IsInitialized) == 0xC &&
                 offsetof(VecBase_007F0D5C, IsAllocated) == 0xD &&
                 sizeof(VecBase_007F0D5C) == 0x10);

// VTABLE: GAMEMD 0x007F0D7C
GG_VECBASE_DECL(007F0D7C);
GG_STATIC_ASSERT(offsetof(VecBase_007F0D7C, Items) == 0x4 &&
                 offsetof(VecBase_007F0D7C, Capacity) == 0x8 &&
                 offsetof(VecBase_007F0D7C, IsInitialized) == 0xC &&
                 offsetof(VecBase_007F0D7C, IsAllocated) == 0xD &&
                 sizeof(VecBase_007F0D7C) == 0x10);

// VTABLE: GAMEMD 0x007E4424
GG_VECBASE_DECL(007E4424);
GG_STATIC_ASSERT(offsetof(VecBase_007E4424, Items) == 0x4 &&
                 offsetof(VecBase_007E4424, Capacity) == 0x8 &&
                 offsetof(VecBase_007E4424, IsInitialized) == 0xC &&
                 offsetof(VecBase_007E4424, IsAllocated) == 0xD &&
                 sizeof(VecBase_007E4424) == 0x10);

// VTABLE: GAMEMD 0x007EAAE8
GG_DYNVEC_DECL(007EA9E4, 007EAAE8);
GG_STATIC_ASSERT(offsetof(DynVec_007EAAE8, Count) == 0x10 &&
                 offsetof(DynVec_007EAAE8, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007EAAE8) == 0x18);

// VTABLE: GAMEMD 0x007EABE8
GG_DYNVEC_DECL(007EAC48, 007EABE8);
GG_STATIC_ASSERT(offsetof(DynVec_007EABE8, Count) == 0x10 &&
                 offsetof(DynVec_007EABE8, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007EABE8) == 0x18);

// VTABLE: GAMEMD 0x007EABC8
GG_DYNVEC_DECL(007EAC68, 007EABC8);
GG_STATIC_ASSERT(offsetof(DynVec_007EABC8, Count) == 0x10 &&
                 offsetof(DynVec_007EABC8, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007EABC8) == 0x18);

// VTABLE: GAMEMD 0x007EAC88
GG_DYNVEC_DECL(007EAC28, 007EAC88);
GG_STATIC_ASSERT(offsetof(DynVec_007EAC88, Count) == 0x10 &&
                 offsetof(DynVec_007EAC88, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007EAC88) == 0x18);

// VTABLE: GAMEMD 0x007EB6D4
GG_DYNVEC_DECL(007EB6F4, 007EB6D4);
GG_STATIC_ASSERT(offsetof(DynVec_007EB6D4, Count) == 0x10 &&
                 offsetof(DynVec_007EB6D4, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007EB6D4) == 0x18);

// VTABLE: GAMEMD 0x007ED90C
GG_DYNVEC_DECL(007EAA08, 007ED90C);
GG_STATIC_ASSERT(offsetof(DynVec_007ED90C, Count) == 0x10 &&
                 offsetof(DynVec_007ED90C, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007ED90C) == 0x18);

// VTABLE: GAMEMD 0x007EE3F0
GG_DYNVEC_DECL(007EE3D0, 007EE3F0);
GG_STATIC_ASSERT(offsetof(DynVec_007EE3F0, Count) == 0x10 &&
                 offsetof(DynVec_007EE3F0, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007EE3F0) == 0x18);

// VTABLE: GAMEMD 0x007F0D3C
GG_DYNVEC_DECL(007F0D5C, 007F0D3C);
GG_STATIC_ASSERT(offsetof(DynVec_007F0D3C, Count) == 0x10 &&
                 offsetof(DynVec_007F0D3C, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007F0D3C) == 0x18);

// VTABLE: GAMEMD 0x007F0D1C
GG_DYNVEC_DECL(007F0D7C, 007F0D1C);
GG_STATIC_ASSERT(offsetof(DynVec_007F0D1C, Count) == 0x10 &&
                 offsetof(DynVec_007F0D1C, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007F0D1C) == 0x18);

// VTABLE: GAMEMD 0x007F4F9C
GG_DYNVEC_DECL(007E4424, 007F4F9C);
GG_STATIC_ASSERT(offsetof(DynVec_007F4F9C, Count) == 0x10 &&
                 offsetof(DynVec_007F4F9C, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007F4F9C) == 0x18);

// VTABLE: GAMEMD 0x007F0DCC
GG_DYNVEC_DECL(007F0D5C, 007F0DCC);
GG_STATIC_ASSERT(offsetof(DynVec_007F0DCC, Count) == 0x10 &&
                 offsetof(DynVec_007F0DCC, CapacityIncrement) == 0x14 &&
                 sizeof(DynVec_007F0DCC) == 0x18);

// One shared copy-constructor body, parameterised by the base and the
// derived vtable tag. The derived members go in the initializer list: that
// is what sinks the derived vtable store below both member copies, where
// retail has it.
#define GG_DYNVEC_COPY_CTOR_BODY(BASETAG, TAG)                            \
DynVec_##TAG::DynVec_##TAG(const DynVec_##TAG& other)                     \
    : VecBase_##BASETAG(other),                                           \
      Count(other.Count),                                                 \
      CapacityIncrement(other.CapacityIncrement)                          \
{ }


// Address -> class map for the thirteen instantiations. A constructor cannot
// be redeclared at namespace scope, so the reccmp `// FUNCTION:` annotations
// live on the bodies in the .cpp; this is the index.
//   0x0050E830  ->  DynVec_007EAAE8
//   0x00513740  ->  DynVec_007EABE8
//   0x005137D0  ->  DynVec_007EABC8
//   0x00513860  ->  DynVec_007EAC88
//   0x005255F0  ->  DynVec_007EB6D4
//   0x005AD660  ->  DynVec_007ED90C
//   0x005C4F30  ->  DynVec_007EE3F0
//   0x0067C1F0  ->  DynVec_007F0D3C
//   0x0067C280  ->  DynVec_007F0D1C
//   0x00717D20  ->  DynVec_007F4F9C
//   0x0075E6B0  ->  DynVec_007F0DCC

#endif  // GG_MATCH_CORE_DYNAMIC_VECTOR_COPY_CTOR_FAMILY_METHODS_H
