// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x41DC80. The walk is bounded at 0x65 iterations
//   (`CMP EDI,0x64; JG`), which is the queue's own safety limit rather than a
//   count of anything.
#ifndef GG_MATCH_AI_QUEUE_UNLINK_METHODS_H
#define GG_MATCH_AI_QUEUE_UNLINK_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — the engine frame counter.
#include "../core/frame_counter.h"

struct Node_0041DC80
{
    char _pad000[0x294];        // +0x0000
    int  At_294;                // +0x0294  cleared once unlinked
    char _pad298[0x340];        // +0x0298
    Node_0041DC80* Next;        // +0x05D8
};
GG_STATIC_ASSERT(offsetof(Node_0041DC80, At_294) == 0x294);
GG_STATIC_ASSERT(offsetof(Node_0041DC80, Next) == 0x5D8);

struct Owner_0041DC80
{
    char _pad000[0x30];         // +0x0000
    int  Active;                // +0x0030  how many nodes are linked
    char _pad034[0x8];          // +0x0034
    char field_3C;              // +0x003C
    char field_3D;              // +0x003D
    char _pad03E[0x2];          // +0x003E
    int  field_40;              // +0x0040  stamped with the frame counter
    char _pad044[0x18];         // +0x0044
    Node_0041DC80* Head;        // +0x005C

    // FUNCTION: GAMEMD 0x41DC80 — a member, not a free __fastcall: retail reads
    // the node from `[ESP+4]` at 0x41DC83, so only the receiver is in a
    // register.
    void FUN_0041DC80(Node_0041DC80* node);
};
GG_STATIC_ASSERT(offsetof(Owner_0041DC80, Active) == 0x30);
GG_STATIC_ASSERT(offsetof(Owner_0041DC80, field_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(Owner_0041DC80, field_40) == 0x40);
GG_STATIC_ASSERT(offsetof(Owner_0041DC80, Head) == 0x5C);

#endif  // GG_MATCH_AI_QUEUE_UNLINK_METHODS_H
