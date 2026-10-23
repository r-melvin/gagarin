// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/addresses derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x481870 and its callees),
//   cross-checked against YRpp (every
//   offset reconfirmed numerically below).
//
// CellClass::UpdateThreat is the helper called by TechnoClass::UpdateThreatInCell.
// It walks the global HouseClass::Array and, for every non-allied foreign house,
// folds this cell's threat contribution into that house's per-region threat
// accumulator. This TU models only the members those code paths touch:
//   * CellClass::MapCoords  @0x24 (CellStruct, 4 bytes)  — read by UpdateThreat
//   * HouseClass::ArrayIndex @0x30 (int)                 — fast-path self test
#ifndef GG_MATCH_MAP_CELL_CLASS_THREAT_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_THREAT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4): UpdateThreat copies it as a single
// dword (mov eax,[ecx+0x24]; mov [esp+..],eax) and passes its address on.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// ---------------------------------------------------------------------------
// HouseClass — only ArrayIndex @0x30 plus the two callees UpdateThreat invokes
// are modelled. The methods are declared without bodies so cl emits a single
// relocatable call (the differ reloc-normalises them); they are matched in
// their own TUs, not here.
// ---------------------------------------------------------------------------
class HouseClass
{
public:
    char _base[0x30];   // +0x00
    int  ArrayIndex;    // +0x30

    // 0x4F9A10 — true if `idxHouse` is allied with (or equal to) this house.
    bool IsAlliedWith(int idxHouse) const;
    // 0x4FA2E0 — fold a threat delta into this house's per-region threat table.
    void AccumulateThreat(int region, int threat);
};
GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex) == 0x30);

// ---------------------------------------------------------------------------
// The global cell-coordinate -> threat-region lookup object @0x87F7E8. The
// helper at 0x56BC50 is a __thiscall member (it ignores `this`, reading the
// CellStruct from the stack) that maps a cell to a coarse region index.
// ---------------------------------------------------------------------------
struct RegionLookupClass
{
    // 0x56BC50 — coarse region index for a cell coordinate.
    int CoordsToRegion(CellStruct const* coords);
};

class CellClass
{
public:
    char       _base[0x24];   // +0x00  AbstractClass (vtable + base)
    CellStruct MapCoords;     // +0x24  read by UpdateThreat

    // 0x481870
    void UpdateThreat(unsigned int SourceHouse, int ThreatLevel);
};
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);

#endif  // GG_MATCH_MAP_CELL_CLASS_THREAT_METHODS_H
