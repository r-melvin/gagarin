// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU238_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU238_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Gptr_008871E0;
struct Obj_00711E90;
struct Obj_00711EC0;
struct Obj_00712120;
struct Obj_00717800;

// GLOBAL: GAMEMD 0x8871E0
extern Gptr_008871E0* DAT_008871E0;
// GLOBAL: GAMEMD 0xA8B238
extern int DAT_00A8B238;

struct Gptr_008871E0
{
    char unknown_00[0x7B4];
    int unknown_7B4;   // +0x07B4
    char unknown_7B8[0xF14];
    int unknown_16CC;   // +0x16CC
};
GG_STATIC_ASSERT(offsetof(Gptr_008871E0, unknown_7B4) == 0x7B4);
GG_STATIC_ASSERT(offsetof(Gptr_008871E0, unknown_16CC) == 0x16CC);

struct Obj_00711E90
{
    char unknown_00[0x6C8];
    bool unknown_6C8;   // +0x06C8
    char unknown_6C9[0x1CF];
    int unknown_898;   // +0x0898
    // FUNCTION: GAMEMD 0x711E90
    bool FUN_00711E90();
};
GG_STATIC_ASSERT(offsetof(Obj_00711E90, unknown_6C8) == 0x6C8);
GG_STATIC_ASSERT(offsetof(Obj_00711E90, unknown_898) == 0x898);

struct Obj_00711EC0
{
    char unknown_00[0x6CC];
    int unknown_6CC;   // +0x06CC
    char unknown_6D0[0x5C9];
    unsigned char unknown_C99;   // +0x0C99
    // FUNCTION: GAMEMD 0x711EC0
    int FUN_00711EC0();
};
GG_STATIC_ASSERT(offsetof(Obj_00711EC0, unknown_6CC) == 0x6CC);
GG_STATIC_ASSERT(offsetof(Obj_00711EC0, unknown_C99) == 0xC99);

struct Obj_00712120
{
    // FUNCTION: GAMEMD 0x712120
    int FUN_00712120() const;
};

struct Obj_00717800
{
    char unknown_00[0x618];
    int unknown_618;   // +0x0618
    // FUNCTION: GAMEMD 0x717800
    int FUN_00717800();
};
GG_STATIC_ASSERT(offsetof(Obj_00717800, unknown_618) == 0x618);



#endif  // GG_MATCH_CORE_TRIVIAL_TU238_METHODS_H
