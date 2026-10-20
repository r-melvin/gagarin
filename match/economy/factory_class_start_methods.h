// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4CA5A0. The member layout is confirmed against YRpp
//   FactoryClass.h (consult-only) working *backwards* from its named tail:
//   Owner @0x6C and IsSuspended @0x70 are read directly by this function, and
//   Object @0x58 sits immediately after a DynamicVectorClass — which places
//   QueuedObjects at 0x40, hence Items @0x44 and Count @0x50, exactly the
//   offsets the body uses.
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_START_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_START_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HouseClass
{
    // 0x4FA350 — __thiscall taking the result of the queued item's Slot_2C.
    void ProductionStarted(int result);
};

// The queued blueprint. Two vtable slots are dispatched; because Slot_2C takes
// stack arguments it must be a real virtual rather than the tree's
// __fastcall-fn-pointer shortcut (methodology §4.6).
struct TechnoTypeClass
{
#include "factory_class_start_slots.inc"

    char          _padAfterVtbl[0xCCE - 4];  // +0x0004
    unsigned char unknown_CCE;               // +0x0CCE  passed to Slot_2C
};
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, unknown_CCE) == 0xCCE);

struct FactoryClass
{
    char              _pad00[0x38];          // +0x0000
    int               unknown_38;            // +0x0038  gates the IsSuspended check
    char              _pad3C[0x44 - 0x3C];   // +0x003C  (QueuedObjects vptr @0x40)
    TechnoTypeClass** QueuedObjects_Items;   // +0x0044
    char              _pad48[0x50 - 0x48];   // +0x0048
    int               QueuedObjects_Count;   // +0x0050
    char              _pad54[0x58 - 0x54];   // +0x0054
    void*             Object;                // +0x0058
    char              _pad5C[0x6C - 0x5C];   // +0x005C
    HouseClass*       Owner;                 // +0x006C
    bool              IsSuspended;           // +0x0070

    void StartProduction();                  // GAMEMD 0x4CA5A0
};
GG_STATIC_ASSERT(offsetof(FactoryClass, unknown_38)          == 0x38);
GG_STATIC_ASSERT(offsetof(FactoryClass, QueuedObjects_Items) == 0x44);
GG_STATIC_ASSERT(offsetof(FactoryClass, QueuedObjects_Count) == 0x50);
GG_STATIC_ASSERT(offsetof(FactoryClass, Object)              == 0x58);
GG_STATIC_ASSERT(offsetof(FactoryClass, Owner)               == 0x6C);
GG_STATIC_ASSERT(offsetof(FactoryClass, IsSuspended)         == 0x70);

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_START_METHODS_H
