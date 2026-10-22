// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5F65F0: AttachedBomb `MOV ECX,[ESI+0x38]`, the techno
//   test `TEST byte ptr [ESI+0x14],1` (AbstractFlags), IsAlive
//   `MOV byte ptr [ESI+0x90],0`, the virtual `CALL [EAX+0xD4]` (slot 53), and the
//   DynamicVectorClass at 0xB0F698 (`MOV EAX,[0xB0F6A0]` Capacity,
//   `CMP [0xB0F6A8],EAX` Count, `MOV CL,[0xB0F6A5]` IsAllocated,
//   `MOV ECX,[0xB0F6AC]` CapacityIncrement, `MOV ECX,[0xB0F69C]` Items,
//   `CALL [EDX+8]` SetCapacity). Names for the method and the three callees —
//   BombClass::Disarm 0x4389B0, TechnoClass::KillPassengers 0x707CB0,
//   AbstractClass::AnnounceExpiredPointer 0x7258D0 — from YRpp.
//
// ObjectClass slot 62 (UnInit) — retire an object: disarm any attached bomb, kill the
// passengers if this is a TechnoClass, announce the expiring pointer, limbo,
// clear IsAlive, and push the object onto the pending-delete vector.
#ifndef GG_MATCH_CORE_OBJECT_CLASS_UNINIT_METHODS_H
#define GG_MATCH_CORE_OBJECT_CLASS_UNINIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/techno_class.h"   // TechnoClass : ... : ObjectClass

GG_STATIC_ASSERT(offsetof(AbstractClass, Flags) == 0x14);
GG_STATIC_ASSERT(offsetof(ObjectClass,   AttachedBomb)  == 0x38);
GG_STATIC_ASSERT(offsetof(ObjectClass,   IsAlive)       == 0x90);

// BombClass — only Disarm() is called; no members are read.
struct UnInitBomb
{
    // FUNCTION: GAMEMD 0x4389B0 (decl; reloc) — BombClass::Disarm, __thiscall.
    void Disarm();
};

// Call view for shared pending-delete storage at 0xB0F698. The
// retail vtable order is confirmed by the inlined AddItem's growth call going
// through [vtbl+0x08] (SetCapacity). IsAllocated is the byte at +0x0D
// (`MOV CL,[0xB0F6A5]`), so +0x0C/+0x0D are two separate bools.
class UnInitVector
{
public:
    virtual ~UnInitVector();                                   // [vtbl+0x00]
    virtual bool operator==(const UnInitVector& other) const;  // [vtbl+0x04]
    virtual bool SetCapacity(int capacity, ObjectClass** pMem); // [vtbl+0x08]

    // Capacity is read once into a local: re-reading the member at each use
    // makes VC6 sum into EAX (`ADD EAX,ECX; PUSH EAX`) where retail sums into
    // ECX (`ADD ECX,EAX; PUSH ECX`). The local is what keeps EAX pinned.
    bool AddItem(ObjectClass* item)
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

    // The element access goes through operator[] so the post-increment (with
    // its Count store) is complete before Items is read, as in retail.
    ObjectClass*& operator[](int i) { return this->Items[i]; }

    ObjectClass** Items;              // +0x04
    int           Capacity;           // +0x08
    bool          IsInitialized;      // +0x0C
    bool          IsAllocated;        // +0x0D
    int           Count;              // +0x10
    int           CapacityIncrement;  // +0x14
};
GG_STATIC_ASSERT(offsetof(UnInitVector, Items)             == 0x04);
GG_STATIC_ASSERT(offsetof(UnInitVector, Capacity)          == 0x08);
GG_STATIC_ASSERT(offsetof(UnInitVector, IsAllocated)       == 0x0D);
GG_STATIC_ASSERT(offsetof(UnInitVector, Count)             == 0x10);
GG_STATIC_ASSERT(offsetof(UnInitVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(UnInitVector)                      == 0x18);

// Shared storage declaration; the call view does not establish its owner.
#include "abstract_registry.h"

#endif  // GG_MATCH_CORE_OBJECT_CLASS_UNINIT_METHODS_H
