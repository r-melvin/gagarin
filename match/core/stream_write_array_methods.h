// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, slot displacements and argument slots read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x43A770.
//
// Serialise a counted array: write the count, then let each element write
// itself through its own slot +0x18. The same ISequentialStream shape as the
// 0x410320 pair - receiver pushed, `Write` at +0x10 - and the same
// parameter-home staging: the count is stashed in the *stream* argument's own
// stack slot, whose address is what the write receives, and read back from
// there afterwards as the loop bound.
//
// A zero count still succeeds: the loop guard skips straight to `XOR EAX,EAX`.
#ifndef GG_MATCH_CORE_STREAM_WRITE_ARRAY_METHODS_H
#define GG_MATCH_CORE_STREAM_WRITE_ARRAY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Stream_0043A770;
struct Element_0043A770;

typedef long (__stdcall* StreamWrite_0043A770)(Stream_0043A770*, void*,
                                               unsigned long, unsigned long*);
typedef long (__stdcall* ElementSave_0043A770)(Element_0043A770*,
                                               Stream_0043A770*, void*);

#define STREAM_WRITE_0043A770(s, p, n) \
    ((*(StreamWrite_0043A770*)(*(char**)(s) + 0x10))(s, p, n, 0))
#define ELEMENT_SAVE_0043A770(e, s, c) \
    ((*(ElementSave_0043A770*)(*(char**)(e) + 0x18))(e, s, c))

struct Owner_0043A770
{
    char               _pad000[0x8];
    Element_0043A770** Items;   // +0x0008
    char               _pad00C[0x14 - 0x0C];
    int                Count;   // +0x0014

    // FUNCTION: GAMEMD 0x43A770
    long FUN_0043A770(Stream_0043A770* stream, void* context);
};
GG_STATIC_ASSERT(offsetof(Owner_0043A770, Items) == 0x8);
GG_STATIC_ASSERT(offsetof(Owner_0043A770, Count) == 0x14);

// ---------------------------------------------------------------------------
// 0x413850 — the bulk form: 400 counted int arrays, each written count-first.
//
// The vectors are 0x18 bytes apart starting at `this + 4`, with the payload
// pointer at +0x00 and the count at +0x0C. The count is staged in the stream
// argument's stack home exactly as above, and because its address escapes into
// the write the inner loop re-reads it as the bound on every pass.
//
// 0x190 is 400 and the stride is 0x18, both read straight off the outer loop.
// ---------------------------------------------------------------------------
struct IntVector_00413850
{
    int* Items;   // +0x0000
    char _pad004[0xC - 0x4];
    int  Count;   // +0x000C
    char _pad010[0x18 - 0x10];
};
GG_STATIC_ASSERT(sizeof(IntVector_00413850) == 0x18);
GG_STATIC_ASSERT(offsetof(IntVector_00413850, Count) == 0xC);

struct Owner_00413850
{
    char              _pad000[0x4];
    IntVector_00413850 Vectors[0x190];   // +0x0004

    // FUNCTION: GAMEMD 0x413850
    long FUN_00413850(Stream_0043A770* stream);
};
GG_STATIC_ASSERT(offsetof(Owner_00413850, Vectors) == 0x4);

#endif  // GG_MATCH_CORE_STREAM_WRITE_ARRAY_METHODS_H
