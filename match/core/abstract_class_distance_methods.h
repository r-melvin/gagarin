// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x5F6440: the GetCoords slot `[EAX+0x48]` on both objects
//   (hidden 12-byte buffer, `LEA ECX,[ESP+0x14]` / `LEA EAX,[ESP+0x24]`), the
//   WhatAmI slot `[EDX+0x2C]` compared with 6 (BuildingClass), the building's
//   Type `[ESI+0x520]` handed to 0x45ECA0 / 0x45EC90 (the foundation height
//   and width, already matched in match/economy/building_type_class.cpp),
//   sqrt via 0x4CAC40 and __ftol 0x7C5F00. The method name is YRpp's
//   AbstractClass::DistanceFrom (name only).
#ifndef GG_MATCH_CORE_ABSTRACT_CLASS_DISTANCE_METHODS_H
#define GG_MATCH_CORE_ABSTRACT_CLASS_DISTANCE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) — square root, __cdecl.
double __cdecl FUN_004CAC40(double value);

struct Coord_005F6440
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_005F6440) == 0xC);

// The X/Y difference. An aggregate rather than two ints: as plain locals VC6
// homes the two FILD spills in the dead parameter slot and the dead first
// coordinate buffer, while retail gives them their own 8 bytes below the
// buffers (frame 0x20, not 0x1C).
struct Point_005F6440
{
    int X;   // +0x0000
    int Y;   // +0x0004
};
GG_STATIC_ASSERT(sizeof(Point_005F6440) == 0x8);

// BuildingTypeClass — only the two foundation accessors are used.
struct BuildingType_005F6440
{
    // FUNCTION: GAMEMD 0x45EC90 (decl; reloc) — BuildingTypeClass::GetFoundationWidth.
    int GetFoundationWidth();
    // FUNCTION: GAMEMD 0x45ECA0 (decl; reloc) — BuildingTypeClass::GetFoundationHeight.
    int GetFoundationHeight(int includeBib);
};

// Declaration order per match/_rt/gg_vslot.h: the object must be complete
// before the member-function-pointer typedefs.
struct Vtbl_005F6440;

struct Obj_005F6440
{
    Vtbl_005F6440*         Vtbl;        // +0x0000
    char                   _pad004[0x51C];  // +0x0004
    BuildingType_005F6440* Type;        // +0x0520 (BuildingClass::Type)

    // FUNCTION: GAMEMD 0x5F6440 — AbstractClass::DistanceFrom.
    int DistanceFrom(Obj_005F6440* that);
};
GG_STATIC_ASSERT(offsetof(Obj_005F6440, Type) == 0x520);

typedef int (Obj_005F6440::*Fn2C_005F6440)();
typedef Coord_005F6440* (Obj_005F6440::*Fn48_005F6440)(Coord_005F6440* out);

struct Vtbl_005F6440
{
    char           _pad000[0x2C];   // +0x0000
    Fn2C_005F6440  WhatAmI;         // +0x002C
    char           _pad030[0x18];   // +0x0030
    Fn48_005F6440  GetCoords;       // +0x0048
};
GG_STATIC_ASSERT(offsetof(Vtbl_005F6440, WhatAmI)   == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_005F6440, GetCoords) == 0x48);

#endif  // GG_MATCH_CORE_ABSTRACT_CLASS_DISTANCE_METHODS_H
