// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout and the called vtable slot re-derived numerically from the user's
//   retail gamemd.exe v1.001 with the local Ghidra CLI at 0x478720: [ESI+4]
//   Items, [ESI+8] Capacity, [ESI+0xD] IsAllocated, and `MOV EAX,[ESI];
//   CALL dword ptr [EAX+0xC]` fixing the called virtual at slot 3. The sibling
//   family at 0x4777B0 inlines this same operator into a copy constructor and
//   names its slot-3 target concretely (0x477840, which zeroes Count and frees
//   Items), which is the evidence for calling the slot Clear(). The other six
//   slots keep placeholder names.
//
// Shape: the copy-assignment operator of a vector-of-pointers class. Unless
//   assigning from itself it clears the destination, takes the source
//   capacity, allocates that many pointers and copies them element by element,
//   marking the block as owned; a zero capacity or a failed allocation falls
//   into a shared tail that nulls Items and clears the owned flag. Returns
//   *this. Twelve instantiations, byte-identical to one another including the
//   single `operator new` call displacement, so nothing varies at all.
#ifndef GG_MATCH_CORE_VECTOR_CLASS_ASSIGN_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_CLASS_ASSIGN_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#define GG_VECASSIGN_DECL(TAG)                                            \
class Vec_##TAG                                                           \
{                                                                         \
public:                                                                   \
    virtual ~Vec_##TAG();                                                     \
    virtual bool Slot1(const Vec_##TAG& other) const;                         \
    virtual bool Slot2(int capacity, void** pMem);                        \
    virtual void Clear();                                                 \
    virtual void Slot4();                                                 \
    virtual void Slot5();                                                 \
    virtual void Slot6();                                                 \
    Vec_##TAG& operator=(const Vec_##TAG& other);                         \
    void** Items;                                                         \
    int    Capacity;                                                      \
    bool   IsInitialized;                                                 \
    bool   IsAllocated;                                                   \
}

// The one shared out-of-line body.
#define GG_VECASSIGN_BODY(TAG)                                            \
Vec_##TAG& Vec_##TAG::operator=(const Vec_##TAG& other)                   \
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
        return *this;                                                     \
}

GG_VECASSIGN_DECL(00478720);
GG_STATIC_ASSERT(offsetof(Vec_00478720, Items) == 0x4 &&
                 offsetof(Vec_00478720, Capacity) == 0x8 &&
                 offsetof(Vec_00478720, IsInitialized) == 0xC &&
                 offsetof(Vec_00478720, IsAllocated) == 0xD &&
                 sizeof(Vec_00478720) == 0x10);

GG_VECASSIGN_DECL(004787E0);
GG_STATIC_ASSERT(offsetof(Vec_004787E0, Items) == 0x4 &&
                 offsetof(Vec_004787E0, Capacity) == 0x8 &&
                 offsetof(Vec_004787E0, IsInitialized) == 0xC &&
                 offsetof(Vec_004787E0, IsAllocated) == 0xD &&
                 sizeof(Vec_004787E0) == 0x10);

GG_VECASSIGN_DECL(00512BD0);
GG_STATIC_ASSERT(offsetof(Vec_00512BD0, Items) == 0x4 &&
                 offsetof(Vec_00512BD0, Capacity) == 0x8 &&
                 offsetof(Vec_00512BD0, IsInitialized) == 0xC &&
                 offsetof(Vec_00512BD0, IsAllocated) == 0xD &&
                 sizeof(Vec_00512BD0) == 0x10);

GG_VECASSIGN_DECL(00512FA0);
GG_STATIC_ASSERT(offsetof(Vec_00512FA0, Items) == 0x4 &&
                 offsetof(Vec_00512FA0, Capacity) == 0x8 &&
                 offsetof(Vec_00512FA0, IsInitialized) == 0xC &&
                 offsetof(Vec_00512FA0, IsAllocated) == 0xD &&
                 sizeof(Vec_00512FA0) == 0x10);

GG_VECASSIGN_DECL(00513370);
GG_STATIC_ASSERT(offsetof(Vec_00513370, Items) == 0x4 &&
                 offsetof(Vec_00513370, Capacity) == 0x8 &&
                 offsetof(Vec_00513370, IsInitialized) == 0xC &&
                 offsetof(Vec_00513370, IsAllocated) == 0xD &&
                 sizeof(Vec_00513370) == 0x10);

GG_VECASSIGN_DECL(00525060);
GG_STATIC_ASSERT(offsetof(Vec_00525060, Items) == 0x4 &&
                 offsetof(Vec_00525060, Capacity) == 0x8 &&
                 offsetof(Vec_00525060, IsInitialized) == 0xC &&
                 offsetof(Vec_00525060, IsAllocated) == 0xD &&
                 sizeof(Vec_00525060) == 0x10);

GG_VECASSIGN_DECL(0067AA80);
GG_STATIC_ASSERT(offsetof(Vec_0067AA80, Items) == 0x4 &&
                 offsetof(Vec_0067AA80, Capacity) == 0x8 &&
                 offsetof(Vec_0067AA80, IsInitialized) == 0xC &&
                 offsetof(Vec_0067AA80, IsAllocated) == 0xD &&
                 sizeof(Vec_0067AA80) == 0x10);

GG_VECASSIGN_DECL(0067AE00);
GG_STATIC_ASSERT(offsetof(Vec_0067AE00, Items) == 0x4 &&
                 offsetof(Vec_0067AE00, Capacity) == 0x8 &&
                 offsetof(Vec_0067AE00, IsInitialized) == 0xC &&
                 offsetof(Vec_0067AE00, IsAllocated) == 0xD &&
                 sizeof(Vec_0067AE00) == 0x10);

GG_VECASSIGN_DECL(0067B180);
GG_STATIC_ASSERT(offsetof(Vec_0067B180, Items) == 0x4 &&
                 offsetof(Vec_0067B180, Capacity) == 0x8 &&
                 offsetof(Vec_0067B180, IsInitialized) == 0xC &&
                 offsetof(Vec_0067B180, IsAllocated) == 0xD &&
                 sizeof(Vec_0067B180) == 0x10);

GG_VECASSIGN_DECL(0067BFA0);
GG_STATIC_ASSERT(offsetof(Vec_0067BFA0, Items) == 0x4 &&
                 offsetof(Vec_0067BFA0, Capacity) == 0x8 &&
                 offsetof(Vec_0067BFA0, IsInitialized) == 0xC &&
                 offsetof(Vec_0067BFA0, IsAllocated) == 0xD &&
                 sizeof(Vec_0067BFA0) == 0x10);

GG_VECASSIGN_DECL(006F2780);
GG_STATIC_ASSERT(offsetof(Vec_006F2780, Items) == 0x4 &&
                 offsetof(Vec_006F2780, Capacity) == 0x8 &&
                 offsetof(Vec_006F2780, IsInitialized) == 0xC &&
                 offsetof(Vec_006F2780, IsAllocated) == 0xD &&
                 sizeof(Vec_006F2780) == 0x10);

GG_VECASSIGN_DECL(00717C00);
GG_STATIC_ASSERT(offsetof(Vec_00717C00, Items) == 0x4 &&
                 offsetof(Vec_00717C00, Capacity) == 0x8 &&
                 offsetof(Vec_00717C00, IsInitialized) == 0xC &&
                 offsetof(Vec_00717C00, IsAllocated) == 0xD &&
                 sizeof(Vec_00717C00) == 0x10);

#endif  // GG_MATCH_CORE_VECTOR_CLASS_ASSIGN_FAMILY_METHODS_H
