// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every offset, element width, allocation size and sentinel below was read
//   numerically off the user's retail gamemd.exe v1.001 with the local Ghidra
//   CLI over the 0x5A9920-0x5A9C18 run. TS++ (consult-only, GPL-3.0) was read
//   for shape only; none of its text is reproduced here.
//
// The theater tile-link table at 0xABE370. The static initialiser at 0x5A9C40
// fills 109 fixed slots of 0xC bytes each -- 101 at 0xABE370..0xABE834 and 8
// more at 0xABE834..0xABE88C -- and 0x5A5020 walks those two ranges writing
// the owning tile index into each slot's +0x8 (`MOV $0xABE378,%EAX` stepping
// by 0xC until 0xABE834, then the same from 0xABE834). Each slot is a fixed
// list of one to four links; a link is a cell offset plus a facing, and the
// flood-fill walker at 0x5A89D0 consumes `Items[i].Cell` at `+0` and
// `Items[i].Facing` at `+4`, masking the facing with 7 before indexing the
// eight-way neighbour-offset table at 0x89F688. The same walker queues 0x14-byte
// steps -- two (tile index, cell) pairs plus a running index -- in a 0x400-entry
// ring, which is the second class modelled here.
//
// Confirmed numerically:
//   LinkCell        4 bytes   X @+0x0 (word), Y @+0x2 (word)
//   TileLink        8 bytes   Cell @+0x0, Facing @+0x4 (default -1)
//   TileLinkList    0xC bytes Count @+0x0, Links @+0x4, TileIndex @+0x8
//   TileLinkStep    0x14      FromTile @+0x0, FromCell @+0x4, ToTile @+0x8,
//                             ToCell @+0xC, Index @+0x10
// The list allocations are `PUSH 8 / 0x10 / 0x18 / 0x20` for one to four links,
// i.e. exactly N*8 with no array-new cookie, which pins both the element width
// at 8 and the element destructor as trivial.
#ifndef GG_MATCH_MAP_TILE_LINK_TABLE_METHODS_H
#define GG_MATCH_MAP_TILE_LINK_TABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CellStruct -- a map cell coordinate. The user-declared default constructor
// is what retail has: 0x5A9940 zeroes both words in place for a member, while
// 0x5A99B0 builds it in a stack temporary and copies the dword out, which is
// the assignment-from-temporary spelling of the same constructor.
struct LinkCell
{
    short X;   // +0x0000
    short Y;   // +0x0002
    LinkCell() throw() { X = 0; Y = 0; }
};
GG_STATIC_ASSERT(sizeof(LinkCell) == 0x4);

// One link of a tile: the neighbouring cell offset and the facing that reaches
// it. Facing defaults to -1 (`MOVL $0xFFFFFFFF,0x4(%EAX)` in 0x5A9940 and in
// the inlined array-new loops of every list constructor).
//
// The no-throw specification on every constructor was load-bearing under
// `/GX`, the tree's earlier flag set: without it the `new TileLink[n]` expressions below emit the
// unwind frame that would free the block if an element constructor threw, and
// retail has no trace of one.
struct TileLink
{
    LinkCell Cell;     // +0x0000
    int      Facing;   // +0x0004

    // FUNCTION: GAMEMD 0x5A9920
    TileLink(const LinkCell& cell, int facing) throw();
    // The default constructor has to be visible here so the `new TileLink[n]`
    // loops below expand it, which is how retail has them; the out-of-line copy
    // retail also keeps at 0x5A9940 is the layout-compatible stand-in below.
    TileLink() throw() { Facing = -1; }
    // FUNCTION: GAMEMD 0x5A9960
    TileLink(const TileLink& other) throw();
};
GG_STATIC_ASSERT(offsetof(TileLink, Cell) == 0x0 &&
                 offsetof(TileLink, Facing) == 0x4 &&
                 sizeof(TileLink) == 0x8);

// The out-of-line copy of TileLink's default constructor. cl will not emit one
// for an in-class definition it inlines everywhere, and retail has the body at
// both places, so the out-of-line form is written against a layout-compatible
// stand-in (the banked "a helper retail has both out of line and inlined needs
// both forms" rule, applied to a constructor).
struct TileLinkStandin
{
    LinkCell Cell;     // +0x0000
    int      Facing;   // +0x0004

    // FUNCTION: GAMEMD 0x5A9940
    TileLinkStandin() throw();
};
GG_STATIC_ASSERT(offsetof(TileLinkStandin, Cell) == 0x0 &&
                 offsetof(TileLinkStandin, Facing) == 0x4 &&
                 sizeof(TileLinkStandin) == 0x8);

// One queued step of the 0x5A89D0 flood fill: the tile and cell it came from,
// the tile and cell it is going to, and the running link index (-1 when none).
// 0xFFFF is the "no tile" sentinel, stored as a full dword.
struct TileLinkStep
{
    int      FromTile;   // +0x0000
    LinkCell FromCell;   // +0x0004
    int      ToTile;     // +0x0008
    LinkCell ToCell;     // +0x000C
    int      Index;      // +0x0010

    // FUNCTION: GAMEMD 0x5A9980
    TileLinkStep(int fromTile, const LinkCell& fromCell, int toTile,
                 const LinkCell& toCell, int index) throw();
    // FUNCTION: GAMEMD 0x5A99B0
    TileLinkStep() throw();
};
GG_STATIC_ASSERT(offsetof(TileLinkStep, FromTile) == 0x0 &&
                 offsetof(TileLinkStep, FromCell) == 0x4 &&
                 offsetof(TileLinkStep, ToTile) == 0x8 &&
                 offsetof(TileLinkStep, ToCell) == 0xC &&
                 offsetof(TileLinkStep, Index) == 0x10 &&
                 sizeof(TileLinkStep) == 0x14);

// One slot of the 0xABE370 table: a heap array of exactly Count links, plus the
// tile index 0x5A5020 stamps into +0x8 afterwards. The four constructors are
// the four arities the initialiser uses; there is no default constructor and no
// copy, because the table is filled in place.
struct TileLinkList
{
    int       Count;       // +0x0000
    TileLink* Links;       // +0x0004
    int       TileIndex;   // +0x0008

    // FUNCTION: GAMEMD 0x5A9A20
    TileLinkList(const TileLink& a) throw();
    // FUNCTION: GAMEMD 0x5A9A70
    TileLinkList(const TileLink& a, const TileLink& b) throw();
    // FUNCTION: GAMEMD 0x5A9AE0
    TileLinkList(const TileLink& a, const TileLink& b,
                 const TileLink& c) throw();
    // FUNCTION: GAMEMD 0x5A9B60
    TileLinkList(const TileLink& a, const TileLink& b, const TileLink& c,
                 const TileLink& d) throw();
    // FUNCTION: GAMEMD 0x5A9C00
    ~TileLinkList() throw();
};
GG_STATIC_ASSERT(offsetof(TileLinkList, Count) == 0x0 &&
                 offsetof(TileLinkList, Links) == 0x4 &&
                 offsetof(TileLinkList, TileIndex) == 0x8 &&
                 sizeof(TileLinkList) == 0xC);

#endif  // GG_MATCH_MAP_TILE_LINK_TABLE_METHODS_H
