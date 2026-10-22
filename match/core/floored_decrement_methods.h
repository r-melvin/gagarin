// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and globals read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x408230.
//
// This TU is where the section 4.8 "redundant test-self after DEC" shape is
// finally reproduced, so the recipe is written out here once.
//
// Retail's shape is
//     MOV ECX,[mem] ; DEC ECX ; TEST ECX,ECX ; MOV [mem],ECX ; JGE
// - the TEST looks redundant because DEC already set SF, and every spelling
// that names the decremented value once folds it away and emits `JNS`.
//
// The source writes the decrement *twice*: once as the value stored, once
// inside the comparison. VC6 common-subexpression-eliminates the arithmetic
// down to a single `DEC`, but because the comparison is its own expression
// rather than a reference to the stored variable it still emits a fresh
// `TEST`, and the store schedules into the gap between TEST and the branch.
//
//     int v = counter;
//     counter = v - 1;
//     if (v - 1 < 0) counter = 0;
//
// What does *not* work, for the record: naming the result once
// (`int v = counter - 1; counter = v; if (v < 0)`) in any of its spellings,
// `<= -1`, `> -1`, `& 0x80000000` (emits a five-byte immediate TEST), an
// unsigned carrier with a signed test, volatile on either the store or the
// value, and every optimisation and processor-target flag the compiler
// accepts (/O1 /O2 /Ox /Og /Os /Ot /Oy- /G3 /G5 /G6 /GB all fold).
#ifndef GG_MATCH_CORE_FLOORED_DECREMENT_METHODS_H
#define GG_MATCH_CORE_FLOORED_DECREMENT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"

// GLOBAL: GAMEMD 0x87E81C — the gate; 0x87E810 is the list header itself.
extern int      DAT_0087E81C;
extern ListNode DAT_0087E810;

struct Counted_00408230
{
    ListNode Link;      // +0x0000
    char     _pad00C[0x88 - 0x0C];
    int      Counter;   // +0x0088
};
GG_STATIC_ASSERT(offsetof(Counted_00408230, Counter) == 0x88);

// FUNCTION: GAMEMD 0x408230
void __cdecl FUN_00408230();

// ---------------------------------------------------------------------------
// 0x402860 / 0x4028B0 — attach and detach, both ending in the same floored
// decrement of the owner's +0x104.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x407420 / 0x407450 — the link and unlink steps, __fastcall.
void __fastcall FUN_00407420(void* link, void* member);
void __fastcall FUN_00407450(void* self);

struct Owner_00402860
{
    char _pad000[0xF0];
    int  Attached;   // +0x00F0
    char _pad0F4[0xF8 - 0xF4];
    char Link[0x104 - 0xF8];   // +0x00F8
    int  Pending;    // +0x0104
};
GG_STATIC_ASSERT(offsetof(Owner_00402860, Attached) == 0xF0);
GG_STATIC_ASSERT(offsetof(Owner_00402860, Link) == 0xF8);
GG_STATIC_ASSERT(offsetof(Owner_00402860, Pending) == 0x104);

struct Member_00402860
{
    char              _pad000[0xAC];
    Owner_00402860*   Owner;   // +0x00AC
};
GG_STATIC_ASSERT(offsetof(Member_00402860, Owner) == 0xAC);

// FUNCTION: GAMEMD 0x402860 — attach: record the owner, count the attachment,
// raise the pending count, link, then floor it back down.
void __fastcall FUN_00402860(Owner_00402860* self, Member_00402860* member);

// FUNCTION: GAMEMD 0x4028B0 — detach: unlink, drop the attachment count, raise
// and floor the pending count with a second unlink in between.
void __fastcall FUN_004028B0(Member_00402860* self);

// The owner also carries its capacity right after the attachment count, which
// the two spawn entry points below compare against.
struct Pool_00402860
{
    char             _pad000[0xF0];
    int              Attached;   // +0x00F0
    int              Capacity;   // +0x00F4
    char             Link[0x104 - 0xF8];   // +0x00F8
    int              Pending;    // +0x0104
};
GG_STATIC_ASSERT(offsetof(Pool_00402860, Capacity) == 0xF4);
GG_STATIC_ASSERT(offsetof(Pool_00402860, Link) == 0xF8);
GG_STATIC_ASSERT(offsetof(Pool_00402860, Pending) == 0x104);

// FUNCTION: GAMEMD 0x402040 — allocate one member, __fastcall.
Member_00402860* __fastcall FUN_00402040(Pool_00402860* pool);

// FUNCTION: GAMEMD 0x4034B0 — spawn one: refuse when full, otherwise allocate,
// attach and hand it back.
Member_00402860* __fastcall FUN_004034B0(Pool_00402860* self);

// FUNCTION: GAMEMD 0x403530 — spawn up to `count`, answering how many were
// made. Stops early when the pool fills or an allocation fails.
int __fastcall FUN_00403530(Pool_00402860* self, int count);

#endif  // GG_MATCH_CORE_FLOORED_DECREMENT_METHODS_H
