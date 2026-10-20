// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, the two table bases and the +0x116 / +0x28 member reads are taken
//   numerically off the user's retail gamemd.exe v1.001 through the local
//   Ghidra CLI at 0x42D490.
#ifndef GG_MATCH_MAP_ADJACENT_CELL_METHODS_H
#define GG_MATCH_MAP_ADJACENT_CELL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Two 16-bit components packed in one dword — retail copies the pair with a
// single 32-bit move, which is why the halves are written to a temporary first.
struct Pair_0042D490
{
    short X;                  // +0x00
    short Y;                  // +0x02
};
GG_STATIC_ASSERT(sizeof(Pair_0042D490) == 4);

struct Slot_0042D490
{
    char _pad0000[0x28];      // +0x00
    Pair_0042D490 At_28;      // +0x28
};
GG_STATIC_ASSERT(offsetof(Slot_0042D490, At_28) == 0x28);

struct Found_0042D490
{
    char _pad0000[0x116];     // +0x0000
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
// GLOBAL: GAMEMD 0x89F688 — per-direction step table.
extern Pair_0042D490 DAT_0089F688[];

// FUNCTION: GAMEMD 0x42D490
Pair_0042D490* __fastcall FUN_0042D490(Pair_0042D490* dest, Pair_0042D490* src,
                                       int dir);

#endif  // GG_MATCH_MAP_ADJACENT_CELL_METHODS_H
