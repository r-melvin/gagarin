// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x6CB7B0. IsPresent @0x6D and IsReady @0x6F match
//   the member run already committed in super_class_methods.h and are
//   reconfirmed here. The vector globals — vptr 0x00A83D50, Items 0x00A83D54,
//   Count 0x00A83D60 — are +0x00/+0x04/+0x10 of one object, which is YRpp's
//   SuperClass::ShowTimers at 0x00A83D50 (consult-only, no LICENSE).
#ifndef GG_MATCH_COMBAT_SUPER_CLASS_LOSE_METHODS_H
#define GG_MATCH_COMBAT_SUPER_CLASS_LOSE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct SuperClass;

// DynamicVectorClass<SuperClass*>. Retail issues FindItemIndex *indirectly*
// through the object's vptr rather than devirtualising it, so the slot run is
// declared for real. The placeholder slots are declared rather than made pure:
// an `extern` object of the type has to be concrete, and no vtable is emitted
// because the class is never instantiated here. The argument is taken by reference: retail hands over the
// address of a stack temporary (`MOV [ESP],ECX; LEA EAX,[ESP]; PUSH EAX`).
struct SuperTimerVectorClass
{
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual int  FindItemIndex(SuperClass* const& item);   // +0x10 (declared; reloc)

    SuperClass** Items;        // +0x04
    int          Capacity;     // +0x08
    int          IsAllocated;  // +0x0C
    int          Count;        // +0x10
};
GG_STATIC_ASSERT(offsetof(SuperTimerVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(SuperTimerVectorClass, Count) == 0x10);

// GLOBAL: GAMEMD 0x00A83D50 — SuperClass::ShowTimers.
extern SuperTimerVectorClass ShowTimers;

struct SuperClass
{
    char _pad00[0x6D];   // +0x0000
    bool IsPresent;      // +0x006D
    char _pad6E;         // +0x006E
    bool IsReady;        // +0x006F

    bool Lose();         // GAMEMD 0x6CB7B0
};
GG_STATIC_ASSERT(offsetof(SuperClass, IsPresent) == 0x6D);
GG_STATIC_ASSERT(offsetof(SuperClass, IsReady)   == 0x6F);

#endif  // GG_MATCH_COMBAT_SUPER_CLASS_LOSE_METHODS_H
