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
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/iso_tile_type_class.h"

// GLOBAL: GAMEMD 0xA8E9A0 — Unsorted::IsActive (byte), gates the occupier walk.
extern unsigned char DAT_00A8E9A0;

// ObjectClass spine: WhatAmI at vtable slot +0x2C, NextObject +0x30, Health +0x6C.
struct ObjVtbl_004838E0;
struct Obj_004838E0
{
    ObjVtbl_004838E0* Vtbl;   // +0x0000
    char _pad004[0x2C];       // +0x0004
    Obj_004838E0* NextObject; // +0x0030
    char _pad034[0x38];       // +0x0034
    int  Health;              // +0x006C
};
GG_STATIC_ASSERT(offsetof(Obj_004838E0, NextObject) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_004838E0, Health) == 0x6C);

typedef int (Obj_004838E0::*Fn02C_004838E0)();
struct ObjVtbl_004838E0
{
    char _pad000[0x2C];       // +0x0000
    Fn02C_004838E0 WhatAmI;   // +0x002C
};
GG_STATIC_ASSERT(offsetof(ObjVtbl_004838E0, WhatAmI) == 0x2C);

// BuildingTypeClass — two bytes consulted for ore growth under a building.
struct BuildingType_004838E0
{
    char _pad000[0xC9A];      // +0x0000
    char At_C9A;              // +0x0C9A
    char _padC9B[0x1701 - 0xC9B]; // +0x0C9B
    char At_1701;             // +0x1701
};
GG_STATIC_ASSERT(offsetof(BuildingType_004838E0, At_C9A) == 0xC9A);
GG_STATIC_ASSERT(offsetof(BuildingType_004838E0, At_1701) == 0x1701);

// BuildingClass — Type at +0x520 on top of the ObjectClass spine.
struct Building_004838E0
{
    char _pad000[0x520];      // +0x0000
    BuildingType_004838E0* Type; // +0x0520
};
GG_STATIC_ASSERT(offsetof(Building_004838E0, Type) == 0x520);

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

// CellClass — only the members the germination test reads.
struct Cell_004838E0
{
    char _pad000[0x24];               // +0x0000
    CellStruct          MapCoords;    // +0x0024
    char _pad028[0x10];               // +0x0028
    int  IsoTileTypeIndex;            // +0x0038
    char _pad03C[0x8];                // +0x003C
    int  OverlayTypeIndex;            // +0x0044
    char _pad048[0xE4 - 0x48];        // +0x0048
    Obj_004838E0* FirstObject;        // +0x00E4
    char _pad0E8[4];                  // +0x00E8
    int  LandType;                    // +0x00EC
    char _pad0F0[0x11C - 0xF0];       // +0x00F0
    char At_11C;                      // +0x011C
    char _pad11D[0x140 - 0x11D];      // +0x011D
    unsigned int Flags;               // +0x0140

    // Inlined occupier walks (bodies in the .cpp, ahead of their caller).
    Obj_004838E0* GetBuilding() const;
    Obj_004838E0* GetTerrain() const;

    // FUNCTION: GAMEMD 0x4838E0 — CellClass::CanTiberiumGerminate.
    bool CanTiberiumGerminate(void* tiberium);
};
GG_STATIC_ASSERT(offsetof(Cell_004838E0, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(Cell_004838E0, IsoTileTypeIndex) == 0x38);
GG_STATIC_ASSERT(offsetof(Cell_004838E0, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(Cell_004838E0, FirstObject) == 0xE4);
GG_STATIC_ASSERT(offsetof(Cell_004838E0, LandType) == 0xEC);
GG_STATIC_ASSERT(offsetof(Cell_004838E0, At_11C) == 0x11C);
GG_STATIC_ASSERT(offsetof(Cell_004838E0, Flags) == 0x140);

#endif  // GG_MATCH_MAP_CELL_CLASS_TIBERIUM_GERMINATE_METHODS_H
