// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every offset below was read numerically off the user's retail gamemd.exe
//   v1.001 with the local Ghidra CLI at 0x56EF50 / 0x56F8B0 and their six
//   siblings. On the cell: `[ESI+0x24]` the map coords handed to the map's
//   redraw helper, `[ESI+0x38]` the iso-tile index differenced against the
//   global tile base, `[ESI+0x44]` a dword reset to -1, `[ESI+0x11A]` the
//   sub-tile selector (tested `&1` by the 917-byte shape and `>4` by the
//   964-byte one), `[ESI+0x11B]` the sub-tile ordinal that becomes the last
//   argument minus four, `[ESI+0x11E]` the overlay-type index, and
//   `[ESI+0x140]` the flag byte whose 0x80 bit gates the whole bridge block.
//   The cell lookup is the tree's already-established inline expansion:
//   `MOVSX [c+2] << 9 + MOVSX [c]`, bounded by 0x40000, through the global
//   cell array at 0x87F924 (= the map instance 0x87F7E8 + 0x13C), falling
//   back to the invalid cell at 0xABDC50 whose coords sit at 0xABDC74.
//   These functions carry no name in the binary and none in the YRpp map, so
//   they keep address-tagged placeholder names.
#ifndef GG_MATCH_MAP_BRIDGE_SPAN_COLLAPSE_FAMILY_METHODS_H
#define GG_MATCH_MAP_BRIDGE_SPAN_COLLAPSE_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4): X@0, Y@2.
struct BridgeCellStruct
{
    short X;  // +0x00
    short Y;  // +0x02

    // FUNCTION: GAMEMD 0x42D510 (decl; reloc) — CellStruct::operator+, the
    // MSVC named-return form: hidden result pointer pushed after the operand.
    BridgeCellStruct operator+(BridgeCellStruct const& offset) const;
};
GG_STATIC_ASSERT(sizeof(BridgeCellStruct) == 4 &&
                 offsetof(BridgeCellStruct, X) == 0 &&
                 offsetof(BridgeCellStruct, Y) == 2);

struct BridgeCellClass
{
    char             _pad000[0x24];   // +0x0000
    BridgeCellStruct MapCoords;       // +0x0024
    char             _pad028[0x10];   // +0x0028
    int              TileIndex;       // +0x0038
    char             _pad03C[0x8];    // +0x003C
    int              Field44;         // +0x0044
    char             _pad048[0xD2];   // +0x0048
    unsigned char    SubTileFlags;    // +0x011A
    signed char      SubTileOrdinal;  // +0x011B
    char             _pad11C[0x2];    // +0x011C
    unsigned char    OverlayTypeIndex;// +0x011E
    char             _pad11F[0x21];   // +0x011F
    unsigned char    Flags140;        // +0x0140

    // FUNCTION: GAMEMD 0x47DD70 (decl; reloc) — the cell's redraw/mark helper.
    void Touch();
    // FUNCTION: GAMEMD 0x47E470 (decl; reloc) — the cell's overlay detach.
    void DetachOverlay(int kind, int flag);
};
GG_STATIC_ASSERT(offsetof(BridgeCellClass, MapCoords) == 0x24 &&
                 offsetof(BridgeCellClass, TileIndex) == 0x38 &&
                 offsetof(BridgeCellClass, Field44) == 0x44 &&
                 offsetof(BridgeCellClass, SubTileFlags) == 0x11A &&
                 offsetof(BridgeCellClass, SubTileOrdinal) == 0x11B &&
                 offsetof(BridgeCellClass, OverlayTypeIndex) == 0x11E &&
                 offsetof(BridgeCellClass, Flags140) == 0x140);

