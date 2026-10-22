// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x45ADD0. Not bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC25_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC25_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Remove by index: drop the count first, then slide the tail down one slot.
// The items pointer is re-read from the object on every iteration
// (`MOV EDX,[ECX+4]` sits inside the loop), so the source indexes through the
// member rather than a hoisted local - the same shape as MatrixApply's copy.
struct Vector_0045ADD0
{
    char   _pad00[0x4];
    void** Items;   // +0x0004
    char   _pad08[0x10 - 0x08];
    int    Count;   // +0x0010

    // FUNCTION: GAMEMD 0x45ADD0
    bool FUN_0045ADD0(int index);
    // FUNCTION: GAMEMD 0x45AE10 — byte-identical on a second vector type,
    // written out longhand per the family rule.
    bool FUN_0045AE10(int index);
};
GG_STATIC_ASSERT(offsetof(Vector_0045ADD0, Count) == 0x10);


// Two floored decrements in sequence: the object's own counter and one on the
// record it points at. Neither is allowed below zero.
struct Owner_00408E70 { char _pad[0x98]; int at98; };

struct Obj_00408E70
{
    Owner_00408E70* Owner;        // +0x0000
    char            _pad04[0x1C - 0x04];
    int             unknown_1C;   // +0x001C

    // FUNCTION: GAMEMD 0x408E70
    void FUN_00408E70();
};
GG_STATIC_ASSERT(offsetof(Obj_00408E70, unknown_1C) == 0x1C);

#endif  // GG_MATCH_CORE_SMALL_MISC25_METHODS_H
