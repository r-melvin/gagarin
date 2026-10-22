// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU040_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU040_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0046AFD0;
struct Obj_0046B030;
struct Obj_0046B030_AC;
struct Obj_0046B540;
struct Obj_0046B550;
struct Obj_0046B5A0;
struct Obj_0046B5B0;

// GLOBAL: GAMEMD 0xABCD3C
extern int DAT_00ABCD3C;

// Import InterlockedIncrement from KERNEL32.dll (IAT slot 0x7E11C8)
extern "C" __declspec(dllimport) void __stdcall InterlockedIncrement(int);

struct Obj_0046AFD0
{
    // FUNCTION: GAMEMD 0x46AFD0
    void FUN_0046AFD0(int a1);
};

struct Obj_0046B030
{
    char unknown_00[0xAC];
    Obj_0046B030_AC* unknown_AC;   // +0x00AC
    // FUNCTION: GAMEMD 0x46B030
    bool FUN_0046B030() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0046B030, unknown_AC) == 0xAC);

struct Obj_0046B030_AC
{
    char unknown_00[0x2DC];
    int unknown_2DC;   // +0x02DC
};
GG_STATIC_ASSERT(offsetof(Obj_0046B030_AC, unknown_2DC) == 0x2DC);

struct Obj_0046B540
{
    // FUNCTION: GAMEMD 0x46B540
    int FUN_0046B540() const;
};

struct Obj_0046B550
{
    // FUNCTION: GAMEMD 0x46B550
    int FUN_0046B550() const;
};

struct Obj_0046B5A0
{
    char unknown_00[0x10C];
    int unknown_10C;   // +0x010C
    // FUNCTION: GAMEMD 0x46B5A0
    void FUN_0046B5A0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0046B5A0, unknown_10C) == 0x10C);

struct Obj_0046B5B0
{
    char unknown_00[0xAC];
    int unknown_AC;   // +0x00AC
    // FUNCTION: GAMEMD 0x46B5B0
    int FUN_0046B5B0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0046B5B0, unknown_AC) == 0xAC);


// FUNCTION: GAMEMD 0x4666B0
void __cdecl FUN_004666B0();

#endif  // GG_MATCH_CORE_TRIVIAL_TU040_METHODS_H
