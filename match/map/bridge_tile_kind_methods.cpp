// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x5746C0.
//
// Address index: 0x574600 0x5746C0

#include "bridge_span_collapse_family_methods.h"

// FUNCTION: GAMEMD 0x005746C0
// True when the iso-tile index belongs to one of the bridge tile sets and the cell's sub-tile selector
// (+0x11A) holds the value that set expects: ramp 12, vertical span 4, end cap 8, horizontal span 2.
bool __fastcall FUN_005746C0(int tile, BridgeCellClass* cell)
{
    if (tile == GgCapH1 && cell->SubTileFlags == 12)
        return true;
    if (tile == GgRampH1 && cell->SubTileFlags == 12)
        return true;
    if ((tile == GgBridgeSetV || tile == GgBridgeSetV + 3 || tile == GgBridgeSetV + 1 || tile == GgBridgeSetV + 2) &&
        cell->SubTileFlags == 4)
        return true;
    if (tile == GgCapV1 && cell->SubTileFlags == 8)
        return true;
    if (tile == GgRampV1 && cell->SubTileFlags == 8)
        return true;
    if ((tile == GgBridgeSetH || tile == GgBridgeSetH + 3 || tile == GgBridgeSetH + 1 || tile == GgBridgeSetH + 2) &&
        cell->SubTileFlags == 2)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x00574600
// Same test for one axis: kind 2 checks the vertical sets (sub-tile selector 4), kind 4 the horizontal ones
// (selector 2); any other kind is false.
bool __fastcall FUN_00574600(unsigned int tile, int kind, BridgeCellClass* cell)
{
    if (kind == 2) {
        if (tile == GgCapV0 && cell->SubTileFlags == 4)
            return true;
        if (tile == GgRampV0 && cell->SubTileFlags == 4)
            return true;
        if ((tile == GgBridgeSetV || tile == GgBridgeSetV + 3 || tile == GgBridgeSetV + 1 ||
             tile == GgBridgeSetV + 2) &&
            cell->SubTileFlags == 4)
            return true;
    } else if (kind == 4) {
        if (tile == GgCapH0 && cell->SubTileFlags == 2)
            return true;
        if (tile == GgRampH0 && cell->SubTileFlags == 2)
            return true;
        if ((tile == GgBridgeSetH || tile == GgBridgeSetH + 3 || tile == GgBridgeSetH + 1 ||
             tile == GgBridgeSetH + 2) &&
            cell->SubTileFlags == 2)
            return true;
    }
    return false;
}
