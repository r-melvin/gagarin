// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RE-findings-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm 0x486750
//   len 0x1F, 0x486770 len 0x1F, 0x486790 len 0x1A).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x486750  CellClass::IsBridgeTile        (__thiscall)
//   FUNCTION: GAMEMD 0x486770  CellClass::IsWoodBridgeTile    (__thiscall)
//   FUNCTION: GAMEMD 0x486790  CellClass::IsTileInSet00AA0E24 (__thiscall)
//   GLOBAL:   GAMEMD 0xAA0E28  GgBridgeTileBase
//   GLOBAL:   GAMEMD 0xABAD1C  GgWoodBridgeTileBase
//   GLOBAL:   GAMEMD 0xAA0E24  GgTileBase_00AA0E24
//
// Three half-open iso-tile range tests: a tile set is sixteen consecutive
// iso-tile indices starting at a global the map loader fills in, and the cell
// belongs to the set when its own index falls inside that window. Two of the
// three treat -1 in the base as "this map has no such set".

#include "cell_class_bridge_tile_queries.h"

// FUNCTION: GAMEMD 0x486750  (__thiscall)
// Is this cell a concrete bridge tile?
//
// LEVER, measured over six spellings in one probe compile: the base must be
// referenced as the global on all three occurrences, NOT copied into a named
// local first. With a local cl colours the global EAX and the member ECX
// (53.8%, multiset identical, pure register naming); referencing the global
// directly makes cl keep it in EDX and give the member EAX, which is retail
// exactly. Hoisting the member into a local, an early `return false` on the
// -1 arm, and a single `&&` chain all reproduce the losing colouring.
// The upper bound is written as `base + 0x10` so cl emits retail's in-place
// `ADD EDX,0x10`, and the success arm is nested so `return false` stays the
// trailing fall-through and cl materialises `MOV AL,0x1`.
bool CellClass::IsBridgeTile()
{
    if (GgBridgeTileBase != -1) {
        if (this->IsoTileTypeIndex >= GgBridgeTileBase
            && this->IsoTileTypeIndex < GgBridgeTileBase + 0x10) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x486770  (__thiscall)
// Is this cell a wooden bridge tile? Same window test against the wood set.
bool CellClass::IsWoodBridgeTile()
{
    if (GgWoodBridgeTileBase != -1) {
        if (this->IsoTileTypeIndex >= GgWoodBridgeTileBase
            && this->IsoTileTypeIndex < GgWoodBridgeTileBase + 0x10) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x486790  (__thiscall)
// The same window test against the set at 0x00AA0E24, without the "-1 means
// absent" guard the other two carry. Retail loads the member before the global
// here, which is the order the member-first expression gives.
bool CellClass::IsTileInSet00AA0E24()
{
    if (this->IsoTileTypeIndex >= GgTileBase_00AA0E24
        && this->IsoTileTypeIndex < GgTileBase_00AA0E24 + 0x10) {
        return true;
    }
    return false;
}
