// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below.
//
// The four short bridge-span breakers beside the Collapse walkers (bridge_span_collapse_family_methods.cpp).
// Each steps one cell along `facing`, and when that cell carries the bridge flag (+0x140 bit 0x80) bumps its
// overlay index into the damaged range. It then classifies the cell's iso-tile index against the tile-set
// globals: an end cap or ramp finishes the run through MarkSpan, the two short spans re-place a fixed tile.
// The 0x56ED40 / 0x572230 pair differs from the 0x56EE40 / 0x572330 pair in the overlay values and sets;
// within a pair only the iso-tile base differs.
//
// Address index: 0x56ED40 0x56EE40 0x572230 0x572330

#include "bridge_span_collapse_family_methods.h"

// FUNCTION: GAMEMD 0x0056ED40
void BridgeSpanWalker::Break_0056ED40(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t;
    const BridgeCellStruct& step = AdjacentCellOffset[facing & 7];
    t.X = step.X + cell->X;
    t.Y = step.Y + cell->Y;
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov > 3) {
            if (ov == 5)
                c->OverlayTypeIndex = 6;
        } else {
            c->OverlayTypeIndex = 4;
        }
    }

    int n = c->TileIndex - GgTileBaseA + 1;
    if (n == GgCapV0 || n == GgRampV0) {
        MarkSpan(adj, 1, 0);
    } else {
        if (n == GgBridgeSetV) {
            PlaceSpan(adj, GgBridgeSetV + GgTileBaseA, -1, -1, 0);
            return;
        }
        if (n == GgBridgeSetV + 2) {
            PlaceSpan(adj, GgBridgeSetV + GgTileBaseA + 2, -1, -1, 0);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x0056EE40
void BridgeSpanWalker::Break_0056EE40(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t;
    const BridgeCellStruct& step = AdjacentCellOffset[facing & 7];
    t.X = step.X + cell->X;
    t.Y = step.Y + cell->Y;
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov > 3) {
            if (ov == 4)
                c->OverlayTypeIndex = 6;
        } else {
            c->OverlayTypeIndex = 5;
        }
    }

    int n = c->TileIndex - GgTileBaseA + 1;
    if (n == GgCapV1 || n == GgRampV1) {
        MarkSpan(adj, 1, 0);
    } else {
        if (n == GgBridgeSetV) {
            PlaceSpan(adj, GgBridgeSetV + GgTileBaseA + 1, -1, -1, 0);
            return;
        }
        if (n == GgBridgeSetV + 1) {
            PlaceSpan(adj, GgBridgeSetV + GgTileBaseA + 2, -1, -1, 0);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x00572230
void BridgeSpanWalker::Break_00572230(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t;
    const BridgeCellStruct& step = AdjacentCellOffset[facing & 7];
    t.X = step.X + cell->X;
    t.Y = step.Y + cell->Y;
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov > 3) {
            if (ov == 5)
                c->OverlayTypeIndex = 6;
        } else {
            c->OverlayTypeIndex = 4;
        }
    }

    int n = c->TileIndex - GgTileBaseB + 1;
    if (n == GgCapV0 || n == GgRampV0) {
        MarkSpan(adj, 1, 0);
    } else {
        if (n == GgBridgeSetV) {
            PlaceSpan(adj, GgBridgeSetV + GgTileBaseB, -1, -1, 0);
            return;
        }
        if (n == GgBridgeSetV + 2) {
            PlaceSpan(adj, GgBridgeSetV + GgTileBaseB + 2, -1, -1, 0);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x00572330
void BridgeSpanWalker::Break_00572330(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t;
    const BridgeCellStruct& step = AdjacentCellOffset[facing & 7];
    t.X = step.X + cell->X;
    t.Y = step.Y + cell->Y;
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov > 3) {
            if (ov == 4)
                c->OverlayTypeIndex = 6;
        } else {
            c->OverlayTypeIndex = 5;
        }
    }

    int n = c->TileIndex - GgTileBaseB + 1;
    if (n == GgCapV1 || n == GgRampV1) {
        MarkSpan(adj, 1, 0);
    } else {
        if (n == GgBridgeSetV) {
            PlaceSpan(adj, GgBridgeSetV + GgTileBaseB + 1, -1, -1, 0);
            return;
        }
        if (n == GgBridgeSetV + 1) {
            PlaceSpan(adj, GgBridgeSetV + GgTileBaseB + 2, -1, -1, 0);
            return;
        }
    }
}
