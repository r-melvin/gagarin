// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_MAP_0087F7E8_H_H
#define GG_MATCH__LAYOUT_MAP_0087F7E8_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class CellClass;
struct CellStruct;
struct MapObjCell;

struct Map_0087F7E8
{
    // FUNCTION: GAMEMD 0x4AE450 (decl; reloc)
    void FUN_004AE450();
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    CellClass* FUN_005657A0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x5657E0 (decl; reloc)
    bool FUN_005657E0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x56D230 (decl; reloc) -- the zone of a cell for a movement zone.
    int FUN_0056D230(const CellStruct& cell, int movementZone, bool isBridge);
    // FUNCTION: GAMEMD 0x568300 (decl; reloc) -- is the cell coordinate on the map (terrain-object cell view).
    bool FUN_00568300(const MapObjCell* cell);
};

#endif
