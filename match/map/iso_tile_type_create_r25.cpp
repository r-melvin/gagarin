// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x549AE0 (lazy tile-data load, PUSH 0xB0 / operator new, then the
//   IsometricTileClass constructor 0x543780 with the type's +0x294 index and the cell at 0xAA105C).
//
// Address index: 0x549AE0.
#include "../_layout/iso_tile_type_class.h"
#include "terrain_objects/isometric_tile_class.h"

// GLOBAL: GAMEMD 0xAA105C -- the all-zero cell value passed as the placement cell.
extern MapObjCell DAT_00AA105C;

// FUNCTION: GAMEMD 0x549AE0
// Creates a tile object of this type, loading the tile data first if it is still pending.
IsometricTileClass* IsometricTileTypeClass::FUN_00549AE0(int)
{
    if (Image == 0 && TileDataLoadable)
        LoadTileData();
    return new IsometricTileClass(unknown_294, &DAT_00AA105C);
}
