// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4838E0: `LEA EAX,[EDI+0x24]` (MapCoords),
//   `[EDI+0x140]` (Flags, TEST AH,5), `[EDI+0xE4]` (FirstObject),
//   `[ESI+0x30]` (NextObject), `CALL [EDX+0x2C]` (WhatAmI), `[ESI+0x6C]`
//   (Health), `[ESI+0x520]` (BuildingClass::Type), `[ESI+0xC9A]` /
//   `[ESI+0x1701]` (BuildingTypeClass bytes), `[ESI+0xC8]` (TerrainClass::Type),
//   `[ECX+0x2B1]` (TerrainTypeClass byte), `[EDI+0xEC]` (LandType) indexing
//   the 36-byte table at 0x89EA60, `[EDI+0x44]` (OverlayTypeIndex),
//   `[EDI+0x11C]`, `[EDI+0x38]` (IsoTileTypeIndex) bounded by the
//   DynamicVectorClass at 0xA8ED28 (Items +4 = 0xA8ED2C, Count +0x10 =
//   0xA8ED38) and `[EDX+0x306]` (IsometricTileTypeClass byte). Names are
//   cross-checked against YRpp and used as names only.
#ifndef GG_MATCH_MAP_CELL_CLASS_TIBERIUM_GERMINATE_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_TIBERIUM_GERMINATE_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/cell.h"
#include "_layout/map_0087f7e8.h"
#include "_layout/iso_tile_type_class.h"

// GLOBAL: GAMEMD 0xA8E9A0 — Unsorted::IsActive (byte), gates the occupier walk.
extern unsigned char DAT_00A8E9A0;

// TerrainTypeClass — one byte consulted.
struct TerrainType_004838E0
{
    char _pad000[0x2B1];      // +0x0000
    char At_2B1;              // +0x02B1
};
GG_STATIC_ASSERT(offsetof(TerrainType_004838E0, At_2B1) == 0x2B1);

// TerrainClass — Type at +0xC8.
struct Terrain_004838E0
{
    char _pad000[0xC8];       // +0x0000
    TerrainType_004838E0* Type; // +0x00C8
};
GG_STATIC_ASSERT(offsetof(Terrain_004838E0, Type) == 0xC8);

// Ground (land type) table entry: 36 bytes, first byte tested.
struct Ground_004838E0
{
    char At_000;              // +0x0000
    char _pad001[0x23];       // +0x0001
};
GG_STATIC_ASSERT(sizeof(Ground_004838E0) == 0x24);
// GLOBAL: GAMEMD 0x89EA60 — the ground-type table indexed by LandType.
extern Ground_004838E0 GroundTable_004838E0[];

#endif  // GG_MATCH_MAP_CELL_CLASS_TIBERIUM_GERMINATE_METHODS_H
