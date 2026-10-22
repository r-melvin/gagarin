// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RE-findings-cross-check
//   Bytes and offsets from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (0x486750, 0x486770, 0x486790).
//
//   Receiver: the cell. `[ECX+0x38]` is IsoTileTypeIndex, which is the offset
//   already pinned in this tree by match/map/cell_class_tiberium_germinate_
//   methods.h (`Cell_004838E0::IsoTileTypeIndex == 0x38`), and the three bodies
//   here sit in the 0x486xxx CellClass run.
//
//   The disassembly shows 0x00486750 testing the half-open iso-tile range
//   [0xAA0E28, +0x10) and 0x00486770 the range [0xABAD1C, +0x10).
//
//   0x00486790 is a third sibling, found by
//   reading on past 0x486770: the same range test against 0x00AA0E24, with no
//   "-1 means no such tile set" guard.
//
//   Each body reads its own base global, so each gets its own extern; the
//   differ normalises the relocation and separate declarations stop one
//   instance claiming another's address.
#ifndef GG_MATCH_MAP_CELL_CLASS_BRIDGE_TILE_QUERIES_H
#define GG_MATCH_MAP_CELL_CLASS_BRIDGE_TILE_QUERIES_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xAA0E28 — first iso-tile index of the concrete bridge set.
extern int GgBridgeTileBase;
// GLOBAL: GAMEMD 0xABAD1C — first iso-tile index of the wood bridge set.
extern int GgWoodBridgeTileBase;
// GLOBAL: GAMEMD 0xAA0E24 — first iso-tile index of the set 0x486790 tests.
extern int GgTileBase_00AA0E24;

class CellClass
{
public:
    // Declared ascending by retail address (reccmp/isle TU discipline).
    bool IsBridgeTile();          // GAMEMD 0x486750
    bool IsWoodBridgeTile();      // GAMEMD 0x486770
    bool IsTileInSet00AA0E24();   // GAMEMD 0x486790

    char _pad_000[0x38];      // +0x00
    int  IsoTileTypeIndex;    // +0x38
};
GG_STATIC_ASSERT(offsetof(CellClass, IsoTileTypeIndex) == 0x38);

#endif // GG_MATCH_MAP_CELL_CLASS_BRIDGE_TILE_QUERIES_H
