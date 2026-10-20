// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x47D210: the cell's overlay index `[ECX+0x44]`
//   indexes the overlay-type array at 0xA83D84 and the type's byte at +0x2A8
//   gates the search; the building array is `[0xA8EB44]` with its count at
//   0xA8EB50; on each building `[ESI+0x90]`, `[ESI+0x74]`, the owner
//   `[ESI+0x21C]`, the owner's type `[EAX+0x34]` and its byte at +0x1A7; the
//   result is written to `[ECX+0x50]`. The vtable slot `[EAX+0x38]` is the
//   AbstractClass owning-house-index getter. Names cross-checked against YRpp
//   CellClass::SetWallOwner / AbstractClass::DistanceFrom3D.
#ifndef GG_MATCH_MAP_CELL_CLASS_WALL_OWNER_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_WALL_OWNER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct CellClass;

struct OverlayType_0047D210
{
    char _pad000[0x2A8];      // +0x0000
    char Wall;                // +0x02A8
};
GG_STATIC_ASSERT(offsetof(OverlayType_0047D210, Wall) == 0x2A8);

// GLOBAL: GAMEMD 0xA83D84 — OverlayTypeClass::Array.Items.
extern OverlayType_0047D210** DAT_00A83D84;

struct HouseType_0047D210
{
    char _pad000[0x1A7];      // +0x0000
    char WallOwner;           // +0x01A7
};
GG_STATIC_ASSERT(offsetof(HouseType_0047D210, WallOwner) == 0x1A7);

struct House_0047D210
{
    char _pad000[0x34];       // +0x0000
    HouseType_0047D210* Type; // +0x0034
};
GG_STATIC_ASSERT(offsetof(House_0047D210, Type) == 0x34);

struct Vtbl_0047D210;

struct Building_0047D210
{
    Vtbl_0047D210*  Vtbl;     // +0x0000
    char            _pad004[0x70];   // +0x0004
    char            At_74;           // +0x0074
    char            _pad075[0x1B];   // +0x0075
    char            At_90;           // +0x0090
    char            _pad091[0x18B];  // +0x0091
    House_0047D210* Owner;           // +0x021C

    // FUNCTION: GAMEMD 0x5F6360 (decl; reloc) — AbstractClass::DistanceFrom3D.
    int DistanceFrom3D(CellClass* that);
};
GG_STATIC_ASSERT(offsetof(Building_0047D210, At_74) == 0x74);
GG_STATIC_ASSERT(offsetof(Building_0047D210, At_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Building_0047D210, Owner) == 0x21C);

typedef int (Building_0047D210::*Fn38_0047D210)();

struct Vtbl_0047D210
{
    char _pad000[0x38];               // +0x0000
    Fn38_0047D210 GetOwningHouseIndex; // +0x0038
};
GG_STATIC_ASSERT(offsetof(Vtbl_0047D210, GetOwningHouseIndex) == 0x38);

// GLOBAL: GAMEMD 0xA8EB44 — BuildingClass::Array.Items.
extern Building_0047D210** DAT_00A8EB44;
// GLOBAL: GAMEMD 0xA8EB50 — BuildingClass::Array.Count.
extern int DAT_00A8EB50;

struct CellClass
{
    char _pad000[0x44];       // +0x0000
    int  OverlayTypeIndex;    // +0x0044
    char _pad048[0x8];        // +0x0048
    int  WallOwnerIndex;      // +0x0050

    // FUNCTION: GAMEMD 0x47D210
    void SetWallOwner();
};
GG_STATIC_ASSERT(offsetof(CellClass, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(CellClass, WallOwnerIndex) == 0x50);

#endif  // GG_MATCH_MAP_CELL_CLASS_WALL_OWNER_METHODS_H
