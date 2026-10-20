// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x438060. Not bound by YRpp or the seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC30_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC30_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Flush a pending buffer and then whatever the sink itself owes, returning the
// combined byte count. Both calls are __thiscall on this object.
struct Obj_00438060
{
    char _pad00[0xC];
    int  unknown_0C;   // +0x000C
    char Pending[8];   // +0x0010
    int  PendingLen;   // +0x0018

    // Declared only.
    int FUN_00631D10(const void* block, int length);   // GAMEMD 0x631D10
    int FUN_00631D30();                                // GAMEMD 0x631D30

    // FUNCTION: GAMEMD 0x438060
    int FUN_00438060();
};
GG_STATIC_ASSERT(offsetof(Obj_00438060, Pending) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_00438060, PendingLen) == 0x18);

#endif  // GG_MATCH_CORE_SMALL_MISC30_METHODS_H