struct BridgeMapClass
{
    char              _pad000[0x13C];  // +0x0000
    BridgeCellClass** Cells;           // +0x013C

    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt, the
    // out-of-line copy retail keeps for the two call sites cl declined.
    BridgeCellClass* GetCellAt(BridgeCellStruct const& coord) const;
    // FUNCTION: GAMEMD 0x6551C0 (decl; reloc) — the map's cell redraw request.
    void RedrawCell(BridgeCellStruct const& coord);
};
GG_STATIC_ASSERT(offsetof(BridgeMapClass, Cells) == 0x13C);

// GLOBAL: GAMEMD 0x87F7E8 — the map instance; its Cells member is 0x87F924.
extern BridgeMapClass MapInstance;
// GLOBAL: GAMEMD 0xABDC50 — the invalid cell; its MapCoords is 0xABDC74.
extern BridgeCellClass InvalidCell;
// GLOBAL: GAMEMD 0x89F688 — the eight adjacent-cell offsets, indexed by facing.
extern const BridgeCellStruct AdjacentCellOffset[8];

// The bounds-checked cell lookup, expanded at every site retail expanded it.
// A macro rather than an inline function: the body uses it seven times and the
// frame-slot reuse retail shows depends on the expansion being unconditional.
#define GG_BRIDGE_CELL_AT(dst, coord)                                      \
    do {                                                                    \
        int ggIndex = ((coord).Y << 9) + (coord).X;                         \
        if (ggIndex >= 0 && ggIndex < 0x40000 &&                            \
            MapInstance.Cells[ggIndex] != 0) {                              \
            dst = MapInstance.Cells[ggIndex];                               \
        } else {                                                            \
            InvalidCell.MapCoords = (coord);                                \
            dst = &InvalidCell;                                             \
        }                                                                   \
    } while (0)

// The walker that owns the family. `this` is only ever a receiver for the two
// sibling helpers and for the recursion; no member of it is read.
struct BridgeSpanWalker
{
    // FUNCTION: GAMEMD 0x56E990 (decl; reloc)
    void MarkSpan(BridgeCellStruct& coord, int a, int b);
    // FUNCTION: GAMEMD 0x56EB80 (decl; reloc)
    void PlaceSpan(BridgeCellStruct& coord, int tile, int a, int b, int c);

    void Collapse_0056EF50(BridgeCellStruct* cell, unsigned facing);
    void Collapse_0056F2F0(BridgeCellStruct* cell, unsigned facing);
    void Collapse_0056F8B0(BridgeCellStruct* cell, unsigned facing);
    void Collapse_0056FC80(BridgeCellStruct* cell, unsigned facing);
    void Collapse_00572440(BridgeCellStruct* cell, unsigned facing);
    void Collapse_005727E0(BridgeCellStruct* cell, unsigned facing);
    void Collapse_00572DA0(BridgeCellStruct* cell, unsigned facing);
    void Collapse_00573170(BridgeCellStruct* cell, unsigned facing);
};

// Per-instance tile-set globals. Each retail body reads its own three, so each
// instance gets its own externs; the differ normalises the relocation, and the
// separate declarations keep one instance from claiming another's address.
// GLOBAL: GAMEMD 0xABAD1C / 0xAA0E28 — the iso-tile base the index is off.
extern int GgTileBaseA;
extern int GgTileBaseB;
// GLOBAL: GAMEMD 0xABAD30 / 0xAA1028 — the bridge tile-set the spans sit in.
extern int GgBridgeSetV;
extern int GgBridgeSetH;
// GLOBAL: GAMEMD 0xABC1E8 / 0xABC2B4 / 0xABC1D0 / 0xAA1548 — the end-cap sets.
extern int GgCapV0;
extern int GgCapV1;
extern int GgCapH0;
extern int GgCapH1;
// GLOBAL: GAMEMD 0xAA0E38 / 0xAA1130 / 0xAA1540 / 0xAA0740 — the ramp sets.
extern int GgRampV0;
extern int GgRampV1;
extern int GgRampH0;
extern int GgRampH1;

#endif  // GG_MATCH_MAP_BRIDGE_SPAN_COLLAPSE_FAMILY_METHODS_H
