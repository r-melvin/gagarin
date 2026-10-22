// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU187_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU187_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00652CD0;
struct Obj_00653830;
struct Obj_00656CA0;
struct Obj_00656DC0;
struct Obj_00656DE0;
struct Obj_00656E70;

// FUNCTION: GAMEMD 0x4A9CA0 (declaration)
bool FUN_004A9CA0(Obj_00653830*, int, int, int, int);

struct Obj_00652CD0
{
    char unknown_00[0x14AC];
    int unknown_14AC;   // +0x14AC
    char unknown_14B0[0x4C];
    int unknown_14FC;   // +0x14FC
    // FUNCTION: GAMEMD 0x652CD0
    void FUN_00652CD0();
};
GG_STATIC_ASSERT(offsetof(Obj_00652CD0, unknown_14AC) == 0x14AC);
GG_STATIC_ASSERT(offsetof(Obj_00652CD0, unknown_14FC) == 0x14FC);

struct Obj_00653830
{
    // FUNCTION: GAMEMD 0x653830
    bool FUN_00653830(int a1, int a2, int a3);
};

struct Obj_00656CA0
{
    char unknown_00[0x14AC];
    int unknown_14AC;   // +0x14AC
    // FUNCTION: GAMEMD 0x656CA0
    bool FUN_00656CA0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00656CA0, unknown_14AC) == 0x14AC);

struct Obj_00656DC0
{
    char unknown_00[0x14AC];
    int unknown_14AC;   // +0x14AC
    int unknown_14B0;   // +0x14B0
    // FUNCTION: GAMEMD 0x656DC0
    int FUN_00656DC0();
};
GG_STATIC_ASSERT(offsetof(Obj_00656DC0, unknown_14AC) == 0x14AC);
GG_STATIC_ASSERT(offsetof(Obj_00656DC0, unknown_14B0) == 0x14B0);

struct Obj_00656DE0
{
    char unknown_00[0x14D8];
    unsigned char unknown_14D8;   // +0x14D8
    // FUNCTION: GAMEMD 0x656DE0
    unsigned char FUN_00656DE0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00656DE0, unknown_14D8) == 0x14D8);

struct Obj_00656E70
{
    char unknown_00[0x14AC];
    int unknown_14AC;   // +0x14AC
    int unknown_14B0;   // +0x14B0
    // FUNCTION: GAMEMD 0x656E70
    int FUN_00656E70();
};
GG_STATIC_ASSERT(offsetof(Obj_00656E70, unknown_14AC) == 0x14AC);
GG_STATIC_ASSERT(offsetof(Obj_00656E70, unknown_14B0) == 0x14B0);


// FUNCTION: GAMEMD 0x6528C0
void __cdecl FUN_006528C0();
// FUNCTION: GAMEMD 0x652910
void __cdecl FUN_00652910();
// FUNCTION: GAMEMD 0x653750
void __stdcall FUN_00653750(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU187_METHODS_H
