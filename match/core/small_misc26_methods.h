// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC26_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC26_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A per-mille scale done in 64-bit: the value is sign-extended, multiplied by
// 1000 and divided by the divisor, with the CRT's __allmul and __alldiv doing
// the work. That is what the CDQ/push-pair sequences around 0x7C8EC0 and
// 0x7C9380 are, and it is why the result comes back in EDX:EAX.
struct Obj_00408560
{
    char _pad00[0x14];
    int  Divisor;   // +0x0014

    // FUNCTION: GAMEMD 0x408560
    __int64 __fastcall FUN_00408560(int value) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00408560, Divisor) == 0x14);

struct Rec_00433C30 { char _pad00[0x4]; int at04; char _pad08[0x4]; int at0C; };
struct Src_00433C30 { Rec_00433C30* FUN_00433990(); };   // GAMEMD 0x433990

struct Obj_00433C30;
void FUN_00434700(Obj_00433C30* self);   // GAMEMD 0x434700

struct Obj_00433C30
{
    char           _pad00[0x4];
    Rec_00433C30*  unknown_04;   // +0x0004
    char           _pad08[0x18 - 0x08];
    int            unknown_18;   // +0x0018
    int            unknown_1C;   // +0x001C

    // FUNCTION: GAMEMD 0x433C30
    bool FUN_00433C30(Src_00433C30* src);
};
GG_STATIC_ASSERT(offsetof(Obj_00433C30, unknown_1C) == 0x1C);

#endif  // GG_MATCH_CORE_SMALL_MISC26_METHODS_H
