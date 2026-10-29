// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes measured against the user's retail gamemd.exe v1.001 at each address
//   below with scripts/vc6/match_all.sh.
//
// Eight bridge-span collapse walkers, two shapes of four. Each steps one cell
// along `facing`, resolves the cell, and if the cell carries the bridge flag
// (+0x140 bit 0x80) either bumps its overlay index into the damaged range or,
// on the one index that means "already at the end of the run", recurses along
// the span, detaches the overlay, clears the cell's overlay and its +0x44
// dword and asks the map to redraw it. It then classifies the cell's iso-tile
// index against three tile-set globals: an end cap or a ramp finishes the run
// through MarkSpan, the two short spans re-place a fixed tile, and the long
// span recurses once more and repaints a three-cell neighbourhood before
// re-placing the tile with the neighbour's sub-tile ordinal. The 917-byte
// shape walks the column to the left of the cell; the 964-byte shape walks the
// row above it. Within each shape the four instances differ only in the two
// overlay constants, the +1/+2 span offset, and which tile-set globals they
// read, so one body serves each shape. Ordered ascending by retail address.
//
// PARTIAL. Best measured: 73.7% on the 917-byte shape and 59.6%% on the 964-byte
// one, from 5.7% on the first draft. What is exact: the whole cell-resolution
// idiom, the overlay block, the tile-set classification, the first three
// neighbourhood repaints of both arms, and both short-span tails. Three
// residuals remain, all placement rather than content, and the instruction
// multisets agree:
//   1. The adjacency operator's named-return temporary. Retail coalesces it
//      with the scratch coordinate and reuses the `facing` parameter's home
//      slot for both, so the copy out of the returned pointer is a self-store
//      and the low half of the loaded dword is reused for the X term. cl 8804
//      here allocates a second temporary in the `cell` parameter's home and
//      reloads both halves: seven instructions, and it shifts every offset
//      after it. Six head spellings were measured (initialisation, assignment,
//      declare-both-then-assign, chained assignment, explicit operator call,
//      and the scratch-first order) and all six compile to the identical code.
//   2. The trailing constant argument of the final PlaceSpan. Retail pushes it
//      before evaluating the sub-tile ordinal; cl pushes it after. Measured
//      both with the ordinal bound to a named local and with the lookup written
//      directly into the argument list; no difference.
//   3. The two arms' tails. Retail merges them, parking the second arm past the
//      first arm's return and jumping back into it; cl either duplicates the
//      tail (the spelling kept here, 73.7%) or hoists a shared tail below both
//      arms (54.0%). Writing retail's layout literally with goto is worse
//      still (24.3%), and forcing the out-of-line lookup through a copied
//      temporary to reproduce retail's self-store there costs 28 points
//      (45.6%). This is the eleventh batch's tail-merge lever seen from the
//      other side: there the fix was to split a merged pair, here cl declines
//      to merge a pair retail merged.
//   4. (964-byte shape only) Both arms open with the same `t.X = adj.X - 1`
//      store, and cl hoists that store above the arm branch where retail hoists
//      only the value it stores. Writing the Y assignment first in both arms to
//      break the common prefix is worse (53.9%), so the hoist is not simply a
//      source-order effect.
// Next step: a decomp-permuter run over the head, or a flag bisection on the
// inlining thresholds, since residual 1 is an allocation decision.

#include "bridge_span_collapse_family_methods.h"

