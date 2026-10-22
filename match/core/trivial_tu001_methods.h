// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU001_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU001_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00405490;
struct Obj_004059F0;
struct Obj_004059F0_C0;
struct Obj_00406320;
struct Obj_00406320_24;

// GLOBAL: GAMEMD 0x816108
extern int DAT_00816108;

struct Obj_00405490
{
    char unknown_00[0x158];
    int unknown_158;   // +0x0158
    // FUNCTION: GAMEMD 0x405490
    int FUN_00405490() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00405490, unknown_158) == 0x158);

struct Obj_004059F0
{
    char unknown_00[0xC0];
    Obj_004059F0_C0* unknown_C0;   // +0x00C0
    // FUNCTION: GAMEMD 0x4059F0
    int FUN_004059F0();
};
GG_STATIC_ASSERT(offsetof(Obj_004059F0, unknown_C0) == 0xC0);

struct Obj_004059F0_C0
{
    char unknown_00[0x1C];
    int unknown_1C;   // +0x001C
};
GG_STATIC_ASSERT(offsetof(Obj_004059F0_C0, unknown_1C) == 0x1C);

struct Obj_00406320
{
    char unknown_00[0x24];
    Obj_00406320_24* unknown_24;   // +0x0024
    // FUNCTION: GAMEMD 0x406320
    int FUN_00406320();
};
GG_STATIC_ASSERT(offsetof(Obj_00406320, unknown_24) == 0x24);

struct Obj_00406320_24
{
    char unknown_00[0x10];
    bool unknown_10;   // +0x0010
    char unknown_11[0x3B];
    int unknown_4C;   // +0x004C
};
GG_STATIC_ASSERT(offsetof(Obj_00406320_24, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_00406320_24, unknown_4C) == 0x4C);


// FUNCTION: GAMEMD 0x406740
void __cdecl FUN_00406740();
// FUNCTION: GAMEMD 0x406750
int __cdecl FUN_00406750();

#endif  // GG_MATCH_CORE_TRIVIAL_TU001_METHODS_H
