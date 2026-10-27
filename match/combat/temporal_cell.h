// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA, FUN_0065FA70 entry and callers.
// The by-value cell argument is two 16-bit coordinates (four stack bytes).
#ifndef GG_MATCH_COMBAT_TEMPORAL_CELL_H
#define GG_MATCH_COMBAT_TEMPORAL_CELL_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct TemporalCell
{
    short X;
    short Y;
};

GG_STATIC_ASSERT(offsetof(TemporalCell, X) == 0x00);
GG_STATIC_ASSERT(sizeof(((TemporalCell*)0)->X) == 2);
GG_STATIC_ASSERT(offsetof(TemporalCell, Y) == 0x02);
GG_STATIC_ASSERT(sizeof(((TemporalCell*)0)->Y) == 2);
GG_STATIC_ASSERT(sizeof(TemporalCell) == 4);

#endif  // GG_MATCH_COMBAT_TEMPORAL_CELL_H
