// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4072E0: `[ESI]` / `[ESI+4]` are the two links and
//   `[ESI+8]` the ordering key.
#ifndef GG_MATCH_CORE_SORTED_LIST_INSERT_METHODS_H
#define GG_MATCH_CORE_SORTED_LIST_INSERT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A circular doubly-linked node. The key doubles as the end marker: the list's
// terminating node stores its own address there, which is what the
// `CMP ESI,EBX` at 0x4072F3 tests.
struct Node_004072E0
{
    Node_004072E0* Next;   // +0x0000
    Node_004072E0* Prev;   // +0x0004
    // volatile: the stream thread 0x407680 (CreateThread @0x407610) walks the
    // list at 0x87E810 with 0x4073C0/0x4073E0 (called @0x4076C0, @0x407730),
    // which read +0x8 at 0x4073CA/0x4073EA; 0x4072D0 writes it on this side.
    volatile int   Key;    // +0x0008
};
GG_STATIC_ASSERT(offsetof(Node_004072E0, Prev) == 0x4);
GG_STATIC_ASSERT(offsetof(Node_004072E0, Key) == 0x8);

// FUNCTION: GAMEMD 0x4072E0
int FUN_004072E0(Node_004072E0* list, Node_004072E0* node);

#endif  // GG_MATCH_CORE_SORTED_LIST_INSERT_METHODS_H
