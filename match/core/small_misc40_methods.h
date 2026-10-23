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
// 0x407100 — arm a timer.
//
// 0x4093B0 hands back a 64-bit reading in EDX:EAX (the caller at 0x4070B0 adds
// it with `ADD`/`ADC`), and the two halves land at +0x18 and +0x1C. The
// argument is scaled by 65536 into +0x08, and +0x0C gets 0x10624D. The final
// hand-off is a real `JMP`, so the callee is a __fastcall free function.
// ---------------------------------------------------------------------------
// Modelled as a two-int struct rather than `__int64`. MSVC returns an 8-byte
// POD in EDX:EAX, which is the same register pair, but reading the high half of
// an `__int64` as `(int)(x >> 32)` costs a `MOV EAX,EDX` that retail does not
// have - the struct's second member is already EDX.
struct Pair64 { int Lo; int Hi; };
Pair64 FUN_004093B0();   // FUNCTION: GAMEMD 0x4093B0
void    FUN_004071C0(void* self);   // FUNCTION: GAMEMD 0x4071C0

struct Timer_00407100
{
    int field_00;   // +0x0000  flag word
    int field_04;
    int Scaled;     // +0x0008
    int Rate;       // +0x000C
    int Limit;      // +0x0010
    int field_14;   // +0x0014
    int StartLo;    // +0x0018
    int StartHi;    // +0x001C
};
GG_STATIC_ASSERT(offsetof(Timer_00407100, StartHi) == 0x1C);

// FUNCTION: GAMEMD 0x407100
void FUN_00407100(Timer_00407100* self, int value);

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
