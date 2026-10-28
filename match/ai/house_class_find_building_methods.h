// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4FD060: `LEA ECX,[EBX+0x5500]` feeding CALL 0x49FAE0 (the
//   per-type counter lookup, the same method building_class.h binds on the
//   0x5550 counter), the owned-building vector `[EBX+0x6C]` / `[EBX+0x78]`
//   (Items / Count, as in house_class_silos_methods.h), the building's
//   `[ESI+0x81]` InLimbo and `[ESI+0x520]` Type, the BuildingTypeClass array
//   globals 0xA83C6C (Items) / 0xA83C78 (Count) walked inline, GetCoords
//   `[EDX+0x48]` with a 12-byte hidden buffer `LEA EAX,[ESP+0x14]`, and CALL
//   0x4FFB20 (the sector of a coordinate). The method name is YRpp's
//   HouseClass::FindBuildingOfType (name only).
#ifndef GG_MATCH_AI_HOUSE_CLASS_FIND_BUILDING_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_FIND_BUILDING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Coord_004FD060
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_004FD060) == 0xC);

struct BuildingType_004FD060;

// GLOBAL: GAMEMD 0xA83C6C — BuildingTypeClass::Array items.
extern BuildingType_004FD060** DAT_00A83C6C;
// GLOBAL: GAMEMD 0xA83C78 — BuildingTypeClass::Array count.
extern int DAT_00A83C78;

// Declaration order per match/_rt/gg_vslot.h.
struct BuildingVtbl_004FD060;

struct Building_004FD060
{
    BuildingVtbl_004FD060*  Vtbl;                   // +0x0000
    char                    _pad004[0x81 - 0x4];    // +0x0004
    char                    InLimbo;                // +0x0081
    char                    _pad082[0x520 - 0x82];  // +0x0082
    BuildingType_004FD060*  Type;                   // +0x0520
};
GG_STATIC_ASSERT(offsetof(Building_004FD060, InLimbo) == 0x81);
GG_STATIC_ASSERT(offsetof(Building_004FD060, Type)    == 0x520);

typedef Coord_004FD060* (Building_004FD060::*Fn48_004FD060)(Coord_004FD060* out);

struct BuildingVtbl_004FD060
{
    char           _pad000[0x48];   // +0x0000
    Fn48_004FD060  GetCoords;       // +0x0048
};
GG_STATIC_ASSERT(offsetof(BuildingVtbl_004FD060, GetCoords) == 0x48);

// The per-building-type counter embedded in HouseClass at +0x5500.
struct Counter_004FD060
{
    // FUNCTION: GAMEMD 0x49FAE0 (decl; reloc) — the count held for one type.
    int GetCount(int index);
};

// A cell as two shorts (read through a pointer at 0x4FFD90).
struct Cell_004FFD90
{
    short X;   // +0x0000
    short Y;   // +0x0002
};

struct House_004FD060
{
    char                  _pad000[0x6C];             // +0x0000
    Building_004FD060**   BuildingItems;             // +0x006C
    char                  _pad070[0x8];              // +0x0070
    int                   unknown_78;             // +0x0078
    char                  _pad07C[0x5500 - 0x7C];    // +0x007C
    Counter_004FD060      At_5500;                   // +0x5500
    char                  _pad5501[0x564C - 0x5501]; // +0x5501
    int                   At_564C;                   // +0x564C

    // FUNCTION: GAMEMD 0x4FFB20 (decl; reloc) — which sector a coordinate is in.
    int SectorOf(Coord_004FD060* coords);

    // FUNCTION: GAMEMD 0x4FFD50 — sector of an object's coordinates, -1 for a null object.
    int SectorOfObject(Building_004FD060* object);
    // FUNCTION: GAMEMD 0x4FFD90 — sector of the centre of a cell.
    int SectorOfCell(Cell_004FFD90* cell);

    // FUNCTION: GAMEMD 0x4FD060 — HouseClass::FindBuildingOfType.
    Building_004FD060* FindBuildingOfType(int index, int sector);

    // FUNCTION: GAMEMD 0x4FD040 — the building type being produced, null when none.
    BuildingType_004FD060* GetProducingBuildingType();
};
GG_STATIC_ASSERT(offsetof(House_004FD060, BuildingItems) == 0x6C);
GG_STATIC_ASSERT(offsetof(House_004FD060, unknown_78) == 0x78);
GG_STATIC_ASSERT(offsetof(House_004FD060, At_5500)       == 0x5500);
GG_STATIC_ASSERT(offsetof(House_004FD060, At_564C)       == 0x564C);

#endif  // GG_MATCH_AI_HOUSE_CLASS_FIND_BUILDING_METHODS_H
