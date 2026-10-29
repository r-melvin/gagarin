// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x439080-0x439150), cross-checked
//   against YRpp and reconfirmed numerically.
//
// BombListClass: the bomb vector (DynamicVectorClass<BombClass*>) is the
// object's own prefix at +0x00 (sizeof 0x18), followed by the detector vector
// (DynamicVectorClass<TechnoClass*>) at +0x18 and UpdateDelay at +0x30.
// Methods: AddDetector 0x439080, RemoveDetector 0x4390D0, PointerGotInvalid
// 0x439150. FindItemIndex of the bomb vector is virtual slot 4 (+0x10).
#ifndef GG_MATCH_LAYOUT_BOMB_LIST_CLASS_H
#define GG_MATCH_LAYOUT_BOMB_LIST_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "bomb_class.h"

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

// FindItemIndex takes its argument by reference: retail hands it the
// address of a stack temporary (`LEA ECX,[ESP+8]; PUSH ECX`).
// DynamicVectorClass<BombClass*> -- vptr at +0x00, then the standard vector fields.
struct BombVectorClass
{
    virtual void v00() = 0;
    virtual void v04() = 0;
    virtual void v08() = 0;
    virtual void v0C() = 0;
    virtual int  FindItemIndex(BombClass* const& item);   // +0x10 (declared; reloc)

    BombClass** Items;         // +0x04
    int         Capacity;      // +0x08
    int         IsAllocated;   // +0x0C
    int         Count;         // +0x10
    int         CapacityIncrement;   // +0x14
};
GG_STATIC_ASSERT(offsetof(BombVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(BombVectorClass, Count) == 0x10);

GG_STATIC_ASSERT(offsetof(BombVectorClass, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(BombVectorClass) == 0x18);

struct BombListClass : BombVectorClass
{
    void AddDetector(TechnoClass* Detector);          // GAMEMD 0x439080 __thiscall
    void RemoveDetector(TechnoClass* Detector);       // GAMEMD 0x4390D0 __thiscall
    void PointerGotInvalid(AbstractClass* invalid);   // GAMEMD 0x439150

    DetectorVectorClass Detectors;   // +0x18
    int                 UpdateDelay; // +0x30
};

GG_STATIC_ASSERT(offsetof(BombListClass, Detectors)   == 0x18);
GG_STATIC_ASSERT(offsetof(BombListClass, UpdateDelay) == 0x30);

#endif  // GG_MATCH_LAYOUT_BOMB_LIST_CLASS_H
