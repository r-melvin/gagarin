// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x480510: the cell's `[EBP+0x44]` (OverlayTypeIndex)
//   and occupier list head `[EBP+0xE4]` (FirstObject) threaded through
//   `[ESI+0x30]` (NextObject); each occupier's WhatAmI slot `[EAX+0x2C]`
//   (6 = building), `[ESI+0x6C]` (Health) and `[ESI+0x520]`
//   (BuildingClass::Type); RulesClass 0x8871E0 building-type pointers at
//   +0x86C / +0x870 / +0x874 / +0x878 / +0x87C (GDIGateOne, GDIGateTwo,
//   NodGateOne, NodGateTwo, WallTower). The overlay indices 2 / 0x1A / 0xF3
//   are the wall overlays a gate joins. Names cross-checked against YRpp.
#ifndef GG_MATCH_MAP_CELL_CLASS_OVERLAY_CONNECT_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_OVERLAY_CONNECT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct BuildingType_00480510;

struct Vtbl_00480510;

// ObjectClass / BuildingClass as seen from the occupier walk.
struct Obj_00480510
{
    Vtbl_00480510*          Vptr;             // +0x0000
    char                    _pad004[0x2C];    // +0x0004
    Obj_00480510*           NextObject;       // +0x0030
    char                    _pad034[0x38];    // +0x0034
    int                     Health;           // +0x006C
    char                    _pad070[0x4B0];   // +0x0070
    BuildingType_00480510*  Type;             // +0x0520
};
GG_STATIC_ASSERT(offsetof(Obj_00480510, NextObject) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_00480510, Health)     == 0x6C);
GG_STATIC_ASSERT(offsetof(Obj_00480510, Type)       == 0x520);

typedef int (Obj_00480510::*Fn2C_00480510)();

struct Vtbl_00480510
{
    char           _pad000[0x2C];   // +0x0000
    Fn2C_00480510  WhatAmI;         // +0x002C
};
GG_STATIC_ASSERT(offsetof(Vtbl_00480510, WhatAmI) == 0x2C);

// RulesClass — the five gate / wall-tower building types.
struct Rules_00480510
{
    char                    _pad000[0x86C];   // +0x0000
    BuildingType_00480510*  GDIGateOne;       // +0x086C
    BuildingType_00480510*  GDIGateTwo;       // +0x0870
    BuildingType_00480510*  NodGateOne;       // +0x0874
    BuildingType_00480510*  NodGateTwo;       // +0x0878
    BuildingType_00480510*  WallTower;        // +0x087C
};
GG_STATIC_ASSERT(offsetof(Rules_00480510, GDIGateOne) == 0x86C);
GG_STATIC_ASSERT(offsetof(Rules_00480510, WallTower)  == 0x87C);
// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_00480510* DAT_008871E0;

// CellClass — OverlayTypeIndex and the ground occupier list head.
struct Cell_00480510
{
    char           _pad000[0x44];           // +0x0000
    int            OverlayTypeIndex;        // +0x0044
    char           _pad048[0xE4 - 0x48];    // +0x0048
    Obj_00480510*  FirstObject;             // +0x00E4

    // FUNCTION: GAMEMD 0x480510 — CellClass::ConnectsToOverlay.
    bool ConnectsToOverlay(int overlay, int direction);
};
GG_STATIC_ASSERT(offsetof(Cell_00480510, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(Cell_00480510, FirstObject)      == 0xE4);

#endif  // GG_MATCH_MAP_CELL_CLASS_OVERLAY_CONNECT_METHODS_H
