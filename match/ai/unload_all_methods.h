// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4575B0. The count at +0x702 is a signed byte — retail
//   sign-extends it with MOVSX before indexing — and it indexes the pointer array
//   that starts at +0x5E8.
#ifndef GG_MATCH_AI_UNLOAD_ALL_METHODS_H
#define GG_MATCH_AI_UNLOAD_ALL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Target_004575B0
{
    char _pad0000[0x5778];    // +0x0000
    char At_5778;             // +0x5778
    char At_5779;             // +0x5779

    // FUNCTION: GAMEMD 0x4F9950 — a member, not a free __fastcall: retail
    // pushes the value and passes the target in ECX.
    void FUN_004F9950(int value);
};
GG_STATIC_ASSERT(offsetof(Target_004575B0, At_5779) == 0x5779);

// Declaration order per match/_rt/gg_vslot.h, for both classes with slot calls.
struct ItemVtbl_004575B0;
struct Item_004575B0 { ItemVtbl_004575B0* Vptr; };
typedef int (Item_004575B0::*FnB8_004575B0)(Target_004575B0* target, int flag);
struct ItemVtbl_004575B0
{
    char _pad000[0xB8];       // +0x0000
    FnB8_004575B0 At_B8;      // +0x00B8
};
GG_STATIC_ASSERT(offsetof(ItemVtbl_004575B0, At_B8) == 0xB8);

struct ObjVtbl_004575B0;

struct Obj_004575B0
{
    ObjVtbl_004575B0* Vptr;         // +0x0000
    char _pad0004[0x218];           // +0x0004
    Target_004575B0* Target;        // +0x021C
    char _pad0220[0x3C8];           // +0x0220
    Item_004575B0* Items[0x46];     // +0x05E8
    char _pad0700[0x2];             // +0x0700
    char Count;                     // +0x0702

    // FUNCTION: GAMEMD 0x451690
    void FUN_00451690();

    // FUNCTION: GAMEMD 0x4575B0
    void FUN_004575B0();
};
GG_STATIC_ASSERT(offsetof(Obj_004575B0, Target) == 0x21C);
GG_STATIC_ASSERT(offsetof(Obj_004575B0, Items) == 0x5E8);
GG_STATIC_ASSERT(offsetof(Obj_004575B0, Count) == 0x702);

typedef int (Obj_004575B0::*Fn1A0_004575B0)(int flag);

struct ObjVtbl_004575B0
{
    char _pad000[0x1A0];      // +0x0000
    Fn1A0_004575B0 At_1A0;    // +0x01A0
};
GG_STATIC_ASSERT(offsetof(ObjVtbl_004575B0, At_1A0) == 0x1A0);

#endif  // GG_MATCH_AI_UNLOAD_ALL_METHODS_H
