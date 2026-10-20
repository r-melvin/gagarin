// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and the vtable slot read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x44F5C0: `[ESI+0x504]`,
//   `[ESI+0x21C]`, `[ESI+0x2C0]`, `[ESI+0x520]` and the slot `[EAX+0x284]`,
//   plus the owner's `+0x408` and `+0x16B9`.
#ifndef GG_MATCH_AI_CAN_RETALIATE_METHODS_H
#define GG_MATCH_AI_CAN_RETALIATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Owner_0044F5C0
{
    char _pad0000[0x408];      // +0x0000
    int  At_408;               // +0x0408
    char _pad040C[0x12AD];     // +0x040C
    char At_16B9;              // +0x16B9
};
GG_STATIC_ASSERT(offsetof(Owner_0044F5C0, At_408) == 0x408);
GG_STATIC_ASSERT(offsetof(Owner_0044F5C0, At_16B9) == 0x16B9);

// GLOBAL: GAMEMD 0xA8B238
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0xA8B320
extern char DAT_00A8B320;

// FUNCTION: GAMEMD 0x50B730
bool __fastcall FUN_0050B730(void* target);

struct Vtbl_0044F5C0;

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x44F5C0 -> BuildingClass slot 40 (byte-off 0xA0).
// That table is the only table in the image that holds it, so the slot is
// declared on BuildingClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BuildingClass_0044F5C0
{
    Vtbl_0044F5C0* Vptr;       // +0x0000
    char _pad0004[0x218];      // +0x0004
    void* At_21C;              // +0x021C
    char _pad0220[0xA0];       // +0x0220
    int  At_2C0;               // +0x02C0
    char _pad02C4[0x240];      // +0x02C4
    int  At_504;               // +0x0504
    char _pad0508[0x18];       // +0x0508
    Owner_0044F5C0* Owner;     // +0x0520

    // FUNCTION: GAMEMD 0x44F5C0
    bool FUN_0044F5C0();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_0044F5C0, At_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(BuildingClass_0044F5C0, At_2C0) == 0x2C0);
GG_STATIC_ASSERT(offsetof(BuildingClass_0044F5C0, At_504) == 0x504);
GG_STATIC_ASSERT(offsetof(BuildingClass_0044F5C0, Owner) == 0x520);

typedef bool (BuildingClass_0044F5C0::*Fn284_0044F5C0)();

struct Vtbl_0044F5C0
{
    char _pad000[0x284];       // +0x0000
    Fn284_0044F5C0 At_284;     // +0x0284
};
GG_STATIC_ASSERT(offsetof(Vtbl_0044F5C0, At_284) == 0x284);

#endif  // GG_MATCH_AI_CAN_RETALIATE_METHODS_H
