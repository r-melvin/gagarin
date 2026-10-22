// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU186_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU186_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Gbl_00A8E9C0;
struct Obj_00646CE0;
struct Obj_00646D00;
struct Obj_00652540;

// GLOBAL: GAMEMD 0xA8B238
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0xA8E9C0
extern Gbl_00A8E9C0 DAT_00A8E9C0;

// FUNCTION: GAMEMD 0x7C8B3D (declaration)
void __cdecl FUN_007C8B3D(int);

struct Gbl_00A8E9C0
{
    // FUNCTION: GAMEMD 0x543090
    void FUN_00543090();
};

struct Obj_00646CE0
{
    char unknown_00[0x334];
    int unknown_334;   // +0x0334
    // FUNCTION: GAMEMD 0x646CE0
    void FUN_00646CE0();
};
GG_STATIC_ASSERT(offsetof(Obj_00646CE0, unknown_334) == 0x334);

struct Obj_00646D00
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    int unknown_0C;   // +0x000C
    int unknown_10;   // +0x0010
    int unknown_14;   // +0x0014
    // FUNCTION: GAMEMD 0x646D00
    Obj_00646D00* FUN_00646D00();
};
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_00646D00, unknown_14) == 0x14);

struct Obj_00652540
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    // FUNCTION: GAMEMD 0x652540
    int FUN_00652540();
};
GG_STATIC_ASSERT(offsetof(Obj_00652540, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00652540, unknown_04) == 0x4);


// FUNCTION: GAMEMD 0x646D50
void __cdecl FUN_00646D50();
// FUNCTION: GAMEMD 0x646DB0
void __cdecl FUN_00646DB0();
// FUNCTION: GAMEMD 0x652100
void __cdecl FUN_00652100();

#endif  // GG_MATCH_CORE_TRIVIAL_TU186_METHODS_H