// FUNCTION: GAMEMD 0x0056EF50
void BridgeSpanWalker::Collapse_0056EF50(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t = *cell + AdjacentCellOffset[facing & 7];
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov > 6) {
            if (ov == 8) {
                Collapse_0056EF50(&adj, facing);
                c->DetachOverlay(0, 0);
                c->OverlayTypeIndex = 0;
                c->Field44 = -1;
                MapInstance.RedrawCell(c->MapCoords);
            }
        } else {
            c->OverlayTypeIndex = 7;
        }
    }

    int n = c->TileIndex - GgTileBaseA + 1;
    if (n == GgCapV0 || n == GgRampV0) {
        MarkSpan(adj, 1, 0);
        return;
    }
    if (n == GgBridgeSetV || n == GgBridgeSetV + 2) {
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseA + 2, -1, -1, 0);
        return;
    }
    if (n != GgBridgeSetV + 3) {
        return;
    }

    Collapse_0056EF50(&adj, facing);

    BridgeCellClass* last;
    if (c->SubTileFlags & 1) {
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y + 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseA + 3, -1, last->SubTileOrdinal - 4, 0);
        return;
    } else {
        t.X = adj.X;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y + 1;
        MapInstance.GetCellAt(t)->Touch();
        last = MapInstance.GetCellAt(adj);
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseA + 3, -1, last->SubTileOrdinal - 4, 0);
    }
}

// FUNCTION: GAMEMD 0x0056F2F0
void BridgeSpanWalker::Collapse_0056F2F0(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t = *cell + AdjacentCellOffset[facing & 7];
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov > 6) {
            if (ov == 7) {
                Collapse_0056F2F0(&adj, facing);
                c->DetachOverlay(0, 0);
                c->OverlayTypeIndex = 0;
                c->Field44 = -1;
                MapInstance.RedrawCell(c->MapCoords);
            }
        } else {
            c->OverlayTypeIndex = 8;
        }
    }

    int n = c->TileIndex - GgTileBaseA + 1;
    if (n == GgCapV1 || n == GgRampV1) {
        MarkSpan(adj, 1, 0);
        return;
    }
    if (n == GgBridgeSetV || n == GgBridgeSetV + 1) {
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseA + 2, -1, -1, 0);
        return;
    }
    if (n != GgBridgeSetV + 3) {
        return;
    }

    Collapse_0056F2F0(&adj, facing);

    BridgeCellClass* last;
    if (c->SubTileFlags & 1) {
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y + 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseA + 3, -1, last->SubTileOrdinal - 4, 0);
        return;
    } else {
        t.X = adj.X;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y + 1;
        MapInstance.GetCellAt(t)->Touch();
        last = MapInstance.GetCellAt(adj);
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseA + 3, -1, last->SubTileOrdinal - 4, 0);
    }
}

// FUNCTION: GAMEMD 0x0056F8B0
void BridgeSpanWalker::Collapse_0056F8B0(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t = *cell + AdjacentCellOffset[facing & 7];
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov >= 9) {
            if (ov > 0xF) {
                if (ov == 0x10) {
                    Collapse_0056F8B0(&adj, facing);
                    c->DetachOverlay(6, 0);
                    c->OverlayTypeIndex = 0;
                    c->Field44 = -1;
                    MapInstance.RedrawCell(c->MapCoords);
                }
            } else {
                c->OverlayTypeIndex = 0x11;
            }
        }
    }

    int n = c->TileIndex - GgTileBaseA + 1;
    if (n == GgCapH0 || n == GgRampH0) {
        MarkSpan(adj, 1, 0);
        return;
    }
    if (n == GgBridgeSetH || n == GgBridgeSetH + 2) {
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseA + 2, -1, -1, 0);
        return;
    }
    if (n != GgBridgeSetH + 3) {
        return;
    }

    Collapse_0056F8B0(&adj, facing);

    BridgeCellClass* last;
    if (c->SubTileFlags > 4) {
        t.X = adj.X - 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X + 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseA + 3, -1, last->SubTileOrdinal - 4, 0);
        return;
    } else {
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X + 1;
        t.Y = adj.Y;
        MapInstance.GetCellAt(t)->Touch();
        last = MapInstance.GetCellAt(adj);
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseA + 3, -1, last->SubTileOrdinal - 4, 0);
    }
}

