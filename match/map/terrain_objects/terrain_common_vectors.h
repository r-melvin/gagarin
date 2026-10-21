// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The seven-slot VectorClass / DynamicVectorClass shape every pointer array of the terrain-objects
//   module uses (OverlayClass::Array 0xA8EC50, OverlayTypeClass::Array 0xA83D80, SmudgeClass::Array
//   0xA8B1E0, SmudgeTypeClass::Array 0xA8EC18, TerrainTypeClass::Array 0xA8E318, TerrainClass::Array
//   0xA8E988). Layout and slot order match match/core/vector_class.h, which this module does not
//   include. Virtual slots are declared (no bodies here) so the inlined AddItem / RemoveItem reach
//   SetCapacity (slot 2, [vptr+8]) and FindItemIndex (slot 4, [vptr+0x10]) through the same vtable slots
//   as retail.
//
// MapObjVector<T> is the common base; MapObjDynVector<T> adds Count / CapacityIncrement (+0x10 / +0x14,
// sizeof 0x18) and the inlined members. The retail compiler expanded AddItem (and the index lookup)
// in several different shapes in different bodies, and VC6 compiles each source shape to different
// instructions (register choice and load order of Count / Capacity), so the shapes are NOT
// interchangeable. They are kept as distinctly named members, one per proven shape:
//   AddItem             one short-circuit condition, Capacity loaded into a local first (Overlay /
//                       Smudge / Terrain object constructors, Smudge type constructor). The Terrain
//                       object constructors' variant that stores through an index local compiles to
//                       the same bytes, so they use this member too.
//   AddItemEarlyOut     early returns, Count compared with Capacity before the local is read, element
//                       stored through an index local (OverlayTypeClass constructor)
//   AddItemSlotEarlyOut early returns, element address formed first (`T* slot = &Items[Count++]`;
//                       TerrainTypeClass constructor)
// The two early-out shapes were tried against each other's constructors and both regress, so they stay
// separate. FindIndex (a plain loop with a single `return -1` exit) serves every family; the variant
// that leaves the loop through a label compiles to the same bytes.
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_VECTORS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_VECTORS_H

#include "terrain_common_types.h"

// VectorClass<T> layout: vptr, Items, Capacity, IsInitialized, IsAllocated.
template <class T> class MapObjVector
{
public:
    virtual ~MapObjVector();
    virtual bool operator==(const MapObjVector<T>& other) const;               // 1
    virtual bool SetCapacity(int capacity, T* mem);                            // 2
    virtual void Clear();                                                      // 3
    virtual int FindItemIndex(const T& item) const;                            // 4
    virtual int Slot5(T* element) const;                                       // 5
    virtual T Slot6(int index) const;                                          // 6
    T& operator[](int index) { return Items[index]; }

    T*            Items;           // +0x04
    int           Capacity;        // +0x08
    bool          IsInitialized;   // +0x0C
    bool          IsAllocated;     // +0x0D
    unsigned char unknown_0E[2];   // +0x0E
};

template <class T> class MapObjDynVector : public MapObjVector<T>
{
public:
    // DynamicVectorClass::AddItem, inlined by the original.
    bool AddItem(const T& item)
    {
        int cap = this->Capacity;
        if (Count < cap
            || ((this->IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && this->SetCapacity(CapacityIncrement + cap, 0))) {
            (*this)[Count++] = item;
            return true;
        }
        return false;
    }

    // The same operation in the shape the OverlayTypeClass constructor's expansion has: early returns,
    // Count loaded before Capacity.
    bool AddItemEarlyOut(const T& item)
    {
        if (Count >= this->Capacity) {
            int cap = this->Capacity;
            if (!this->IsAllocated && cap != 0)
                return false;
            if (CapacityIncrement <= 0)
                return false;
            if (!this->SetCapacity(CapacityIncrement + cap, 0))
                return false;
        }
        int index = Count++;
        this->Items[index] = item;
        return true;
    }

    // The TerrainTypeClass constructor's shape: early returns, the element address formed first.
    bool AddItemSlotEarlyOut(const T& item)
    {
        if (Count >= this->Capacity) {
            if (!this->IsAllocated && this->Capacity != 0)
                return false;
            if (CapacityIncrement <= 0)
                return false;
            if (!this->SetCapacity(CapacityIncrement + this->Capacity, 0))
                return false;
        }
        T* slot = &this->Items[Count++];
        *slot = item;
        return true;
    }

    // DynamicVectorClass::RemoveItem, inlined by the original.
    bool RemoveItem(const T& item)
    {
        int index = this->FindItemIndex(item);
        if (index != -1 && index < Count) {
            Count = Count - 1;
            for (; index < Count; ++index) {
                this->Items[index] = this->Items[index + 1];
            }
            return true;
        }
        return false;
    }

    // The non-virtual lookup retail expands inline where it names the class explicitly.
    int FindIndex(const T& item) const
    {
        int i;
        for (i = 0; i < Count; ++i) {
            if (this->Items[i] == item)
                return i;
        }
        return -1;
    }

    int Count;               // +0x10
    int CapacityIncrement;   // +0x14
};
GG_STATIC_ASSERT(sizeof(MapObjVector<OverlayClass*>) == 0x10);
GG_STATIC_ASSERT(sizeof(MapObjDynVector<OverlayClass*>) == 0x18);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_VECTORS_H
