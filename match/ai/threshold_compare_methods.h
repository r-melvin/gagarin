// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x41F230. The jump table at 0x41F2C4 has six entries, which
//   fixes the operator range at 0..5; the sub-object's virtual is called with the
//   receiver pushed, so that interface uses __stdcall.
#ifndef GG_MATCH_AI_THRESHOLD_COMPARE_METHODS_H
#define GG_MATCH_AI_THRESHOLD_COMPARE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Sub_0041F230;

struct SubVtbl_0041F230
{
    char _pad000[0x18];                            // +0x0000
    int (__stdcall* At_18)(Sub_0041F230* self);    // +0x0018
};
GG_STATIC_ASSERT(offsetof(SubVtbl_0041F230, At_18) == 0x18);

struct Sub_0041F230 { SubVtbl_0041F230* Vptr; };

struct Node_0041F230
{
    char _pad000[0x24];        // +0x0000
    Sub_0041F230 Sub;          // +0x0024
};
GG_STATIC_ASSERT(offsetof(Node_0041F230, Sub) == 0x24);

struct Obj_0041F230
{
    char _pad000[0xE4];        // +0x0000
    int  Threshold;            // +0x00E4
    int  Op;                   // +0x00E8

    // FUNCTION: GAMEMD 0x41F230
    //
    // The first stack parameter is never read; `RET 0x8` says it is there.
    bool FUN_0041F230(int unused, Node_0041F230* node);
};
GG_STATIC_ASSERT(offsetof(Obj_0041F230, Threshold) == 0xE4);
GG_STATIC_ASSERT(offsetof(Obj_0041F230, Op) == 0xE8);

#endif  // GG_MATCH_AI_THRESHOLD_COMPARE_METHODS_H
