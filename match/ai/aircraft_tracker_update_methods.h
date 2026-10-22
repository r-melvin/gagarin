// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets re-derived numerically from the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x4138C0. Convention: `PUSH ECX` (one spill
//   slot), `MOV [ESP],ECX` (this), `MOV EDX,[ESP+0x10]` and `RET 0xC` — a
//   __thiscall taking three dword arguments, read back after the five pushes
//   as `[ESP+0x18]` (the techno), `[ESP+0x1C]/[ESP+0x1E]` (the old cell's X
//   and Y words) and `[ESP+0x20]/[ESP+0x22]` (the new cell's). Vtable slot
//   `CALL [EAX+0x2F8]` is SetTrackedCoords (CellStruct by value). The grid
//   divisors come from `MOV ECX,[0x87F914]` / `[0x87F918]` each divided by
//   twenty (the 0x66666667 IMUL/SAR 3 fold) and are CSE'd across both cells.
//   On the bucket vector: `MOV EDX,[EBX+ECX*8]` (vptr), `CALL [EDX+0x10]`
//   (FindItemIndex), `[ESI+0x4]` Items, `[ESI+0x8]` Capacity, `[ESI+0xD]`
//   IsAllocated, `[ESI+0x10]` Count, `[ESI+0x14]` CapacityIncrement and
//   `CALL [EDX+0x8]` (SetCapacity); the `LEA reg,[b+b*2]` + `*8` scaling
//   pins the element stride at 0x18. Layout identical to the one already
//   confirmed in match/ai/aircraft_tracker_class.h (Add/Remove at 100%),
//   restated here under local names so this TU compiles standalone and adds
//   no member to that header. Names cross-checked against YRpp
//   AircraftTrackerClass.
#ifndef GG_MATCH_AI_AIRCRAFT_TRACKER_UPDATE_METHODS_H
#define GG_MATCH_AI_AIRCRAFT_TRACKER_UPDATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct CellStruct_004138C0 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(CellStruct_004138C0) == 4);

// GLOBAL: GAMEMD 0x87F914 / 0x87F918 — map width / height in cells.
extern int DAT_0087F914;
extern int DAT_0087F918;

struct TrackVtbl_004138C0;

class Techno_004138C0
{
public:
    TrackVtbl_004138C0* Vptr;   // +0x00
};
typedef void (Techno_004138C0::*FnSetCell_004138C0)(CellStruct_004138C0 cell);

struct TrackVtbl_004138C0
{
    char _pad000[0x2F8];                        // +0x0000
    FnSetCell_004138C0 SetTrackedCoords;        // +0x02F8
};
GG_STATIC_ASSERT(offsetof(TrackVtbl_004138C0, SetTrackedCoords) == 0x2F8);

// DynamicVectorClass<TechnoClass*> — 0x18 bytes; slot 2 SetCapacity,
// slot 4 FindItemIndex. Slots 0/1/3 are declared only to pin the layout.
struct DynVec_004138C0
{
    virtual ~DynVec_004138C0();
    virtual int  operator==(const DynVec_004138C0& other) const;
    virtual bool SetCapacity(int capacity, void* pMem);
    virtual void Clear();
    virtual int  FindItemIndex(Techno_004138C0* const& item) const;

    Techno_004138C0** Items;             // +0x04
    int               Capacity;          // +0x08
    unsigned char     IsInitialized;     // +0x0c
    unsigned char     IsAllocated;       // +0x0d
    int               Count;             // +0x10
    int               CapacityIncrement; // +0x14

    bool AddItem(Techno_004138C0* const& item)
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
    bool RemoveItem(Techno_004138C0* const& item)
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
GG_STATIC_ASSERT(offsetof(DynVec_004138C0, Items)             == 0x04);
GG_STATIC_ASSERT(offsetof(DynVec_004138C0, Capacity)          == 0x08);
GG_STATIC_ASSERT(offsetof(DynVec_004138C0, IsAllocated)       == 0x0D);
GG_STATIC_ASSERT(offsetof(DynVec_004138C0, Count)             == 0x10);
GG_STATIC_ASSERT(offsetof(DynVec_004138C0, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(DynVec_004138C0) == 0x18);

class AircraftTracker_004138C0
{
public:
    // FUNCTION: GAMEMD 0x4138C0 — AircraftTrackerClass::Update.
    void Update(Techno_004138C0* techno, CellStruct_004138C0 oldCell,
                CellStruct_004138C0 newCell);

    DynVec_004138C0 TrackerVectors[20][20];  // +0x0000  (400 * 0x18)
    DynVec_004138C0 CurrentVector;           // +0x2580
};
GG_STATIC_ASSERT(offsetof(AircraftTracker_004138C0, CurrentVector) == 0x2580);
GG_STATIC_ASSERT(sizeof(AircraftTracker_004138C0) == 0x2598);

#endif  // GG_MATCH_AI_AIRCRAFT_TRACKER_UPDATE_METHODS_H
