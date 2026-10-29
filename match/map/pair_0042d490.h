// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001; two 16-bit values are copied as one
// dword by the entry at 0x42D490, and the table base is read at 0x89F688.
#ifndef GG_MATCH_MAP_PAIR_0042D490_H
#define GG_MATCH_MAP_PAIR_0042D490_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/cell_step_tables.h"

struct Pair_0042D490
{
    short X;                  // +0x00
    short Y;                  // +0x02
};
GG_STATIC_ASSERT(offsetof(Pair_0042D490, X) == 0x00);
GG_STATIC_ASSERT(offsetof(Pair_0042D490, Y) == 0x02);
GG_STATIC_ASSERT(sizeof(Pair_0042D490) == 0x04);

#endif  // GG_MATCH_MAP_PAIR_0042D490_H
