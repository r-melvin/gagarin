// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Shared declarations for the two cell-walk searches at 0x5835D0 and
//   0x583820. Offsets and globals are read from the entry-bounded retail
//   bodies and from the callees 0x578460, 0x481810, 0x486750 and 0x486770.
//
//   MapClass is declared here as a partial view of the map singleton at
//   0x87F7E8: the repository has no complete MapClass header yet, and other
//   translation units carry their own partial views of it.
#ifndef GG_MATCH_MAP_CELL_FLAG_SEARCH_SHARED_H
#define GG_MATCH_MAP_CELL_FLAG_SEARCH_SHARED_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"
#include "../_layout/cell_class.h"

class MapClass
{
public:
    // FUNCTION: GAMEMD 0x578460 (decl; reloc)
    // True when the cell lies inside the usable map area; the flag selects the
    // level-adjusted test. __thiscall, two stack arguments, RET 8.
    bool FUN_00578460(const CellStruct* cell, bool useLevel);

    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    // The cell object at a coordinate. __thiscall, one stack argument, RET 4.
    CellClass* FUN_005657A0(const CellStruct* cell);

    // FUNCTION: GAMEMD 0x583820
    // The nearest cell to `start` whose zone word at `zoneWordOffset` equals
    // `targetZone`, or the "no cell" coordinate. __thiscall, hidden result
    // pointer first, RET 0x10.
    Cell FUN_00583820(const CellStruct* start, int zoneWordOffset, int targetZone);

    unsigned char unknown_00[0x6C];
    int CellCount;               // +0x6C  clamp bound for the zone index
    short* ZoneWords;            // +0x70  five words per cell
    unsigned char unknown_74[0xF4 - 0x74];
    int MapWidth;                // +0xF4
    int MapHeight;               // +0xF8
};
GG_STATIC_ASSERT(offsetof(MapClass, CellCount) == 0x6C);
GG_STATIC_ASSERT(offsetof(MapClass, ZoneWords) == 0x70);
GG_STATIC_ASSERT(offsetof(MapClass, MapWidth) == 0xF4);
GG_STATIC_ASSERT(offsetof(MapClass, MapHeight) == 0xF8);

// GLOBAL: GAMEMD 0x87F7E8 -- the map singleton.
extern MapClass DAT_0087F7E8;
// GLOBAL: GAMEMD 0x87F924 -- the 512 x 512 cell pointer table.
extern CellClass** DAT_0087F924;
// GLOBAL: GAMEMD 0xABDC50 -- the cell returned for an out-of-range lookup.
extern CellClass DAT_00ABDC50;
// GLOBAL: GAMEMD 0xABDC74 -- the coordinate that failed the last lookup.
extern CellStruct DAT_00ABDC74;
// GLOBAL: GAMEMD 0xABD480 -- the "no cell" coordinate.
extern CellStruct DAT_00ABD480;
// GLOBAL: GAMEMD 0x89F688 -- the eight one-cell steps, indexed by facing.
extern const CellStruct DAT_0089F688[8];

// The cell for a coordinate, or the invalid cell (remembering the coordinate).
inline CellClass* CellAt(const CellStruct* coord)
{
    int index = coord->Y * 0x200 + coord->X;
    if (index >= 0 && index < 0x40000) {
        CellClass* cell = DAT_0087F924[index];
        if (cell)
            return cell;
    }
    DAT_00ABDC74 = *coord;
    return &DAT_00ABDC50;
}

#endif
