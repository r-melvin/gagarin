// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and call targets read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x4070B0 and 0x4080F0.
//
// Two bounded spin-waits. Both take a 64-bit reading from 0x4093B0, add an
// interval to it to get a deadline, and then yield through 0x48D080 until
// either the guarded condition clears or the deadline passes.
//
// The deadline comparison is `CMP EDX,EDI; JA out; JC in; CMP EAX,EBX; JNC out`
// - the three-branch form of an *unsigned* 64-bit `>`, so both operands are
// `unsigned __int64` rather than signed.
#ifndef GG_MATCH_CORE_SPIN_WAIT_METHODS_H
#define GG_MATCH_CORE_SPIN_WAIT_METHODS_H

#include <stddef.h>
#include "triple_timer_init_methods.h"
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x48D080 — the yield, no arguments.
void FUN_0048D080();

// ---------------------------------------------------------------------------
// 0x4070B0 — wait while a pair of cursors disagree.
// ---------------------------------------------------------------------------
struct Queue_004070B0
{
    char             _pad000[0x4];
    int              Head;      // +0x0004
    int              Tail;      // +0x0008
    char             _pad00C[0x4];
    unsigned __int64 Interval;  // +0x0010
};
GG_STATIC_ASSERT(offsetof(Queue_004070B0, Tail) == 0x8);
GG_STATIC_ASSERT(offsetof(Queue_004070B0, Interval) == 0x10);

// FUNCTION: GAMEMD 0x4070B0
void FUN_004070B0(Timer_00401000* self);

// ---------------------------------------------------------------------------
// 0x4080F0 — the same wait one level down: the cursors and the interval live on
// the object at +0x14, and an extra flag bit at +0x0C arms the whole thing.
// ---------------------------------------------------------------------------
struct Inner_004080F0
{
    char             _pad000[0x14];
    int              Head;      // +0x0014
    int              Tail;      // +0x0018
    char             _pad01C[0x4];
    unsigned __int64 Interval;  // +0x0020
};
GG_STATIC_ASSERT(offsetof(Inner_004080F0, Tail) == 0x18);
GG_STATIC_ASSERT(offsetof(Inner_004080F0, Interval) == 0x20);

struct Outer_004080F0
{
    char            _pad000[0xC];
    char            Flags;   // +0x000C
    char            _pad00D[0x14 - 0xD];
    Inner_004080F0* Inner;   // +0x0014
};
GG_STATIC_ASSERT(offsetof(Outer_004080F0, Flags) == 0xC);
GG_STATIC_ASSERT(offsetof(Outer_004080F0, Inner) == 0x14);

// FUNCTION: GAMEMD 0x4080F0
void FUN_004080F0(Outer_004080F0* self);

#endif  // GG_MATCH_CORE_SPIN_WAIT_METHODS_H
