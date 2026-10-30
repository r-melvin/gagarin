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
    // FUNCTION: GAMEMD 0x453240 (decl; reloc) -- thiscall on the cell value.
    void FUN_00453240();
    // FUNCTION: GAMEMD 0x660B80 (decl; reloc) -- thiscall on the cell value.
    void FUN_00660B80();
    // FUNCTION: GAMEMD 0x42D510 (decl; reloc) -- this offset plus `base`, returned by value through a hidden pointer.
    class Cell FUN_0042D510(const CellStruct& base) const;
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);
GG_STATIC_ASSERT(offsetof(CellStruct, X) == 0);
GG_STATIC_ASSERT(offsetof(CellStruct, Y) == 2);

// Member-wise cell comparison (two 16-bit compares), as the inlined vector searches and coordinate
// tests expand it.
inline bool operator==(CellStruct const& a, CellStruct const& b)
{
    return a.X == b.X && a.Y == b.Y;
}
inline bool operator!=(CellStruct const& a, CellStruct const& b)
{
    return !(a == b);
}
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
    // The element comparison reads both signed-short coordinates (0x42F7F0/0x42F930).
    bool operator==(const Cell& other) const { return X == other.X && Y == other.Y; }
    bool operator!=(const Cell& other) const { return !(*this == other); }
};
GG_STATIC_ASSERT(sizeof(Cell) == 4);
GG_STATIC_ASSERT(offsetof(Cell, X) == 0);
GG_STATIC_ASSERT(offsetof(Cell, Y) == 2);

// GLOBAL: GAMEMD 0xA8EF98 -- the (0, 0) "no cell" sentinel; defined by the header
// static initialiser at 0x4F50A0 (match/core/header_init_4f4ee0.cpp).
extern Cell DAT_00A8EF98;
#endif

#endif  // GG_MATCH_LAYOUT_CELL_H
