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
#include "../../_rt/gg_static_assert.h"
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

// A pointer-array of the vector family (DynamicVectorClass<T*>, sizeof 0x18).
template <class T> class BuildingBVector
{
public:
    virtual void unused_slot_0();
    virtual void unused_slot_1();
    virtual bool SetCapacity(int capacity, void* mem);   // 2 (+8)
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
// GLOBAL: GAMEMD 0xB0C110
extern HBSwizzleView BuildingBSwizzle;

// The pointer index of every ObjectClass (global IndexClass at 0xB0E840).
struct BuildingBIndexNode
{
    int   ID;     // +0x00
    void* Data;   // +0x04
    BuildingBIndexNode() {}
};
GG_STATIC_ASSERT(sizeof(BuildingBIndexNode) == 8);
struct BuildingBIndexView
{
    BuildingBIndexNode* IndexTable;   // +0x00
    int                 IndexCount;   // +0x04
    int                 IndexSize;    // +0x08
    bool                IsSorted;     // +0x0C
    BuildingBIndexNode* Archive;      // +0x10

    // FUNCTION: GAMEMD 0x41C500 (read-only here) - grows the table by `amount` entries.
    bool Grow(int amount);
    // FUNCTION: GAMEMD 0x41C590 (read-only here) - the sorted search; returns the node or 0.
    BuildingBIndexNode* Find(const int* key);

    void RemoveIndex(const int& id)
    {
        BuildingBIndexNode* node = Find(&id);
        if (node) {
            int found = node - IndexTable;
            if (found != -1) {
                for (int i = found + 1; i < IndexCount; i++) {
                    IndexTable[i - 1].ID = IndexTable[i].ID;
                    IndexTable[i - 1].Data = IndexTable[i].Data;
                }
                IndexCount--;
                IndexTable[IndexCount].ID = 0;
                IndexTable[IndexCount].Data = 0;
                Archive = 0;
            }
        }
    }
    void AddIndexOutOfLine(const int& id, void* const& data)
    {
        if (IndexCount + 1 > IndexSize) {
            if (!Grow(IndexSize == 0 ? 10 : IndexSize))
                return;
        }
        IndexTable[IndexCount].ID = id;
        IndexTable[IndexCount].Data = data;
        IndexCount++;
        IsSorted = false;
    }
};
GG_STATIC_ASSERT(sizeof(BuildingBIndexView) == 0x14);
// GLOBAL: GAMEMD 0xB0E840
extern BuildingBIndexView BuildingBAbstractIndex;

#endif
