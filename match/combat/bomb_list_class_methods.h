// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x439080-0x439108), cross-checked
//   against YRpp (reconfirmed
//   numerically here).
//
// BombListClass::AddDetector / RemoveDetector both operate purely on the
// `Detectors` vector (a DynamicVectorClass<TechnoClass*> @ +0x18). The bodies
// inline DynamicVectorClass::AddItem and ::Remove/::RemoveItem respectively,
// each issuing one genuine *virtual* vector call:
//   AddDetector  -> SetCapacity   via [vtable + 0x08]  (slot 2)
//   RemoveDetector -> FindItemIndex via [vtable + 0x10] (slot 4)
// so the modelled vector must carry the exact retail vtable order.
#ifndef GG_MATCH_COMBAT_BOMB_LIST_CLASS_METHODS_H
#define GG_MATCH_COMBAT_BOMB_LIST_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class TechnoClass;

// ---------------------------------------------------------------------------
// DetectorVectorClass  -- concrete model of DynamicVectorClass<TechnoClass*>
//   sizeof = 0x18.  vptr@0x00, Items@0x04, Capacity@0x08, IsInitialized@0x0C,
//   IsAllocated@0x0D, Count@0x10, CapacityIncrement@0x14.
//
// Retail vtable order (confirmed: AddItem calls [vtbl+8]=SetCapacity, Remove
// calls [vtbl+0x10]=FindItemIndex). Mirrors YRpp VectorClass virtual order:
//   0x00 ~VectorClass   0x04 operator==   0x08 SetCapacity   0x0C Clear
//   0x10 FindItemIndex  0x14 GetItemIndex 0x18 GetItem
// The virtuals are declared (no body) so cl emits the indirect vtable calls;
// only the non-virtual AddItem / Remove / RemoveItem are inlined to match.
// ---------------------------------------------------------------------------
class DetectorVectorClass
{
public:
    virtual ~DetectorVectorClass();                                   // [vtbl+0x00]
    virtual bool operator==(const DetectorVectorClass& other) const;  // [vtbl+0x04]
    virtual bool SetCapacity(int capacity, TechnoClass** pMem);       // [vtbl+0x08]
    virtual void Clear();                                             // [vtbl+0x0C]
    virtual int  FindItemIndex(TechnoClass* const& item) const;      // [vtbl+0x10]
    virtual int  GetItemIndex(TechnoClass* const* pItem) const;      // [vtbl+0x14]
    virtual TechnoClass* GetItem(int index) const;                   // [vtbl+0x18]

    bool AddItem(TechnoClass* item)
    {
        if (this->Count >= this->Capacity)
        {
            if (!this->IsAllocated && this->Capacity != 0)
                return false;
            if (this->CapacityIncrement <= 0)
                return false;
            if (!this->SetCapacity(this->Capacity + this->CapacityIncrement, 0))
                return false;
        }
        int index = this->Count;
        this->Count = index + 1;
        this->Items[index] = item;
        return true;
    }

    bool RemoveItem(int index)
    {
        if (index < this->Count)
        {
            --this->Count;
            for (int i = index; i < this->Count; ++i)
                this->Items[i] = this->Items[i + 1];
        }
        return true;
    }

    TechnoClass** Items;          // +0x04
    int           Capacity;       // +0x08
    bool          IsInitialized;  // +0x0C
    bool          IsAllocated;    // +0x0D
    int           Count;          // +0x10
    int           CapacityIncrement;  // +0x14
};

GG_STATIC_ASSERT(offsetof(DetectorVectorClass, Items)             == 0x04);
GG_STATIC_ASSERT(offsetof(DetectorVectorClass, Capacity)          == 0x08);
GG_STATIC_ASSERT(offsetof(DetectorVectorClass, IsInitialized)     == 0x0C);
GG_STATIC_ASSERT(offsetof(DetectorVectorClass, IsAllocated)       == 0x0D);
GG_STATIC_ASSERT(offsetof(DetectorVectorClass, Count)             == 0x10);
GG_STATIC_ASSERT(offsetof(DetectorVectorClass, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(DetectorVectorClass)                      == 0x18);

// ---------------------------------------------------------------------------
// BombListClass  -- only the layout these two methods reach.
//   Bombs (DynamicVectorClass<BombClass*>) @0x00, Detectors @0x18,
//   UpdateDelay @0x30.  Non-polymorphic (Bombs.vptr is at offset 0).
// ---------------------------------------------------------------------------
struct BombListClass
{
    void AddDetector(TechnoClass* Detector);     // GAMEMD 0x439080 __thiscall
    void RemoveDetector(TechnoClass* Detector);  // GAMEMD 0x4390D0 __thiscall

    char               Bombs[0x18];  // +0x00  DynamicVectorClass<BombClass*>
    DetectorVectorClass Detectors;   // +0x18
    int                UpdateDelay;  // +0x30
};

GG_STATIC_ASSERT(offsetof(BombListClass, Detectors)   == 0x18);
GG_STATIC_ASSERT(offsetof(BombListClass, UpdateDelay) == 0x30);

#endif  // GG_MATCH_COMBAT_BOMB_LIST_CLASS_METHODS_H
