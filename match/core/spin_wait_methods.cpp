// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4070B0 and 0x4080F0.

#include "spin_wait_methods.h"

// FUNCTION: GAMEMD 0x4070B0
void FUN_004070B0(Queue_004070B0* self)
{
    unsigned __int64 deadline = FUN_004093B0() + self->Interval;

    while (self->Head != self->Tail) {
        if (FUN_004093B0() >= deadline) {
            break;
        }

        FUN_0048D080();
    }
}

// FUNCTION: GAMEMD 0x4080F0
//
// Written out longhand rather than shared with the sibling: the guard has an
// extra flag term and the cursors are one indirection further away, and retail
// re-reads the inner pointer on each pass.
//
// The guard is written as `while (1) { if (!(whole conjunction)) break; ... }`,
// with the negation wrapping both clauses together. That is what gives retail's
// single copy of the head test at 0x408107 and the unconditional `JMP 0x408107`
// back edge. Written as a plain `while` over the same conjunction, cl 8804
// duplicates `TEST byte ptr [ESI+0xC],1; JNE` at the back edge, which also
// hoists the flag byte load into the prologue and splits retail's
// `ADC EDI,dword ptr [EAX+0x24]` into `MOV ECX,..; ADC EDI,ECX` — that whole
// residual was one rotation, and it scored 28.1%. Earlier passes had recorded
// it as the 8447-vs-8804 "loop-head duplication at a back edge" class after ten
// phrasings (the inner pointer in a local, the flag as `char` and as `int`,
// byte-cast and volatile-byte-cast reads, a `for (;;)` with individual breaks,
// the reading hoisted into its own local, the addition the other way round, a
// label/`goto again` loop, and `volatile char` on the flag member); it was a
// phrasing lever, and the same one that cracked 0x40E3E0, 0x505360 and
// 0x526CC0.
//
// Also 100% and measured in the same batch: the deadline test negated whole
// (`if (!(FUN_004093B0() < deadline)) break;`) and the flag read without the
// unsigned-char cast. Re-reading the inner pointer into a local inside the
// guard is 33.3%, so the two reads of `self->Inner` stay in the guard.
void FUN_004080F0(Outer_004080F0* self)
{
    unsigned __int64 deadline = FUN_004093B0() + self->Inner->Interval;

    while (1) {
        if (!((*(unsigned char*)&self->Flags & 1)
              && self->Inner->Head != self->Inner->Tail)) {
            break;
        }

        if (FUN_004093B0() >= deadline) {
            break;
        }

        FUN_0048D080();
    }
}
