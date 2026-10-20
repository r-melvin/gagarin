// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x7265C0 / 0x726720), cross-checked
//   against YRpp TriggerClass.h / TriggerTypeClass.h / TActionClass.h /
//   HouseTypeClass.h / HouseClass.h / ArrayClasses.h (consult-only; every
//   offset reconfirmed numerically here).
//
// TriggerClass::FireActions walks the trigger's type action list and Execute()s
// each, OR-ing the results. TriggerClass::Destroy marks the trigger Destroyed
// and appends it to the global "triggers pending destruction" vector at
// 0x00B0F698 (DynamicVectorClass<TriggerClass*>; AddItem inlined by the original,
// reaching the virtual SetCapacity through [vtable+0x08]).
#ifndef GG_MATCH_AI_TRIGGER_CLASS_DESTROY_METHODS_H
#define GG_MATCH_AI_TRIGGER_CLASS_DESTROY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class ObjectClass;   // only ever a pointer here

// CellStruct (two shorts). FireActions takes it by value; TActionClass::Execute
// takes it by const-ref (so the by-value copy's address is forwarded).
struct CellStruct
{
    short X;
    short Y;
};

// HouseClass::FindByCountryIndex — static __fastcall (arg in ECX) @0x502D30.
class HouseClass
{
public:
    static HouseClass* __fastcall FindByCountryIndex(int houseType);
};

// HouseTypeClass — only ArrayIndex @0xB4 is touched (the FindByCountryIndex arg).
struct HouseTypeClass
{
    char _pad0[0xB4];   // +0x000  AbstractTypeClass base + earlier members (P2)
    int  ArrayIndex;    // +0x0B4
};
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArrayIndex) == 0xB4);

struct TriggerClass;  // fwd (Execute's pTrigger arg)

// TActionClass — singly-linked action node. NextAction @0x28; Execute @0x6DD8B0.
struct TActionClass
{
    char          _pad0[0x28];   // +0x000  AbstractClass base + ArrayIndex (P2)
    TActionClass* NextAction;    // +0x028

    // GAMEMD 0x6DD8B0 __thiscall — declared (no body) so cl emits a reloc call.
    bool Execute(HouseClass* pHouse, ObjectClass* pObject,
                 TriggerClass* pTrigger, const CellStruct& location);
};
GG_STATIC_ASSERT(offsetof(TActionClass, NextAction) == 0x28);

// TriggerTypeClass — House @0xA4, FirstAction @0xB0.
struct TriggerTypeClass
{
    char            _pad0[0xA4];    // +0x000  AbstractTypeClass base + members (P2)
    HouseTypeClass* House;          // +0x0A4
    char            _gap_a8[0x08];  // +0x0A8  NextTrigger + FirstEvent
    TActionClass*   FirstAction;    // +0x0B0
};
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, House)       == 0xA4);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstAction) == 0xB0);

// Global DynamicVectorClass<TriggerClass*> at 0x00B0F698. The virtuals are
// declared only to pin the vtable slot order so the inlined AddItem reaches
// SetCapacity through [vtable+0x08] (slot 2), exactly as retail.
struct TriggerPtrVector
{
    // slot 0 / 1 / 2 — declarations only (never instantiated in this TU).
    virtual ~TriggerPtrVector();
    virtual bool operator==(const TriggerPtrVector& other) const;
    virtual bool SetCapacity(int capacity, TriggerClass** pMem);

    // VectorClass<T> data (vptr occupies +0x00):
    TriggerClass** Items;             // +0x04
    int            Capacity;          // +0x08
    bool           IsInitialized;     // +0x0C
    bool           IsAllocated;       // +0x0D
    // DynamicVectorClass<T> data:
    int            Count;             // +0x10
    int            CapacityIncrement; // +0x14

    // DynamicVectorClass<T>::AddItem — inlined into Destroy by the original.
    // Same shape as the matched CellClass::ReplaceTag expansion (0x485250):
    // Capacity bound to a local so the vtable load stays ahead of the argument
    // pushes (`ADD ECX,EAX; MOV EAX,[vtbl]; PUSH 0; PUSH ECX`), the grow
    // decision as one condition, and `Count++` bound to a local so the
    // increment is sequenced before the store (`MOV EAX,ECX; INC ECX`).
    bool AddItem(TriggerClass* item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && SetCapacity(cap + CapacityIncrement, 0))) {
            int index = Count++;
            Items[index] = item;
            return true;
        }
        return false;
    }
};

// TriggerClass — Type @0x24, Destroyed @0x30, Enabled @0x44 are the only members
// these two methods touch; the base is padded (full layout is P2).
struct TriggerClass
{
    char              _pad0[0x24];     // +0x000  AbstractClass base (P2)
    TriggerTypeClass* Type;            // +0x024
    char              _gap_28[0x08];   // +0x028  NextTrigger + House
    bool              Destroyed;       // +0x030
    char              _gap_31[0x13];   // +0x031  align + Timer + OccuredEvents
    bool              Enabled;         // +0x044

    // GAMEMD 0x7265C0 __thiscall — true if any action executed.
    bool FireActions(ObjectClass* pObj, CellStruct location);
    // GAMEMD 0x726720 __thiscall — mark destroyed + enqueue for destruction.
    void Destroy();
};
GG_STATIC_ASSERT(offsetof(TriggerClass, Type)      == 0x24);
GG_STATIC_ASSERT(offsetof(TriggerClass, Destroyed) == 0x30);
GG_STATIC_ASSERT(offsetof(TriggerClass, Enabled)   == 0x44);

// The retail global cleanup vector (relocation-normalised by the differ).
extern TriggerPtrVector TriggersToDestroy;  // 0x00B0F698

#endif  // GG_MATCH_AI_TRIGGER_CLASS_DESTROY_METHODS_H
