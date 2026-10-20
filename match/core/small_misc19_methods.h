// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC19_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC19_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

struct Obj_00433C00
{
    char  _pad00[0x18];
    void* unknown_18;   // +0x0018
    void* unknown_1C;   // +0x001C

    // FUNCTION: GAMEMD 0x433C00
    void FUN_00433C00();
};
GG_STATIC_ASSERT(offsetof(Obj_00433C00, unknown_1C) == 0x1C);

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x449410 -> BuildingClass slot 46 (byte-off 0xB8).
// No other table in the image holds it, so the slot is declared on
// BuildingClass rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
struct BuildingClass_00449410;
int __fastcall FUN_005F6BD0b(BuildingClass_00449410* self);   // GAMEMD 0x5F6BD0

struct Flags_00449410
{
    char          _pad0000[0x16B7];
    unsigned char at16B7;   // +0x16B7
    char          _pad16B8[0x16C5 - 0x16B8];
    unsigned char at16C5;   // +0x16C5
};
GG_STATIC_ASSERT(offsetof(Flags_00449410, at16C5) == 0x16C5);

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x449410 -> BuildingClass slot 46 (byte-off 0xB8).
// That table is the only table in the image that holds it, so the slot is
// declared on BuildingClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BuildingClass_00449410
{
    char             _pad000[0x520];
    Flags_00449410*  unknown_520;   // +0x0520

    // FUNCTION: GAMEMD 0x449410
    int FUN_00449410();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00449410, unknown_520) == 0x520);

// A pair of doubles. Zeroed means "unset", and the reset value is 100.0 written
// as two dword stores.
struct Pair2d
{
    double x;   // +0x0000
    double y;   // +0x0008

    // FUNCTION: GAMEMD 0x41C460
    void FUN_0041C460();
};
GG_STATIC_ASSERT(offsetof(Pair2d, y) == 0x8);

struct Triple3i
{
    int a, b, c;

    // FUNCTION: GAMEMD 0x459F60
    int FUN_00459F60(const Triple3i* other) const;
};

#endif  // GG_MATCH_CORE_SMALL_MISC19_METHODS_H
