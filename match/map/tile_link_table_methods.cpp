// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 over the
//   0x5A9920-0x5A9C18 run. See the header for the numeric offset derivation.
//
// The theater tile-link table's element, step and slot constructors. Bodies are
// ordered ascending by retail address.
#include "tile_link_table_methods.h"

// GLOBAL: GAMEMD 0xABE370 — the 101-slot tile-link table (0xC per slot).
// GLOBAL: GAMEMD 0xABE834 — the 8-slot continuation of the same table.

// Build a link from a cell offset and a facing.
// FUNCTION: GAMEMD 0x5A9920
TileLink::TileLink(const LinkCell& cell, int facing) throw()
    : Cell(cell), Facing(facing)
{
}

// Default link: the cell offset zeroed by LinkCell's own constructor and no
// facing yet. This is the body the array-new loops of every list constructor
// below inline.
// FUNCTION: GAMEMD 0x5A9940
TileLinkStandin::TileLinkStandin() throw()
{
    Facing = -1;
}

// Copy one link.
// FUNCTION: GAMEMD 0x5A9960
TileLink::TileLink(const TileLink& other) throw()
    : Cell(other.Cell), Facing(other.Facing)
{
}

// Build one queued walk step from its two (tile, cell) endpoints and the link
// index that produced it.
// FUNCTION: GAMEMD 0x5A9980
TileLinkStep::TileLinkStep(int fromTile, const LinkCell& fromCell, int toTile,
                           const LinkCell& toCell, int index) throw()
    : FromTile(fromTile), FromCell(fromCell), ToTile(toTile),
      ToCell(toCell), Index(index)
{
}

// Empty walk step: both endpoints are the "no tile" sentinel over a zeroed
// cell, and no link index. The two cells are assigned from temporaries rather
// than constructed in place, which is what puts the pair of stack-slot builds
// at the top of retail's body.
// FUNCTION: GAMEMD 0x5A99B0
TileLinkStep::TileLinkStep() throw()
    : FromTile(0xFFFF), FromCell(LinkCell()), ToTile(0xFFFF),
      ToCell(LinkCell()), Index(-1)
{
}

// A one-link slot.
// FUNCTION: GAMEMD 0x5A9A20
TileLinkList::TileLinkList(const TileLink& a) throw()
{
    TileIndex = 0;
    Count = 1;
    Links = new TileLink[1];
    Links[0] = a;
}

// A two-link slot.
// FUNCTION: GAMEMD 0x5A9A70
TileLinkList::TileLinkList(const TileLink& a, const TileLink& b) throw()
{
    TileIndex = 0;
    Count = 2;
    Links = new TileLink[2];
    Links[0] = a;
    Links[1] = b;
}

// A three-link slot.
// FUNCTION: GAMEMD 0x5A9AE0
TileLinkList::TileLinkList(const TileLink& a, const TileLink& b,
                           const TileLink& c) throw()
{
    TileIndex = 0;
    Count = 3;
    Links = new TileLink[3];
    Links[0] = a;
    Links[1] = b;
    Links[2] = c;
}

// A four-link slot.
// FUNCTION: GAMEMD 0x5A9B60
TileLinkList::TileLinkList(const TileLink& a, const TileLink& b,
                           const TileLink& c, const TileLink& d) throw()
{
    TileIndex = 0;
    Count = 4;
    Links = new TileLink[4];
    Links[0] = a;
    Links[1] = b;
    Links[2] = c;
    Links[3] = d;
}

// Release a slot's link array and forget it.
// FUNCTION: GAMEMD 0x5A9C00
TileLinkList::~TileLinkList() throw()
{
    delete[] Links;
    Links = 0;
}
