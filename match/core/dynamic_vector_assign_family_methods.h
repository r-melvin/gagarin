// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x67A090 and its five siblings, a contiguous 0x80-strided
//   run. Offsets come straight off the instructions: Items at `[ESI+4]`,
//   Capacity at `[ESI+8]`, the owned flag at `[ESI+0xD]`, and the three
//   derived members copied wholesale at `[EDI+0x10]`, `[EDI+0x14]` and
//   `[EDI+0x18]`, which fixes the class size at 0x1C. The cleared slot is
//   `MOV EAX,[ESI]; CALL dword ptr [EAX+0xC]`, slot 3 — the same Clear() the
//   already-matched sibling families at 0x478720 (the base assignment
//   operator) and 0x4777B0 (the base copy constructor) name, and the element
//   block is `operator new[]` of Capacity pointers, so the element type is a
//   pointer.
//
// Shape: the copy-assignment operator of the derived growable vector, i.e.
//   the base vector-of-pointers assignment (clear, take the source capacity,
//   allocate and copy, with a zero capacity falling into the Items=0 /
//   not-owned tail) expanded inline, followed unconditionally by the three
//   derived members. The three copies sit OUTSIDE the self-assignment guard —
//   retail's `JZ` at the top jumps straight to them, which is exactly what
//   inlining a base `operator=` that carries its own `this != &other` test
//   produces. Returns *this. Six instantiations, identical apart from the one
//   `operator new` call displacement.
//
//   These entry points carry no name in the binary or in the YRpp map and keep
//   their placeholder names.
#ifndef GG_MATCH_CORE_DYNAMIC_VECTOR_ASSIGN_FAMILY_METHODS_H
#define GG_MATCH_CORE_DYNAMIC_VECTOR_ASSIGN_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One instantiation: the seven-slot vector-of-pointers head, the four base
// members at +4/+8/+0xC/+0xD, and the three derived members at +0x10/+0x14/
// +0x18.
#define GG_DYNVEC_ASSIGN_DECL(TAG)                                        \
class DynVecA_##TAG                                                       \
{                                                                         \
public:                                                                   \
    virtual ~DynVecA_##TAG();                                             \
    virtual bool Slot1(const DynVecA_##TAG& other) const;                 \
    virtual bool Slot2(int capacity, void** pMem);                        \
    virtual void Clear();                                                 \
    virtual void Slot4();                                                 \
    virtual void Slot5();                                                 \
    virtual void Slot6();                                                 \
    DynVecA_##TAG& operator=(const DynVecA_##TAG& other);                 \
    void** Items;              /* +0x0004 */                              \
    int    Capacity;           /* +0x0008 */                              \
    bool   IsInitialized;      /* +0x000C */                              \
    bool   IsAllocated;        /* +0x000D */                              \
    int    Count;              /* +0x0010 */                              \
    int    CapacityIncrement;  /* +0x0014 */                              \
    int    Member18;           /* +0x0018 */                              \
}

// The one shared out-of-line body.
#define GG_DYNVEC_ASSIGN_BODY(TAG)                                        \
DynVecA_##TAG& DynVecA_##TAG::operator=(const DynVecA_##TAG& other)       \
{                                                                         \
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
        this->Count = other.Count;                                        \
        this->CapacityIncrement = other.CapacityIncrement;                \
        this->Member18 = other.Member18;                                  \
        return *this;                                                     \
}

#define GG_DYNVEC_ASSIGN_ASSERTS(TAG)                                     \
GG_STATIC_ASSERT(offsetof(DynVecA_##TAG, Items) == 0x4 &&                 \
                 offsetof(DynVecA_##TAG, Capacity) == 0x8 &&              \
                 offsetof(DynVecA_##TAG, IsInitialized) == 0xC &&         \
                 offsetof(DynVecA_##TAG, IsAllocated) == 0xD &&           \
                 offsetof(DynVecA_##TAG, Count) == 0x10 &&                \
                 offsetof(DynVecA_##TAG, CapacityIncrement) == 0x14 &&    \
                 offsetof(DynVecA_##TAG, Member18) == 0x18 &&             \
                 sizeof(DynVecA_##TAG) == 0x1C)

GG_DYNVEC_ASSIGN_DECL(0067A090);
GG_DYNVEC_ASSIGN_ASSERTS(0067A090);
GG_DYNVEC_ASSIGN_DECL(0067A110);
GG_DYNVEC_ASSIGN_ASSERTS(0067A110);
GG_DYNVEC_ASSIGN_DECL(0067A190);
GG_DYNVEC_ASSIGN_ASSERTS(0067A190);
GG_DYNVEC_ASSIGN_DECL(0067A210);
GG_DYNVEC_ASSIGN_ASSERTS(0067A210);
GG_DYNVEC_ASSIGN_DECL(0067A290);
GG_DYNVEC_ASSIGN_ASSERTS(0067A290);
GG_DYNVEC_ASSIGN_DECL(0067A310);
GG_DYNVEC_ASSIGN_ASSERTS(0067A310);

#endif  // GG_MATCH_CORE_DYNAMIC_VECTOR_ASSIGN_FAMILY_METHODS_H
