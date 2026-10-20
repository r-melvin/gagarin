// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x439110. Not bound by YRpp or the seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC35_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC35_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Only four vtable slots are needed here, so the slot-shaped class is small:
// +0x08 takes two stack arguments and +0x0C takes none.
struct Node_00439110
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008(void* saved, int flag);   // +0x0008
    virtual void vt_00C();                        // +0x000C

    char  _pad04[0x4];
    void* Saved;   // +0x0008
};
GG_STATIC_ASSERT(offsetof(Node_00439110, Saved) == 0x8);

// The outer object *is* one of these and carries a second at +0x18.
struct Obj_00439110 : Node_00439110
{
    char          _pad0C[0x18 - 0x0C];
    Node_00439110 Sub;          // +0x0018
    char          _pad24[0x30 - 0x24];
    int           unknown_30;   // +0x0030

    // FUNCTION: GAMEMD 0x439110
    void FUN_00439110();
};
GG_STATIC_ASSERT(offsetof(Obj_00439110, Sub) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_00439110, unknown_30) == 0x30);

#endif  // GG_MATCH_CORE_SMALL_MISC35_METHODS_H
