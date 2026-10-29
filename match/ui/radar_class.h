// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA; address-scoped helper used by Radar.CPP.
#ifndef GG_MATCH_UI_RADAR_CLASS_H
#define GG_MATCH_UI_RADAR_CLASS_H

#include <stddef.h>
#include "input_controls/ui_display_chain.h"

// Radar's tracking-list cell has the same two-short ABI as CellStruct. Keep a
// distinct value type because its nontrivial default constructor is part of
// the recovered by-value return convention in SetVisibleRect.
#include "../_layout/cell_0050def0.h"

struct RadarTrackNode
{
    char _pad[0x24];
    Cell_0050DEF0 Cell;

    Cell_0050DEF0 GetCell() const
    {
        Cell_0050DEF0 result = Cell;
        return result;
    }
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(RadarTrackNode, Cell) == 0x24);
#endif

// GLOBAL: GAMEMD 0x87F7E8
extern RadarClass Instance;

#endif
