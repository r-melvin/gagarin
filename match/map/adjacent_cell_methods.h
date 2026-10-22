// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, the two table bases and the +0x116 / +0x28 member reads are taken
//   numerically off the user's retail gamemd.exe v1.001 through the local
//   Ghidra CLI at 0x42D490.
#ifndef GG_MATCH_MAP_ADJACENT_CELL_METHODS_H
#define GG_MATCH_MAP_ADJACENT_CELL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "pair_0042d490.h"

struct Slot_0042D490
{
    char unknown_00[0x28];    // +0x00
    Pair_0042D490 At_28;      // +0x28
};
GG_STATIC_ASSERT(offsetof(Slot_0042D490, At_28) == 0x28);

struct Found_0042D490
{
    char unknown_000[0x116];  // +0x0000
    short At_116;             // +0x0116
};
GG_STATIC_ASSERT(offsetof(Found_0042D490, At_116) == 0x116);

struct Host_0042D490
{
    // FUNCTION: GAMEMD 0x5657A0
    Found_0042D490* FUN_005657A0(Pair_0042D490* cell);
};

// GLOBAL: GAMEMD 0x87F7E8 — the singleton the lookup runs against.
extern Host_0042D490 DAT_0087F7E8;
// GLOBAL: GAMEMD 0x8B413C — table of slot pointers, indexed by the found id.
extern Slot_0042D490** DAT_008B413C;
// FUNCTION: GAMEMD 0x42D490
Pair_0042D490* __fastcall FUN_0042D490(Pair_0042D490* dest, Pair_0042D490* src,
                                       int dir);

#endif  // GG_MATCH_MAP_ADJACENT_CELL_METHODS_H
