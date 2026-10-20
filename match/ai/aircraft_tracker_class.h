// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4137A0 / 0x413800), cross-checked
//   against YRpp AircraftTrackerClass.h / ArrayClasses.h (consult-only;
//   reconfirmed numerically here).
//
// AircraftTrackerClass — tracks aerial units in a 20x20 grid of
// DynamicVectorClass<TechnoClass*> buckets (TrackerVectors), plus a scratch
// CurrentVector populated by FillCurrentVector and drained by Get.
#ifndef GG_MATCH_AI_AIRCRAFT_TRACKER_CLASS_H
#define GG_MATCH_AI_AIRCRAFT_TRACKER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellStruct_004134A0 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(CellStruct_004134A0) == 4);

// GLOBAL: GAMEMD 0x87F914 / 0x87F918 — map width / height in cells.
extern int DAT_0087F914;
extern int DAT_0087F918;
// GLOBAL: GAMEMD 0x887850 — the "no cell" coordinate handed back on Remove.
extern CellStruct_004134A0 DAT_00887850;

struct TrackVtbl;
// The tracked object; only three vtable slots are used: +0x1B8 and +0x2F4
// (a CellStruct through an out pointer) and +0x2F8 (a CellStruct by value).
class TechnoClass
{
public:
    TrackVtbl* Vptr;   // +0x00
};
typedef CellStruct_004134A0* (TechnoClass::*FnCell_004134A0)(CellStruct_004134A0* out);
typedef void (TechnoClass::*FnSetCell_004134A0)(CellStruct_004134A0 cell);
struct TrackVtbl
{
    char _pad000[0x1B8];                 // +0x0000
    FnCell_004134A0 GetMapCoords;        // +0x01B8
    char _pad1BC[0x2F4 - 0x1BC];         // +0x01BC
    FnCell_004134A0 GetTrackedCoords;    // +0x02F4
    FnSetCell_004134A0 SetTrackedCoords; // +0x02F8
};
GG_STATIC_ASSERT(offsetof(TrackVtbl, GetMapCoords) == 0x1B8);
GG_STATIC_ASSERT(offsetof(TrackVtbl, GetTrackedCoords) == 0x2F4);
GG_STATIC_ASSERT(offsetof(TrackVtbl, SetTrackedCoords) == 0x2F8);

// DynamicVectorClass<TechnoClass*> — 0x18 bytes. Only the members and vtable
// slots the matched methods touch are modelled; the vtable order is confirmed
// from the indexed virtual calls in Clear()/Get():
//   [vptr+0x08] SetCapacity (slot 2), [vptr+0x0c] Clear (slot 3),
//   [vptr+0x10] FindItemIndex (slot 4).
// Slots 0 (~dtor) and 1 (operator==) are declared only to pin the layout.
struct DynVec
{
    virtual ~DynVec();                                         // slot 0  [+0x00]
    virtual int  operator==(const DynVec& other) const;       // slot 1  [+0x04]
    virtual bool SetCapacity(int capacity, void* pMem);       // slot 2  [+0x08]
    virtual void Clear();                                      // slot 3  [+0x0c]
    virtual int  FindItemIndex(TechnoClass* const& item) const; // slot 4 [+0x10]

    TechnoClass** Items;             // +0x04
    int           Capacity;          // +0x08
    unsigned char IsInitialized;     // +0x0c
    unsigned char IsAllocated;       // +0x0d
    int           Count;             // +0x10
    int           CapacityIncrement; // +0x14

    // DynamicVectorClass::AddItem, expanded inline at 0x4134A0: the index is
    // `index = Count; Count = index + 1;` (LEA form) and the grown size is
    // `CapacityIncrement + cap` with the capacity bound to a local.
    bool AddItem(TechnoClass* item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && SetCapacity(CapacityIncrement + cap, 0))) {
            int index = Count;
            Count = index + 1;
            Items[index] = item;
            return true;
        }
        return false;
    }
    // DynamicVectorClass::RemoveItem, expanded inline at 0x4135D0.
    bool RemoveItem(TechnoClass* const& item)
    {
        int index = FindItemIndex(item);
        if (index != -1 && index < Count) {
            Count = Count - 1;
            for (; index < Count; ++index)
                Items[index] = Items[index + 1];
            return true;
        }
        return false;
    }
};

GG_STATIC_ASSERT(offsetof(DynVec, Items)    == 0x04);
GG_STATIC_ASSERT(offsetof(DynVec, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(DynVec, Count)    == 0x10);
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(sizeof(DynVec) == 0x18);
#endif

class AircraftTrackerClass
{
public:
    void         Add(TechnoClass* techno);    // GAMEMD 0x4134A0 __thiscall
    void         Remove(TechnoClass* techno); // GAMEMD 0x4135D0 __thiscall
    TechnoClass* Get();   // GAMEMD 0x4137A0 __thiscall
    void         Clear(); // GAMEMD 0x413800 __thiscall

    DynVec TrackerVectors[20][20]; // +0x0000  (400 * 0x18 == 0x2580)
    DynVec CurrentVector;          // +0x2580
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(AircraftTrackerClass, CurrentVector) == 0x2580);
GG_STATIC_ASSERT(sizeof(AircraftTrackerClass) == 0x2598);
#endif

#endif // GG_MATCH_AI_AIRCRAFT_TRACKER_CLASS_H
