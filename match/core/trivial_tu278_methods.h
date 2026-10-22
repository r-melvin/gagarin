// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU278_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU278_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0076F000;
struct Obj_0076F160;
struct Obj_0076F170;
struct Obj_0076F180;
struct Obj_0076F190;
struct Obj_0076F1A0;
struct Obj_0076F1B0;

// FUNCTION: GAMEMD 0x76FF40 (declaration)
void FUN_0076FF40(int, void*, int);

struct Obj_0076F000
{
    char unknown_00[0x2C];
    int unknown_2C;   // +0x002C
    // FUNCTION: GAMEMD 0x76F000
    int FUN_0076F000(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_0076F000, unknown_2C) == 0x2C);

struct Obj_0076F160
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x76F160
    Obj_0076F160* FUN_0076F160();
};
GG_STATIC_ASSERT(offsetof(Obj_0076F160, unknown_08) == 0x8);

struct Obj_0076F170
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x76F170
    Obj_0076F170* FUN_0076F170();
};
GG_STATIC_ASSERT(offsetof(Obj_0076F170, unknown_08) == 0x8);

struct Obj_0076F180
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x76F180
    Obj_0076F180* FUN_0076F180();
};
GG_STATIC_ASSERT(offsetof(Obj_0076F180, unknown_08) == 0x8);

struct Obj_0076F190
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x76F190
    Obj_0076F190* FUN_0076F190();
};
GG_STATIC_ASSERT(offsetof(Obj_0076F190, unknown_08) == 0x8);

struct Obj_0076F1A0
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x76F1A0
    Obj_0076F1A0* FUN_0076F1A0();
};
GG_STATIC_ASSERT(offsetof(Obj_0076F1A0, unknown_08) == 0x8);

struct Obj_0076F1B0
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x76F1B0
    Obj_0076F1B0* FUN_0076F1B0();
};
GG_STATIC_ASSERT(offsetof(Obj_0076F1B0, unknown_08) == 0x8);



#endif  // GG_MATCH_CORE_TRIVIAL_TU278_METHODS_H
