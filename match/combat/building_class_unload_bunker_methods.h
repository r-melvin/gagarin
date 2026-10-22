// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, slots and offsets read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x4593A0: BunkerLinkedItem at +0x2E4 on both
//   objects, the unit's WhatAmI slot +0x2C (1 = unit), its locomotor at
//   +0x674 with the COM slots +0x58 (no args) and +0x70 (int, CoordStruct by
//   value), the building's GetCoords slot +0x48, the unit's slot +0x544
//   (one double) and the building's slot +0x274 (one int). YRpp
//   names UnloadBunker and BunkerLinkedItem.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_UNLOAD_BUNKER_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_UNLOAD_BUNKER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Coord_004593A0 { int X; int Y; int Z; };
GG_STATIC_ASSERT(sizeof(Coord_004593A0) == 0xC);

struct ILoco_004593A0;
typedef long (__stdcall* LocoSlot0_004593A0)(ILoco_004593A0*);
typedef long (__stdcall* LocoSlot70_004593A0)(ILoco_004593A0*, int, Coord_004593A0);
#define LOCO_CALL0_004593A0(p, slot) \
    ((*(LocoSlot0_004593A0*)(*(char**)(p) + (slot)))(p))
#define LOCO_CALL70_004593A0(p, a, c) \
    ((*(LocoSlot70_004593A0*)(*(char**)(p) + 0x70))(p, a, c))

void __stdcall FUN_007DC720(unsigned int hr);

struct VtblU_004593A0;

// The occupying unit (a FootClass).
struct Unit_004593A0
{
    VtblU_004593A0* Vptr;             // +0x0000
    char _pad0004[0x2E4 - 0x04];      // +0x0004
    Unit_004593A0* BunkerLinkedItem;  // +0x02E4
    char _pad02E8[0x674 - 0x2E8];     // +0x02E8
    ILoco_004593A0* Locomotor;        // +0x0674
};
GG_STATIC_ASSERT(offsetof(Unit_004593A0, BunkerLinkedItem) == 0x2E4);
GG_STATIC_ASSERT(offsetof(Unit_004593A0, Locomotor) == 0x674);

typedef int  (Unit_004593A0::*Fn2C_004593A0)();
typedef void (Unit_004593A0::*Fn544_004593A0)(double value);

struct VtblU_004593A0
{
    char _pad000[0x2C];            // +0x0000
    Fn2C_004593A0 WhatAmI;         // +0x002C
    char _pad030[0x544 - 0x30];    // +0x0030
    Fn544_004593A0 At_544;         // +0x0544
};
GG_STATIC_ASSERT(offsetof(VtblU_004593A0, WhatAmI) == 0x2C);
GG_STATIC_ASSERT(offsetof(VtblU_004593A0, At_544) == 0x544);

struct VtblB_004593A0;

struct Building_004593A0
{
    VtblB_004593A0* Vptr;             // +0x0000
    char _pad0004[0x2E4 - 0x04];      // +0x0004
    Unit_004593A0* BunkerLinkedItem;  // +0x02E4

    // FUNCTION: GAMEMD 0x4593A0 — BuildingClass::UnloadBunker.
    void UnloadBunker();
};
GG_STATIC_ASSERT(offsetof(Building_004593A0, BunkerLinkedItem) == 0x2E4);

typedef Coord_004593A0* (Building_004593A0::*Fn48_004593A0)(Coord_004593A0* out);
typedef void (Building_004593A0::*Fn274_004593A0)(int mode);

struct VtblB_004593A0
{
    char _pad000[0x48];            // +0x0000
    Fn48_004593A0 GetCoords;       // +0x0048
    char _pad04C[0x274 - 0x4C];    // +0x004C
    Fn274_004593A0 At_274;         // +0x0274
};
GG_STATIC_ASSERT(offsetof(VtblB_004593A0, GetCoords) == 0x48);
GG_STATIC_ASSERT(offsetof(VtblB_004593A0, At_274) == 0x274);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_UNLOAD_BUNKER_METHODS_H
