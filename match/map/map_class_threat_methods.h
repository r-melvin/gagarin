// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm @ 0x56BCD0).
//   Signature cross-checked against YRpp:
//     int MapClass::GetThreatPosed(const CellStruct& cell, HouseClass* pHouse) const
//   All offsets reconfirmed numerically from the disassembly:
//     cell.X@0, cell.Y@2 (MOVSX word[ECX], word[ECX+2]); index = (Y<<9)+X,
//     bounds 0.. 0x40000.  Global Cells ptr @0x0087F924, InvalidCell @0x00ABDC50
//     with MapCoords @0x24.  pCell->MapCoords @0x24 feeds quadrant /4 each axis,
//     idx = qy*0x82 + qx into HouseClass::ThreatPosedEstimates @0x59F0.
#ifndef GG_MATCH_MAP_MAP_CLASS_THREAT_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_THREAT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4): X@0, Y@2.
struct CellStruct
{
    short X;  // +0x00
    short Y;  // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// Minimal CellClass view: only MapCoords @0x24 is touched.
struct CellClass
{
    char       _pad0[0x24];   // +0x00
    CellStruct MapCoords;     // +0x24
};
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);

// Minimal HouseClass view: only the 130x130 threat grid @0x59F0 is touched.
struct HouseClass
{
    char         _pad0[0x59f0];                  // +0x0000
    unsigned int ThreatPosedEstimates[130][130]; // +0x59F0
};
GG_STATIC_ASSERT(offsetof(HouseClass, ThreatPosedEstimates) == 0x59f0);

// Minimal MapClass view: GetThreatPosed touches no instance members (it reads
// the global cell-array pointer and InvalidCell), so the struct is empty apart
// from carrying the method scope for the mangled name.
struct MapClass
{
    int GetThreatPosed(const CellStruct& cell, HouseClass* pHouse) const;  // 0x56BCD0
};

#endif  // GG_MATCH_MAP_MAP_CLASS_THREAT_METHODS_H
