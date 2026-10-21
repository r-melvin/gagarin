// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and globals read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x4A7900: the two compared members
//   `CMP EDI,[ESI+0x24]` / `CMP EDI,[ESI+0x28]` (Owner / Target), the store
//   `MOV dword ptr [ESI+0x30],-1`, and the DynamicVectorClass at 0xB0F698 seen
//   through the inlined AddItem: `MOV EAX,[0xB0F6A0]` Capacity, `CMP
//   [0xB0F6A8],EAX` Count, `MOV CL,[0xB0F6A5]` IsAllocated, `MOV
//   ECX,[0xB0F6AC]` CapacityIncrement, `MOV EAX,[0xB0F698]; CALL [EAX+8]`
//   SetCapacity, `MOV ECX,[0xB0F69C]` Items. The same vector is already bound
//   as the pending-delete list in match/core/object_class_uninit_methods.h
//   and match/ai/tag_class_destroy_methods.h. Names for the method and the
//   members (DiskLaserClass::PointerGotInvalid, Owner, Target, unknown_30)
//   from YRpp DiskLaserClass.h (consult-only; names only).
//
// DiskLaserClass::PointerGotInvalid -- when either end of the laser is the
// object being retired, drop the +0x30 handle and queue the laser itself on
// the pending-delete vector.
#ifndef GG_MATCH_COMBAT_DISK_LASER_POINTER_METHODS_H
#define GG_MATCH_COMBAT_DISK_LASER_POINTER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct DiskLaser_004A7900;

// Call view for shared pending-delete storage at 0xB0F698; owner unconfirmed.
// The grow path issues the virtual SetCapacity through [vptr+0x08]; the
// leading virtuals reproduce that slot. IsAllocated is the byte at +0x0D.
class PendingVector_004A7900
{
public:
    virtual ~PendingVector_004A7900();                                    // +0x00
    virtual bool operator==(const PendingVector_004A7900& other) const;   // +0x04
    virtual bool SetCapacity(int capacity, void** pMem);                  // +0x08

    // DynamicVectorClass::AddItem, expanded inline at both call sites. The
    // same phrasing as match/core/object_class_uninit_methods.h: Capacity
    // bound to a local keeps the new size in ECX ahead of the vtable load.
    bool AddItem(DiskLaser_004A7900* item)
    {
        int cap = this->Capacity;
        if (this->Count >= cap)
        {
            if (!this->IsAllocated && cap != 0)
                return false;
            if (this->CapacityIncrement <= 0)
                return false;
            if (!this->SetCapacity(cap + this->CapacityIncrement, 0))
                return false;
        }
        (*this)[this->Count++] = item;
        return true;
    }

    DiskLaser_004A7900*& operator[](int i) { return this->Items[i]; }

    DiskLaser_004A7900** Items;              // +0x04
    int                  Capacity;           // +0x08
    bool                 IsInitialized;      // +0x0C
    bool                 IsAllocated;        // +0x0D
    int                  Count;              // +0x10
    int                  CapacityIncrement;  // +0x14
};
GG_STATIC_ASSERT(offsetof(PendingVector_004A7900, Items)             == 0x04);
GG_STATIC_ASSERT(offsetof(PendingVector_004A7900, Capacity)          == 0x08);
GG_STATIC_ASSERT(offsetof(PendingVector_004A7900, IsAllocated)       == 0x0D);
GG_STATIC_ASSERT(offsetof(PendingVector_004A7900, Count)             == 0x10);
GG_STATIC_ASSERT(offsetof(PendingVector_004A7900, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(PendingVector_004A7900)                      == 0x18);

// GLOBAL: GAMEMD 0xB0F698 -- the pending-delete DynamicVectorClass.
#include "../core/abstract_registry.h"

struct DiskLaser_004A7900
{
    char  _pad000[0x24];      // +0x0000  AbstractClass base
    void* Owner;              // +0x0024
    void* Target;             // +0x0028
    char  _pad02C[4];         // +0x002C
    int   unknown_30;         // +0x0030  set to -1 when an end goes away

    // FUNCTION: GAMEMD 0x4A7900
    void PointerGotInvalid(void* pInvalid);
};
GG_STATIC_ASSERT(offsetof(DiskLaser_004A7900, Owner)      == 0x24);
GG_STATIC_ASSERT(offsetof(DiskLaser_004A7900, Target)     == 0x28);
GG_STATIC_ASSERT(offsetof(DiskLaser_004A7900, unknown_30) == 0x30);

#endif  // GG_MATCH_COMBAT_DISK_LASER_POINTER_METHODS_H
