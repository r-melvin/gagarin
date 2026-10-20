// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4087F0.

#include <string.h>
#include "slot_array_factory_methods.h"

#pragma intrinsic(memset)

// FUNCTION: GAMEMD 0x4087F0
//
// Allocate an owner, zero it whole, then walk its two slots giving each one a
// back-pointer and its own index.
//
// PARTIAL (86.2%, 25/29; was 72.4%). The instruction multiset is identical and
// only two adjacent pairs are swapped.
//
// The lever was the loop cursor's base. Retail bases it at slot+0x24
// (`LEA EAX,[ESI+0x3C]`, the address of `field_24`) and reaches the other four
// fields at -0x24/-0x8/-0x10/-0xC; cl bases it at slot+0x1C and reaches the
// same five at -0x1C/0/-0x8/+0x8/-0x4. Both are disp8-reachable, so nothing in
// the encoding forces either, and it is not selectable from any spelling that
// names the slot: array indexing, a `Slot*` cursor advanced in the loop header,
// a pointer or a reference taken inside the body, a `do`-while, the per-slot
// stores lifted into a free function taking the slot, and the same lifted into
// a member of the slot all produce cl's base (72.4%). Writing the cursor as the
// address of `field_24` itself, with the other four fields reached at their
// offsets relative to it, gives retail's base and every store lines up: 82.8%.
// Declaring the loop counter ahead of the cursor adds the `LEA` landing after
// the `field_98` store: 86.2%.
//
// The two residual swaps are scheduling. Retail stores `field_98` and then
// zeroes the counter, cl zeroes the counter first; and retail bumps the counter
// before advancing the cursor, cl advances first. Measured against both, all
// 82.8%-86.2%: the `field_98` store through a named zero local, that zero
// shared with the body's three zero stores, the cursor advance moved into the
// increment clause after `i++`, the counter bumped inside the body ahead of the
// advance, a top-tested `while`, a `while (1)` with the test at the bottom
// (75.9%), the cursor declared before the counter (79.3%), and `i != 2` for the
// bound. Nothing reorders either pair.
//
// PERMUTER FINDING (negative, and a confirmation of the batch-fifty-eight
// screen). decomp-permuter, base score 120 against a floor of ZERO -- apart
// from its two calls the body is relocation-free, insertions = deletions = 0,
// and the whole delta is the two transpositions above. 116,148 candidates
// across two runs moved it not one point; every output it wrote was
// equal-scoring.
//
// This is the cleanest confirmation the screen has, because both halves of the
// residual sit in the two classes batch fifty-eight says not to run: the
// `field_98` store races a rematerialised `XOR ECX,ECX`, and `INC ECX` against
// `ADD EAX,0x40` is induction-variable scheduling inside a loop. One refinement
// is worth recording -- the counter's zero here DOES have a source-visible
// producer (`int i = 0`), unlike 0x410170's, and it made no difference. The
// class is about where the constant LANDS, not about whether the source can
// name it.
//
// The per-slot zero stores are redundant after the memset and retail emits
// them anyway, so they are in the source rather than folded away.
// The cursor's base is `field_24`; the other four fields are reached at their
// own offsets relative to it, which is what retail's negative displacements
// off `LEA EAX,[ESI+0x3C]` are.
#define GG_SLOT_FIELD(cur, T, M) \
    (*(T*)((char*)(cur) \
           + (int)(offsetof(Slot_004087F0, M) - offsetof(Slot_004087F0, field_24))))

Owner_004087F0* __fastcall FUN_004087F0()
{
    Owner_004087F0* self = (Owner_004087F0*)FUN_007C8E17(sizeof(Owner_004087F0));
    memset(self, 0, sizeof(Owner_004087F0));

    FUN_004072C0(self->Embedded);
    self->field_98 = 0;

    int i = 0;
    int* cur = &self->Slots[0].field_24;
    for (; i < 2; i++) {
        GG_SLOT_FIELD(cur, Owner_004087F0*, Owner) = self;
        GG_SLOT_FIELD(cur, int, field_1C)          = 0;
        GG_SLOT_FIELD(cur, int, Index)             = i;
        *cur                                       = 0;
        GG_SLOT_FIELD(cur, int, field_18)          = 0;
        cur = (int*)((char*)cur + sizeof(Slot_004087F0));
    }

    return self;
}
