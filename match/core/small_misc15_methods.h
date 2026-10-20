// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC15_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC15_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size);   // operator new

// The two constructors are __thiscall: retail pushes both arguments and leaves
// only the new object in ECX.
struct Made_0041CB20 { char* FUN_00413D20(void* owner, int arg); };   // GAMEMD 0x413D20
struct Made_0045E880 { char* FUN_0043B740(void* owner, int arg); };   // GAMEMD 0x43B740

// The two allocate-and-construct helpers are the same shape with different
// sizes and constructors: 0x6D8 and 0x720.
struct Obj_0041CB20
{
    // FUNCTION: GAMEMD 0x41CB20
    char* FUN_0041CB20(int arg);
};

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BuildingTypeClass's own vtable is 0x7E4570.
//   0x45E880 -> BuildingTypeClass slot 35 (byte-off 0x8C).
// That table is the only table in the image that holds it, so the slot is
// declared on BuildingTypeClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BuildingTypeClass_0045E880
{
    // FUNCTION: GAMEMD 0x45E880
    char* FUN_0045E880(int arg);
};

struct Inner_00459840 { char _pad[0xEA4]; int atEA4; int atEA8; int atEAC; };

struct Obj_00459840
{
    char             _pad000[0x520];
    Inner_00459840*  unknown_520;   // +0x0520
    char             _pad524[0x6F4 - 0x524];
    int              unknown_6F4;   // +0x06F4

    // FUNCTION: GAMEMD 0x459840
    int FUN_00459840() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00459840, unknown_520) == 0x520);
GG_STATIC_ASSERT(offsetof(Obj_00459840, unknown_6F4) == 0x6F4);

#endif  // GG_MATCH_CORE_SMALL_MISC15_METHODS_H
