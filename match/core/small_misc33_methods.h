// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x403870. Not bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC33_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC33_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A 64-bit value stored twice - as the current pair and as the original - with
// a ten-times scaling of it kept alongside. The multiply goes through the CRT's
// __allmul, which is what the four pushes around 0x7C8EC0 are.
struct Obj_00403870
{
    int Current;    // +0x0000  low half
    int CurrentHi;  // +0x0004  high half
    int Original;   // +0x0008
    int OriginalHi; // +0x000C
    char _pad10[0x20 - 0x10];
    int Scaled;     // +0x0020
    int ScaledHi;   // +0x0024

    // FUNCTION: GAMEMD 0x403870
    void FUN_00403870(int lo, int hi);
};
GG_STATIC_ASSERT(offsetof(Obj_00403870, Scaled) == 0x20);
GG_STATIC_ASSERT(offsetof(Obj_00403870, ScaledHi) == 0x24);

#endif  // GG_MATCH_CORE_SMALL_MISC33_METHODS_H