// FUNCTION: GAMEMD 0x0056FC80
void BridgeSpanWalker::Collapse_0056FC80(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t = *cell + AdjacentCellOffset[facing & 7];
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov >= 9) {
            if (ov > 0xF) {
                if (ov == 0x11) {
                    Collapse_0056FC80(&adj, facing);
                    c->DetachOverlay(6, 0);
                    c->OverlayTypeIndex = 0;
                    c->Field44 = -1;
                    MapInstance.RedrawCell(c->MapCoords);
                }
            } else {
                c->OverlayTypeIndex = 0x10;
            }
        }
    }

    int n = c->TileIndex - GgTileBaseA + 1;
    if (n == GgCapH1 || n == GgRampH1) {
        MarkSpan(adj, 1, 0);
        return;
    }
    if (n == GgBridgeSetH || n == GgBridgeSetH + 1) {
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseA + 2, -1, -1, 0);
        return;
    }
    if (n != GgBridgeSetH + 3) {
        return;
    }

    Collapse_0056FC80(&adj, facing);

    BridgeCellClass* last;
    if (c->SubTileFlags > 4) {
        t.X = adj.X - 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X + 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseA + 3, -1, last->SubTileOrdinal - 4, 0);
        return;
    } else {
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X + 1;
        t.Y = adj.Y;
        MapInstance.GetCellAt(t)->Touch();
        last = MapInstance.GetCellAt(adj);
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseA + 3, -1, last->SubTileOrdinal - 4, 0);
    }
}

// FUNCTION: GAMEMD 0x00572440
void BridgeSpanWalker::Collapse_00572440(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t = *cell + AdjacentCellOffset[facing & 7];
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov > 6) {
            if (ov == 8) {
                Collapse_00572440(&adj, facing);
                c->DetachOverlay(0, 0);
                c->OverlayTypeIndex = 0;
                c->Field44 = -1;
                MapInstance.RedrawCell(c->MapCoords);
            }
        } else {
            c->OverlayTypeIndex = 7;
        }
    }

    int n = c->TileIndex - GgTileBaseB + 1;
    if (n == GgCapV0 || n == GgRampV0) {
        MarkSpan(adj, 1, 0);
        return;
    }
    if (n == GgBridgeSetV || n == GgBridgeSetV + 2) {
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseB + 2, -1, -1, 0);
        return;
    }
    if (n != GgBridgeSetV + 3) {
        return;
    }

    Collapse_00572440(&adj, facing);

    BridgeCellClass* last;
    if (c->SubTileFlags & 1) {
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y + 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseB + 3, -1, last->SubTileOrdinal - 4, 0);
        return;
    } else {
        t.X = adj.X;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y + 1;
        MapInstance.GetCellAt(t)->Touch();
        last = MapInstance.GetCellAt(adj);
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseB + 3, -1, last->SubTileOrdinal - 4, 0);
    }
}

// FUNCTION: GAMEMD 0x005727E0
void BridgeSpanWalker::Collapse_005727E0(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t = *cell + AdjacentCellOffset[facing & 7];
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov > 6) {
            if (ov == 7) {
                Collapse_005727E0(&adj, facing);
                c->DetachOverlay(0, 0);
                c->OverlayTypeIndex = 0;
                c->Field44 = -1;
                MapInstance.RedrawCell(c->MapCoords);
            }
        } else {
            c->OverlayTypeIndex = 8;
        }
    }

    int n = c->TileIndex - GgTileBaseB + 1;
    if (n == GgCapV1 || n == GgRampV1) {
        MarkSpan(adj, 1, 0);
        return;
    }
    if (n == GgBridgeSetV || n == GgBridgeSetV + 1) {
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseB + 2, -1, -1, 0);
        return;
    }
    if (n != GgBridgeSetV + 3) {
        return;
    }

    Collapse_005727E0(&adj, facing);

    BridgeCellClass* last;
    if (c->SubTileFlags & 1) {
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y + 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseB + 3, -1, last->SubTileOrdinal - 4, 0);
        return;
    } else {
        t.X = adj.X;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y + 1;
        MapInstance.GetCellAt(t)->Touch();
        last = MapInstance.GetCellAt(adj);
        PlaceSpan(adj, GgBridgeSetV + GgTileBaseB + 3, -1, last->SubTileOrdinal - 4, 0);
    }
}

