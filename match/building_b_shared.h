// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Hand-written helper views shared by the "building-b" sources: coordinates, the pointer-vector family,
//   the global pointer index and the pointer-swizzle manager every Load touches. All layouts were read from the
//   retail bodies of this cluster (Load 0x453E20 shows the index, swizzle and vector accesses; the vector shape
//   is the same inline AddItem the other modules' bodies show: vptr, Items +4, Capacity +8, IsInitialized +0xC,
//   IsAllocated +0xD, Count +0x10, CapacityIncrement +0x14, sizeof 0x18, SetCapacity at slot 2).
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_B_SHARED_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_B_SHARED_H

#include <stddef.h>
#include <objidl.h>   // IStream, HRESULT (VC98 SDK, LIBRARY)
#include "_rt/gg_static_assert.h"
#include "abstract_index_cast_sweep.h"
#include "house_building_views.h"
#include "house_building_com_bases.h"
#include "house_building_views.h"
#include "house_building_com_bases.h"
#include "house_building_views.h"
#include "house_building_com_bases.h"

inline HBCoord operator+(const HBCoord& a, const HBCoord& b)
{
    HBCoord r;
    r.X = a.X + b.X;
    r.Y = a.Y + b.Y;
    r.Z = a.Z + b.Z;
    return r;
}

// The object's canonical coordinate plus a view-typed offset.
inline HBCoord operator+(const CoordStruct& a, const HBCoord& b)
{
    HBCoord r;
    r.X = a.X + b.X;
    r.Y = a.Y + b.Y;
    r.Z = a.Z + b.Z;
    return r;
}

inline HBCoord operator-(const HBCoord& a, const HBCoord& b)
{
    HBCoord r;
    r.X = a.X - b.X;
    r.Y = a.Y - b.Y;
    r.Z = a.Z - b.Z;
    return r;
}

inline HBPoint2D operator+(const HBPoint2D& a, const HBPoint2D& b)
{
    HBPoint2D r;
    r.X = a.X + b.X;
    r.Y = a.Y + b.Y;
    return r;
}

// The cell sum is HBCell::operator+ (house_building_common_types.h).

inline bool operator==(const HBCell& a, const HBCell& b)
{
    return a.X == b.X && a.Y == b.Y;
}

// The cell containing a world coordinate (leptons / 256, per axis).
inline HBCell BuildingBCellOf(const HBCoord& c)
{
    HBCell r;
    r.X = c.X / 256;
    r.Y = c.Y / 256;
    return r;
}

// The same cell as a canonical CellStruct.
inline CellStruct BuildingBCellStructOf(const HBCoord& c)
{
    CellStruct r;
    r.X = c.X / 256;
    r.Y = c.Y / 256;
    return r;
}

inline CellStruct BuildingBCellStructOf(const CoordStruct& c)
{
    CellStruct r;
    r.X = c.X / 256;
    r.Y = c.Y / 256;
    return r;
}

// A pointer-array of the vector family (DynamicVectorClass<T*>, sizeof 0x18).
template <class T> class BuildingBVector
{
public:
    virtual void unused_slot_0();
    virtual void unused_slot_1();
    virtual bool SetCapacity(int capacity, void* mem);   // 2 (+8)
    virtual void Clear();                                // 3 (+0xC)
    virtual int FindItemIndex(T** item);                 // 4 (+0x10)
    T** Items;                   // +0x04
    int Capacity;                // +0x08
    bool IsInitialized;          // +0x0C
    bool IsAllocated;            // +0x0D
    int Count;                   // +0x10
    int CapacityIncrement;       // +0x14

    // FUNCTION: GAMEMD 0x40BD00 (read-only here) - the base constructor (capacity, preallocated array)
    BuildingBVector(int capacity, T** array);
    ~BuildingBVector()
    {
        if (Items && IsAllocated)
            operator delete(Items);
    }

    // DynamicVectorClass::RemoveItem, expanded inline.
    bool RemoveItem(T* item)
    {
        int index = FindItemIndex(&item);
        if (index != -1 && index < Count) {
            Count = Count - 1;
            for (; index < Count; ++index) {
                Items[index] = Items[index + 1];
            }
            return true;
        }
        return false;
    }

    // DynamicVectorClass::AddItem, expanded inline.
    bool AddItem(T* item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && SetCapacity(CapacityIncrement + cap, 0))) {
            int index = Count++;
            Items[index] = item;
            return true;
        }
        return false;
    }
};


#endif
