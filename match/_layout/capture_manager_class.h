// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: CaptureManagerClass ctor FUN_0x004717D0 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0). Argument binding is unusually explicit here,
//   which pins three members outright: arg1 pOwner -> 0x48, arg2
//   nMaxControlNodes -> 0x3C, arg3 bInfiniteControl -> 0x40.
//   sizeof: `PUSH 0x50` before the ctor call at its allocation site.
//   RTTI: 0x007E4B40 / 0x007E4B24 (+ the +8/+0xC tables) resolve to
//   ".?AVCaptureManagerClass@@" (stored @0x00471807..0x0047181B).
//
//   The ctor also re-proves the DynamicVectorClass layout asserted in
//   vector_class.h: for ControlNodes at 0x24 it stores the vptr at 0x24
//   (0x007E4BA4), Items 0x28, Capacity 0x2C, IsAllocated (byte) 0x30, Count
//   0x34 and CapacityIncrement 0x38 = 0xA.
//
//   Cross-read against YRpp CaptureManagerClass.h: 7 named members claimed,
//   7 confirmed. No disagreement found.
//
// CaptureManagerClass — mind-control link bookkeeping. Derives AbstractClass.
#ifndef GG_MATCH_LAYOUT_CAPTURE_MANAGER_CLASS_H
#define GG_MATCH_LAYOUT_CAPTURE_MANAGER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "vector_class.h"

struct CaptureManagerClass : AbstractClass
{
    DynamicVectorClass ControlNodes;           // +0x24 (0x18) ctor vptr @0x004717EF, fields
                                               //   @0x004717E6/0x004717E9/0x004717E2/0x004717FD/0x004717F6
    int           MaxControlNodes;             // +0x3C ctor = arg2 @0x00471822
    unsigned char InfiniteMindControl;         // +0x40 ctor = arg3 @0x00471825
    unsigned char OverloadDeathSoundPlayed;    // +0x41 ctor @0x00471828
    unsigned char align_42[2];                 // +0x42
    int           OverloadPipState;            // +0x44 ctor @0x00471832
    void*         Owner;                       // +0x48 TechnoClass*; ctor = arg1 @0x00471800
    int           OverloadDamageDelay;         // +0x4C ctor MOV [ESI+0x4C],0x1E @0x0047182B;
                                               //   closes the object at 0x50
};

GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes)            == 0x24);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, MaxControlNodes)         == 0x3C);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, InfiniteMindControl)     == 0x40);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, OverloadDeathSoundPlayed)== 0x41);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, OverloadPipState)        == 0x44);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, Owner)                   == 0x48);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, OverloadDamageDelay)     == 0x4C);
GG_STATIC_ASSERT(sizeof(CaptureManagerClass)                            == 0x50);

// VTABLE: GAMEMD 0x007E4B40  CaptureManagerClass
// VTABLE: GAMEMD 0x007E4B24  CaptureManagerClass::(+0x04)
// VTABLE: GAMEMD 0x007E4B1C  CaptureManagerClass::(+0x08)
// VTABLE: GAMEMD 0x007E4B14  CaptureManagerClass::(+0x0C)

#endif  // GG_MATCH_LAYOUT_CAPTURE_MANAGER_CLASS_H
