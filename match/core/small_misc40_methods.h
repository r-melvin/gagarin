// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, constants and call targets read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x403820, 0x407100 and
//   0x408D30.
#ifndef GG_MATCH_CORE_SMALL_MISC40_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC40_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x403820 — clear a block of fields, with one non-zero default.
//
// Twenty stores, all from the single zero in EAX except +0x40, which gets
// 0x1388 (5000). They are written in retail's emitted order; the gaps in that
// order (+0x28 and +0x2C jump ahead of +0x48 and +0x50, and +0x40 lands between
// +0x50 and +0x44) are what the source order has to be, since plain stores are
// not reordered.
// ---------------------------------------------------------------------------
struct Obj_00403820
{
    // FUNCTION: GAMEMD 0x403870 (decl; reloc)
    void FUN_00403870(__int64 value);
    // FUNCTION: GAMEMD 0x4038A0 (decl; reloc)
    void FUN_004038A0(__int64 value);
    // FUNCTION: GAMEMD 0x4038C0 (decl; reloc)
    void FUN_004038C0(__int64 value);
    // FUNCTION: GAMEMD 0x403920 (decl; reloc)
    void FUN_00403920(__int64 value);
    int field_00, field_04, field_08, field_0C;
    int field_10, field_14, field_18, field_1C;
    int field_20, field_24, field_28, field_2C;
    int field_30, field_34, field_38, field_3C;
    int field_40, field_44, field_48, field_4C;
    int field_50, field_54;
};
GG_STATIC_ASSERT(offsetof(Obj_00403820, field_54) == 0x54);

// FUNCTION: GAMEMD 0x403820
void FUN_00403820(Obj_00403820* self);

// ---------------------------------------------------------------------------
// 0x408D30 — the difference between two counters.
// ---------------------------------------------------------------------------
struct Obj_00408D30
{
    char _pad000[0x8C];
    int  Head;   // +0x008C
    // volatile: +0x90 is +0x38 of the second channel (+0x58, see 0x408C30),
    // which the stream thread 0x53E070 (CreateThread @0x53DF2A) advances in
    // 0x409100 (store @0x409127); it calls this body @0x53E0EB.
    volatile int Tail;   // +0x0090

    // FUNCTION: GAMEMD 0x408D30
    int FUN_00408D30();
};
GG_STATIC_ASSERT(offsetof(Obj_00408D30, Head) == 0x8C);
GG_STATIC_ASSERT(offsetof(Obj_00408D30, Tail) == 0x90);

#endif  // GG_MATCH_CORE_SMALL_MISC40_METHODS_H
