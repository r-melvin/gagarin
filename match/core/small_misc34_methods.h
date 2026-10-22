// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x407170. Not bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC34_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC34_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// No arguments (the entry reads only the hook at 0x87E848); returns a 64-bit
// value in EDX:EAX.
__int64 __fastcall FUN_004093B0();   // GAMEMD 0x4093B0

struct Obj_00407170
{
    int  Flags;        // +0x0000
    int  unknown_04;   // +0x0004
    int  unknown_08;   // +0x0008
    char _pad0C[0x18 - 0x0C];
    __int64 unknown_18; // +0x0018: 64-bit stamp
};
GG_STATIC_ASSERT(offsetof(Obj_00407170, unknown_18) == 0x18);

// FUNCTION: GAMEMD 0x407170 — the helper the three list walks and the tail-call
// forwarders all end up in. Rearm the object at a new rate.
void __fastcall FUN_00407170c(Obj_00407170* obj, int rate);

#endif  // GG_MATCH_CORE_SMALL_MISC34_METHODS_H
