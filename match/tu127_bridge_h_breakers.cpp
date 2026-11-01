// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below; REA ev_f863d6c2f44935aa685979176c7c419abdff6a95651971b190fc7d6f493cc663.
//
// The four horizontal-set bridge-span breakers, siblings of the short breakers in
// bridge_span_break_methods.cpp. Each steps one cell along `facing`; when that cell has the bridge flag
// (+0x140 bit 0x80) it bumps an overlay index in 9..14 to the damaged value, then classifies the iso-tile
// index against the H tile-set globals: an end cap or ramp finishes through MarkSpan, the two short spans
// re-place a fixed tile. 0x56F690 / 0x572B80 and 0x56F7A0 / 0x572C90 differ in the overlay values and
// sets; within a pair only the iso-tile base differs.
//
// Address index: 0x56F690 0x56F7A0 0x572B80 0x572C90

#include "bridge_span_collapse_family_methods.h"

// FUNCTION: GAMEMD 0x0056F690
void BridgeSpanWalker::Break_0056F690(BridgeCellStruct* cell, unsigned facing)
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
        if (ov >= 9) {
            if (ov > 12) {
                if (ov == 13)
                    c->OverlayTypeIndex = 15;
            } else {
                c->OverlayTypeIndex = 14;
            }
        }
    }

    int n = c->TileIndex - GgTileBaseA + 1;
    if (n == GgCapH0 || n == GgRampH0) {
        MarkSpan(adj, 1, 0);
    } else {
        if (n == GgBridgeSetH) {
            PlaceSpan(adj, GgBridgeSetH + GgTileBaseA, -1, -1, 0);
            return;
        }
        if (n == GgBridgeSetH + 2) {
            PlaceSpan(adj, GgBridgeSetH + GgTileBaseA + 2, -1, -1, 0);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x0056F7A0
void BridgeSpanWalker::Break_0056F7A0(BridgeCellStruct* cell, unsigned facing)
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
        if (ov >= 9) {
            if (ov > 12) {
                if (ov == 14)
                    c->OverlayTypeIndex = 15;
            } else {
                c->OverlayTypeIndex = 13;
            }
        }
    }

    int n = c->TileIndex - GgTileBaseA + 1;
    if (n == GgCapH1 || n == GgRampH1) {
        MarkSpan(adj, 1, 0);
    } else {
        if (n == GgBridgeSetH) {
            PlaceSpan(adj, GgBridgeSetH + GgTileBaseA + 1, -1, -1, 0);
            return;
        }
        if (n == GgBridgeSetH + 1) {
            PlaceSpan(adj, GgBridgeSetH + GgTileBaseA + 2, -1, -1, 0);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x00572B80
void BridgeSpanWalker::Break_00572B80(BridgeCellStruct* cell, unsigned facing)
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
        if (ov >= 9) {
            if (ov > 12) {
                if (ov == 13)
                    c->OverlayTypeIndex = 15;
            } else {
                c->OverlayTypeIndex = 14;
            }
        }
    }

    int n = c->TileIndex - GgTileBaseB + 1;
    if (n == GgCapH0 || n == GgRampH0) {
        MarkSpan(adj, 1, 0);
    } else {
        if (n == GgBridgeSetH) {
            PlaceSpan(adj, GgBridgeSetH + GgTileBaseB, -1, -1, 0);
            return;
        }
        if (n == GgBridgeSetH + 2) {
            PlaceSpan(adj, GgBridgeSetH + GgTileBaseB + 2, -1, -1, 0);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x00572C90
void BridgeSpanWalker::Break_00572C90(BridgeCellStruct* cell, unsigned facing)
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
        if (ov >= 9) {
            if (ov > 12) {
                if (ov == 14)
                    c->OverlayTypeIndex = 15;
            } else {
                c->OverlayTypeIndex = 13;
            }
        }
    }

    int n = c->TileIndex - GgTileBaseB + 1;
    if (n == GgCapH1 || n == GgRampH1) {
        MarkSpan(adj, 1, 0);
    } else {
        if (n == GgBridgeSetH) {
            PlaceSpan(adj, GgBridgeSetH + GgTileBaseB + 1, -1, -1, 0);
            return;
        }
        if (n == GgBridgeSetH + 1) {
            PlaceSpan(adj, GgBridgeSetH + GgTileBaseB + 2, -1, -1, 0);
            return;
        }
    }
}
