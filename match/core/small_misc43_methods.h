// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, vtable addresses and masks read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at the annotated ring/pause methods.
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

#endif  // GG_MATCH_CORE_SMALL_MISC43_METHODS_H
