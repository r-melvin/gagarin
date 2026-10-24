// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly of the four production
//   accessors), cross-checked against YRpp
//   (each offset reconfirmed numerically below).
//
// FactoryClass — produces units/buildings for a HouseClass. Derives from
// AbstractClass (0x24 bytes; Production.Value lands at this+0x24, so the base is
// exactly 0x24). Only the members the four targeted methods touch are pinned;
// the full layout is asserted to YRpp's 0x74 total size.
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

class TechnoTypeClass;
class TechnoClass;
class HouseClass;

#include "../_layout/stage_class.h"

// DynamicVectorClass<TechnoTypeClass*> head: vtable@0, Items@4, Capacity@8,
// IsAllocated@0xC, Count@0x10, CapacityIncrement@0x14 => sizeof 0x18.
// IsQueued reads Items (this+0x44) and Count (this+0x50).
struct Obj_004CA6B0
{
    void*             vtable;             // +0x00
    TechnoTypeClass** Items;              // +0x04
    int               Capacity;           // +0x08
    int               IsAllocated;        // +0x0C
    int               Count;              // +0x10
    int               CapacityIncrement;  // +0x14
};

class FactoryClass
{
public:
    char         _abstract_base[0x24];  // +0x00  AbstractClass (vtable + members)
    StageClass   Production;            // +0x24  progress timer; .Value == 0x36 when done
    Obj_004CA6B0 QueuedObjects; // +0x40
    TechnoClass* Object;               // +0x58  item currently in production
    bool         OnHold;               // +0x5C
    bool         IsDifferent;          // +0x5D  set when progress changed this frame
    char         _pad5E[2];            // +0x5E  align_5E[2]
    int          Balance;              // +0x60
    int          OriginalBalance;      // +0x64
    int          SpecialItem;          // +0x68  -1 = none
    HouseClass*  Owner;                // +0x6C
    bool         IsSuspended;          // +0x70
    bool         IsManual;             // +0x71
    char         _pad72[2];            // +0x72  padding_72[2]

    // Declared ascending by retail address (reccmp/isle TU discipline).
    bool HasProgressChanged();                       // GAMEMD 0x4C9C60 __thiscall
    int  GetProgress() const;                        // GAMEMD 0x4CA120 __thiscall
    bool IsDone() const;                             // GAMEMD 0x4CA130 __thiscall
    bool IsQueued(TechnoTypeClass* pType) const;     // GAMEMD 0x4CA6B0 __thiscall
};

GG_STATIC_ASSERT(offsetof(FactoryClass, Production) == 0x24);
GG_STATIC_ASSERT(offsetof(FactoryClass, QueuedObjects) == 0x40);
GG_STATIC_ASSERT(offsetof(FactoryClass, QueuedObjects.Items) == 0x44);
GG_STATIC_ASSERT(offsetof(FactoryClass, QueuedObjects.Count) == 0x50);
GG_STATIC_ASSERT(offsetof(FactoryClass, Object) == 0x58);
GG_STATIC_ASSERT(offsetof(FactoryClass, IsDifferent) == 0x5D);
GG_STATIC_ASSERT(offsetof(FactoryClass, SpecialItem) == 0x68);
GG_STATIC_ASSERT(sizeof(FactoryClass) == 0x74);

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_METHODS_H