// FUNCTION: GAMEMD 0x00572DA0
void BridgeSpanWalker::Collapse_00572DA0(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t = *cell + AdjacentCellOffset[facing & 7];
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov >= 9) {
            if (ov > 0xF) {
                if (ov == 0x10) {
                    Collapse_00572DA0(&adj, facing);
                    c->DetachOverlay(6, 0);
                    c->OverlayTypeIndex = 0;
                    c->Field44 = -1;
                    MapInstance.RedrawCell(c->MapCoords);
                }
            } else {
                c->OverlayTypeIndex = 0x11;
            }
        }
    }

    int n = c->TileIndex - GgTileBaseB + 1;
    if (n == GgCapH0 || n == GgRampH0) {
        MarkSpan(adj, 1, 0);
        return;
    }
    if (n == GgBridgeSetH || n == GgBridgeSetH + 2) {
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseB + 2, -1, -1, 0);
        return;
    }
    if (n != GgBridgeSetH + 3) {
        return;
    }

    Collapse_00572DA0(&adj, facing);

    BridgeCellClass* last;
    if (c->SubTileFlags > 4) {
        t.X = adj.X - 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X + 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseB + 3, -1, last->SubTileOrdinal - 4, 0);
        return;
    } else {
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X + 1;
        t.Y = adj.Y;
        MapInstance.GetCellAt(t)->Touch();
        last = MapInstance.GetCellAt(adj);
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseB + 3, -1, last->SubTileOrdinal - 4, 0);
    }
}

// FUNCTION: GAMEMD 0x00573170
void BridgeSpanWalker::Collapse_00573170(BridgeCellStruct* cell, unsigned facing)
{
    BridgeCellStruct t = *cell + AdjacentCellOffset[facing & 7];
    BridgeCellStruct adj = t;
    BridgeCellClass* c;
    GG_BRIDGE_CELL_AT(c, t);

    if (c->Flags140 & 0x80) {
        unsigned char ov = c->OverlayTypeIndex;
        if (ov >= 9) {
            if (ov > 0xF) {
                if (ov == 0x11) {
                    Collapse_00573170(&adj, facing);
                    c->DetachOverlay(6, 0);
                    c->OverlayTypeIndex = 0;
                    c->Field44 = -1;
                    MapInstance.RedrawCell(c->MapCoords);
                }
            } else {
                c->OverlayTypeIndex = 0x10;
            }
        }
    }

    int n = c->TileIndex - GgTileBaseB + 1;
    if (n == GgCapH1 || n == GgRampH1) {
        MarkSpan(adj, 1, 0);
        return;
    }
    if (n == GgBridgeSetH || n == GgBridgeSetH + 1) {
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseB + 2, -1, -1, 0);
        return;
    }
    if (n != GgBridgeSetH + 3) {
        return;
    }

    Collapse_00573170(&adj, facing);

    BridgeCellClass* last;
    if (c->SubTileFlags > 4) {
        t.X = adj.X - 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X + 1;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y - 1;
        GG_BRIDGE_CELL_AT(last, t);
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseB + 3, -1, last->SubTileOrdinal - 4, 0);
        return;
    } else {
        t.X = adj.X - 1;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X;
        t.Y = adj.Y;
        GG_BRIDGE_CELL_AT(last, t);
        last->Touch();
        t.X = adj.X + 1;
        t.Y = adj.Y;
        MapInstance.GetCellAt(t)->Touch();
        last = MapInstance.GetCellAt(adj);
        PlaceSpan(adj, GgBridgeSetH + GgTileBaseB + 3, -1, last->SubTileOrdinal - 4, 0);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAA0740
int GgRampH1;
// GLOBAL: GAMEMD 0xAA1028
int GgBridgeSetH;
// GLOBAL: GAMEMD 0xAA1540
int GgRampH0;
// GLOBAL: GAMEMD 0xAA1548
int GgCapH1;
// GLOBAL: GAMEMD 0xABC1D0
int GgCapH0;
// END defined globals
