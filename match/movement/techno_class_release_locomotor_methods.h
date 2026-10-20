// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x70FEE0: `[ESI+0x2AC]` (LocomotorTarget, re-read
//   from memory at every use), the target's `[EAX+0x2B0]` (LocomotorSource),
//   `[ECX+0x14]` bit 2 (AbstractClass flag: FootClass), `[ECX+0x425]`
//   (IsCrashing), `[EDX+0x427]` (IsBeingManipulated), `[EAX+0x428]`
//   (BeingManipulatedBy), `[ECX+0x42C]` (ChronoWarpedByHouse) written from
//   `[ESI+0x21C]` (Owner), `[EAX+0x6AE]` (FootClass::IsLetGoByLocomotor);
//   vtable slots `[EAX+0x1C8]` GetHeight, `[EAX+0x3A0]` (clear-target
//   action), `[EDX+0x480]` SetDestination(0, true) and `[EAX+0x3C8]`
//   SetTarget(0). Names cross-checked against YRpp TechnoClass.h /
//   FootClass.h (consult-only; NO LICENSE).
#ifndef GG_MATCH_MOVEMENT_TECHNO_CLASS_RELEASE_LOCOMOTOR_METHODS_H
#define GG_MATCH_MOVEMENT_TECHNO_CLASS_RELEASE_LOCOMOTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Vtbl_0070FEE0;

// TechnoClass / FootClass as seen from this method.
struct Techno_0070FEE0
{
    Vtbl_0070FEE0*    Vptr;                    // +0x0000
    char              _pad004[0x10];           // +0x0004
    unsigned char     AbstractFlags;           // +0x0014  bit 2 = FootClass
    char              _pad015[0x21C - 0x15];   // +0x0015
    void*             Owner;                   // +0x021C
    char              _pad220[0x2AC - 0x220];  // +0x0220
    Techno_0070FEE0*  LocomotorTarget;         // +0x02AC
    Techno_0070FEE0*  LocomotorSource;         // +0x02B0
    char              _pad2B4[0x425 - 0x2B4];  // +0x02B4
    unsigned char     IsCrashing;              // +0x0425
    char              _pad426;                 // +0x0426
    unsigned char     IsBeingManipulated;      // +0x0427
    Techno_0070FEE0*  BeingManipulatedBy;      // +0x0428
    void*             ChronoWarpedByHouse;     // +0x042C
    char              _pad430[0x6AE - 0x430];  // +0x0430
    unsigned char     IsLetGoByLocomotor;      // +0x06AE (FootClass)

    // FUNCTION: GAMEMD 0x70FEE0 — TechnoClass::ReleaseLocomotor.
    void ReleaseLocomotor(bool clearTarget);
};
GG_STATIC_ASSERT(offsetof(Techno_0070FEE0, AbstractFlags)       == 0x14);
GG_STATIC_ASSERT(offsetof(Techno_0070FEE0, Owner)               == 0x21C);
GG_STATIC_ASSERT(offsetof(Techno_0070FEE0, LocomotorTarget)     == 0x2AC);
GG_STATIC_ASSERT(offsetof(Techno_0070FEE0, LocomotorSource)     == 0x2B0);
GG_STATIC_ASSERT(offsetof(Techno_0070FEE0, IsCrashing)          == 0x425);
GG_STATIC_ASSERT(offsetof(Techno_0070FEE0, IsBeingManipulated)  == 0x427);
GG_STATIC_ASSERT(offsetof(Techno_0070FEE0, BeingManipulatedBy)  == 0x428);
GG_STATIC_ASSERT(offsetof(Techno_0070FEE0, ChronoWarpedByHouse) == 0x42C);
GG_STATIC_ASSERT(offsetof(Techno_0070FEE0, IsLetGoByLocomotor)  == 0x6AE);

typedef int  (Techno_0070FEE0::*Fn1C8_0070FEE0)();
typedef void (Techno_0070FEE0::*Fn3A0_0070FEE0)();
typedef void (Techno_0070FEE0::*Fn3C8_0070FEE0)(void* target);
typedef void (Techno_0070FEE0::*Fn480_0070FEE0)(void* target, bool a2);

struct Vtbl_0070FEE0
{
    char            _pad000[0x1C8];          // +0x0000
    Fn1C8_0070FEE0  GetHeight;               // +0x01C8
    char            _pad1CC[0x3A0 - 0x1CC];  // +0x01CC
    Fn3A0_0070FEE0  At_3A0;                  // +0x03A0  clear-target action
    char            _pad3A4[0x3C8 - 0x3A4];  // +0x03A4
    Fn3C8_0070FEE0  SetTarget;               // +0x03C8
    char            _pad3CC[0x480 - 0x3CC];  // +0x03CC
    Fn480_0070FEE0  SetDestination;          // +0x0480
};
GG_STATIC_ASSERT(offsetof(Vtbl_0070FEE0, GetHeight)      == 0x1C8);
GG_STATIC_ASSERT(offsetof(Vtbl_0070FEE0, At_3A0)         == 0x3A0);
GG_STATIC_ASSERT(offsetof(Vtbl_0070FEE0, SetTarget)      == 0x3C8);
GG_STATIC_ASSERT(offsetof(Vtbl_0070FEE0, SetDestination) == 0x480);

#endif  // GG_MATCH_MOVEMENT_TECHNO_CLASS_RELEASE_LOCOMOTOR_METHODS_H
