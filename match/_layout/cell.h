// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   CellStruct and Cell, moved out of foot_class.h unchanged so that headers
//   that only need the cell type (multiplayer_game_mode.h) need not pull in
//   the FootClass spine.
#ifndef GG_MATCH_LAYOUT_CELL_H
#define GG_MATCH_LAYOUT_CELL_H

#include "../_rt/gg_static_assert.h"
#include <stddef.h>

// CellStruct — 2D short cell coordinate (sizeof = 4). Self-guarded for reuse.
#ifndef GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02

    CellStruct operator+(CellStruct const& a) const
    {
        CellStruct ret;
        ret.X = X + a.X;
        ret.Y = Y + a.Y;
        return ret;
    }
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);
GG_STATIC_ASSERT(offsetof(CellStruct, X) == 0);
GG_STATIC_ASSERT(offsetof(CellStruct, Y) == 2);
#endif

// Cell -- the cell type RTTI names in `.?AV?$VectorClass@VCell@@@@` (table
// 0x7E38D0). Same four bytes as CellStruct; it has a constructor, so VC6
// returns it through a hidden pointer (0x50DEF0, 0x5D6890), which a plain
// CellStruct would not.
#ifndef GG_MATCH_LAYOUT_CELL_DEFINED
#define GG_MATCH_LAYOUT_CELL_DEFINED
class Cell : public CellStruct
{
public:
    Cell() {}
    // Word stores for the coordinate pair at 0x688573/0x688588.
    Cell(short x, short y) { X = x; Y = y; }
    // Element comparisons the VectorClass<Cell> table's bodies use (declared only).
    bool operator==(const Cell& other) const;
    bool operator!=(const Cell& other) const;
};
GG_STATIC_ASSERT(sizeof(Cell) == 4);
#endif

#endif  // GG_MATCH_LAYOUT_CELL_H
