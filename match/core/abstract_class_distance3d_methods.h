// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, slots and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x5F6360: vtable slots +0x48 (GetCoords with a
//   12-byte out buffer) and +0x2C (WhatAmI, 6 = building), the building's
//   Type at +0x520 and the two foundation helpers 0x45ECA0 / 0x45EC90, the
//   square root at 0x4CAC40 and __ftol at 0x7C5F00. The 2D twin at 0x5F6440
//   (match/core/abstract_class_distance_methods.*) carries the same facts.
//   YRpp names DistanceFrom3D.
#ifndef GG_MATCH_CORE_ABSTRACT_CLASS_DISTANCE3D_METHODS_H
#define GG_MATCH_CORE_ABSTRACT_CLASS_DISTANCE3D_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

double __cdecl FUN_004CAC40(double value);

struct Coord_005F6360
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_005F6360) == 0xC);

struct BuildingType_005F6360
{
    // FUNCTION: GAMEMD 0x45EC90 (decl; reloc) — BuildingTypeClass::GetFoundationWidth.
    int GetFoundationWidth();
    // FUNCTION: GAMEMD 0x45ECA0 (decl; reloc) — BuildingTypeClass::GetFoundationHeight.
    int GetFoundationHeight(int includeBib);
};

struct Vtbl_005F6360;

struct Obj_005F6360
{
    Vtbl_005F6360*         Vtbl;            // +0x0000
    char                   _pad004[0x51C];  // +0x0004
    BuildingType_005F6360* Type;            // +0x0520 (BuildingClass::Type)

    // FUNCTION: GAMEMD 0x5F6360 — AbstractClass::DistanceFrom3D.
    int DistanceFrom3D(Obj_005F6360* that);
};
GG_STATIC_ASSERT(offsetof(Obj_005F6360, Type) == 0x520);

typedef int (Obj_005F6360::*Fn2C_005F6360)();
typedef Coord_005F6360* (Obj_005F6360::*Fn48_005F6360)(Coord_005F6360* out);

struct Vtbl_005F6360
{
    char           _pad000[0x2C];   // +0x0000
    Fn2C_005F6360  WhatAmI;         // +0x002C
    char           _pad030[0x18];   // +0x0030
    Fn48_005F6360  GetCoords;       // +0x0048
};
GG_STATIC_ASSERT(offsetof(Vtbl_005F6360, WhatAmI)   == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_005F6360, GetCoords) == 0x48);

#endif  // GG_MATCH_CORE_ABSTRACT_CLASS_DISTANCE3D_METHODS_H
