// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and slots read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x473750: the snapshot's own fields at +0x4..+0x1C,
//   the source object's at +0x6C and +0x21C, and the four slots +0x2C, +0x84,
//   +0x40 (on the sub-object) and +0x1B8.
#ifndef GG_MATCH_COMBAT_TARGET_SNAPSHOT_CTOR_METHODS_H
#define GG_MATCH_COMBAT_TARGET_SNAPSHOT_CTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// VTABLE: GAMEMD 0x7E4C04
extern void* const VTBL_007E4C04[];

// Declaration order per match/_rt/gg_vslot.h, for each class with a slot call.
struct SubVtbl_00473750;
struct Sub_00473750 { SubVtbl_00473750* Vtbl; };
typedef int (Sub_00473750::*Fn40_00473750)();
struct SubVtbl_00473750
{
    char unknown_00[0x40];        // +0x0000
    Fn40_00473750 At_40;       // +0x0040
};
GG_STATIC_ASSERT(offsetof(Sub_00473750, Vtbl) == 0);
GG_STATIC_ASSERT(sizeof(Fn40_00473750) == 4);
GG_STATIC_ASSERT(offsetof(SubVtbl_00473750, At_40) == 0x40);

struct Owner_00473750;

// Layout view for two 16-bit units cleared separately and copied together.
// Their semantic meaning and signedness are not established by this body.
struct Pair16_00473750 { short A; short B; };
GG_STATIC_ASSERT(offsetof(Pair16_00473750, A) == 0);
GG_STATIC_ASSERT(offsetof(Pair16_00473750, B) == 2);
GG_STATIC_ASSERT(sizeof(Pair16_00473750) == 4);

// What +0x21C points at, and the block 0x34 into it.
struct Detail_00473750
{
    char unknown_00[0xB8];        // +0x0000
    int  At_B8;                // +0x00B8
};
struct Holder_00473750
{
    char unknown_00[0x34];        // +0x0000
    Detail_00473750* Detail;   // +0x0034
};
GG_STATIC_ASSERT(offsetof(Detail_00473750, At_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(Holder_00473750, Detail) == 0x34);

struct OwnerVtbl_00473750;

struct Owner_00473750
{
    OwnerVtbl_00473750* Vtbl;  // +0x0000
    char unknown_04[0x68];        // +0x0004
    int  At_6C;                // +0x006C
    char unknown_70[0x1AC];       // +0x0070
    Holder_00473750* Holder;   // +0x021C
};
GG_STATIC_ASSERT(offsetof(Owner_00473750, Vtbl) == 0);
GG_STATIC_ASSERT(offsetof(Owner_00473750, At_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(Owner_00473750, Holder) == 0x21C);

typedef int (Owner_00473750::*Fn2C_00473750)();
typedef Sub_00473750* (Owner_00473750::*Fn84_00473750)();
typedef Pair16_00473750* (Owner_00473750::*Fn1B8_00473750)(void* scratch);

struct OwnerVtbl_00473750
{
    char unknown_00[0x2C];             // +0x0000
    Fn2C_00473750 At_2C;            // +0x002C
    char unknown_30[0x84 - 0x30];      // +0x0030
    Fn84_00473750 At_84;            // +0x0084
    char unknown_88[0x1B8 - 0x88];     // +0x0088
    Fn1B8_00473750 At_1B8;          // +0x01B8
};
GG_STATIC_ASSERT(sizeof(Fn2C_00473750) == 4);
GG_STATIC_ASSERT(sizeof(Fn84_00473750) == 4);
GG_STATIC_ASSERT(sizeof(Fn1B8_00473750) == 4);
GG_STATIC_ASSERT(offsetof(OwnerVtbl_00473750, At_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(OwnerVtbl_00473750, At_84) == 0x84);
GG_STATIC_ASSERT(offsetof(OwnerVtbl_00473750, At_1B8) == 0x1B8);

struct Snapshot_00473750
{
    const void* Vptr;      // +0x0000
    int  At_04;            // +0x0004
    int  At_08;            // +0x0008
    int  Kind;             // +0x000C
    int  At_10;            // +0x0010
    Pair16_00473750 At_14; // +0x0014
    int  At_18;            // +0x0018
    int  At_1C;            // +0x001C

    // FUNCTION: GAMEMD 0x473750
    Snapshot_00473750* Ctor(Owner_00473750* owner);
};
GG_STATIC_ASSERT(offsetof(Snapshot_00473750, Vptr) == 0);
GG_STATIC_ASSERT(offsetof(Snapshot_00473750, At_04) == 4);
GG_STATIC_ASSERT(offsetof(Snapshot_00473750, At_08) == 8);
GG_STATIC_ASSERT(offsetof(Snapshot_00473750, Kind) == 0xC);
GG_STATIC_ASSERT(offsetof(Snapshot_00473750, At_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Snapshot_00473750, At_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Snapshot_00473750, At_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Snapshot_00473750, At_14) + offsetof(Pair16_00473750, B) == 0x16);
GG_STATIC_ASSERT(offsetof(Snapshot_00473750, At_1C) == 0x1C);

#endif  // GG_MATCH_COMBAT_TARGET_SNAPSHOT_CTOR_METHODS_H
