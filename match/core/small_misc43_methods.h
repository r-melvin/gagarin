// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable addresses and masks read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x4053E0 and 0x410170.
#ifndef GG_MATCH_CORE_SMALL_MISC43_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC43_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x4053E0 — on the first pause only, roll a 64-bit accumulator back by the
// current reading, then count the pause.
//
// The accumulator at +0x140 is subtracted with `SUB`/`SBB` across +0x140 and
// +0x144, so it is a single 64-bit value and 0x4093B0's reading is used as one
// too - unlike 0x407100, where the two halves go to separate fields and the
// two-int struct form is the right model.
// ---------------------------------------------------------------------------
__int64 __fastcall FUN_004093B0();   // FUNCTION: GAMEMD 0x4093B0

struct Obj_004053E0
{
    Obj_004053E0* Next;   // +0x0000  ring link
    char    _pad004[0x1C - 0x04];
    int     State;       // +0x001C
    char    _pad020[0x140 - 0x20];
    __int64 Accumulated; // +0x0140
    char    _pad148[0x158 - 0x148];
    int     PauseCount;  // +0x0158
};
GG_STATIC_ASSERT(offsetof(Obj_004053E0, State) == 0x1C);
GG_STATIC_ASSERT(offsetof(Obj_004053E0, Accumulated) == 0x140);
GG_STATIC_ASSERT(offsetof(Obj_004053E0, PauseCount) == 0x158);

// FUNCTION: GAMEMD 0x4053E0
void __fastcall FUN_004053E0(Obj_004053E0* self);

// FUNCTION: GAMEMD 0x405430 — resume: the mirror of 0x4053E0. The pause count
// is floored down rather than counted up, and the accumulator gains the reading
// instead of losing it.
//
// The addition is written reading-first (`reading + accumulated`) because that
// is which operand retail makes the destination: `ADD EAX,ECX; ADC EDX,EDI`
// keeps the call's own return pair and adds the member into it. The subtract in
// 0x4053E0 has no such freedom, which is why that one is still a partial.
void __fastcall FUN_00405430(Obj_004053E0* self);

// ---------------------------------------------------------------------------
// 0x405040 — resume every timer on the global ring at 0x87E180.
//
// The ring is circular through the word at +0x00 and the header address is its
// own sentinel, so the walk ends when the cursor comes back to 0x87E180. The
// per-node body is exactly 0x405430's.
// ---------------------------------------------------------------------------
// GLOBAL: GAMEMD 0x87E2A0 — the gate; 0x87E180 is the ring header.
extern int DAT_0087E2A0;
extern Obj_004053E0 DAT_0087E180;

// FUNCTION: GAMEMD 0x405040
void __cdecl FUN_00405040();

// ---------------------------------------------------------------------------
// 0x410170 — a constructor that installs two sets of vtable pointers.
//
// The first pair of stores to +0x08 and +0x0C is overwritten by the second set
// a few instructions later. Retail keeps both, which is the multiple-
// inheritance install pattern: the base's constructor slots are written first
// and this class's replace them. Dead stores like that survive only if the
// writes are volatile.
//
// The flag byte at +0x14 is read and masked *before* the vtable block and
// written back after it, which is why it is held in a local across the middle.
// ---------------------------------------------------------------------------
extern char VT_007E1FBC;   // VTABLE: GAMEMD 0x7E1FBC
extern char VT_007E1FB4;   // VTABLE: GAMEMD 0x7E1FB4
extern char VT_007E1F50;   // VTABLE: GAMEMD 0x7E1F50
extern char VT_007E1F34;   // VTABLE: GAMEMD 0x7E1F34
extern char VT_007E1F2C;   // VTABLE: GAMEMD 0x7E1F2C
extern char VT_007E1F24;   // VTABLE: GAMEMD 0x7E1F24

struct Obj_00410170
{
    char* vt0;        // +0x0000
    char* vt1;        // +0x0004
    char* vt2;        // +0x0008
    char* vt3;        // +0x000C
    int   field_10;   // +0x0010
    char  Flags;      // +0x0014
    char  _pad015[0x18 - 0x15];
    int   field_18;   // +0x0018
    int   field_1C;   // +0x001C
    char  field_20;   // +0x0020

    // FUNCTION: GAMEMD 0x410170
    Obj_00410170* FUN_00410170();
};
GG_STATIC_ASSERT(offsetof(Obj_00410170, Flags) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00410170, field_20) == 0x20);

#endif  // GG_MATCH_CORE_SMALL_MISC43_METHODS_H
