// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU177_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU177_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00631E10;
struct Obj_00631F10;
struct Obj_00631F30;

// FUNCTION: GAMEMD 0x631D40 (declaration)
void FUN_00631D40(Obj_00631E10*, int, int);

struct Obj_00631E10
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Obj_00631E10, unknown_00) == 0x0);

struct Obj_00631F10
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
    int unknown_34;   // +0x0034
    // FUNCTION: GAMEMD 0x631F10
    void FUN_00631F10(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_00631F10, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_00631F10, unknown_34) == 0x34);

struct Obj_00631F30
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x631F30
    void FUN_00631F30();
};
GG_STATIC_ASSERT(offsetof(Obj_00631F30, unknown_00) == 0x0);


// FUNCTION: GAMEMD 0x631E10
Obj_00631E10* FUN_00631E10(Obj_00631E10* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU177_METHODS_H
