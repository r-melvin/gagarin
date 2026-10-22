// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU144_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU144_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005C1CB0;
struct Obj_005C36F0;
struct Obj_005C3700;
struct Obj_005C42C0;
struct Obj_005C4EE0;
struct Obj_005C4EF0;
struct Obj_005C4F00;

// FUNCTION: GAMEMD 0x5D7570 (declaration)
void __cdecl FUN_005D7570();

struct Obj_005C1CB0
{
    char unknown_00[0x340];
    unsigned char unknown_340;   // +0x0340
    // FUNCTION: GAMEMD 0x5C1CB0
    void FUN_005C1CB0();
};
GG_STATIC_ASSERT(offsetof(Obj_005C1CB0, unknown_340) == 0x340);

struct Obj_005C36F0
{
    // FUNCTION: GAMEMD 0x5C36F0
    void FUN_005C36F0();
};

struct Obj_005C3700
{
    // FUNCTION: GAMEMD 0x5C3700
    bool FUN_005C3700() const;
};

struct Obj_005C42C0
{
    // FUNCTION: GAMEMD 0x5C42C0
    int FUN_005C42C0() const;
};

struct Obj_005C4EE0
{
    // FUNCTION: GAMEMD 0x5C4EE0
    bool FUN_005C4EE0() const;
};

struct Obj_005C4EF0
{
    // FUNCTION: GAMEMD 0x5C4EF0
    bool FUN_005C4EF0() const;
};

struct Obj_005C4F00
{
    // FUNCTION: GAMEMD 0x5C4F00
    bool FUN_005C4F00() const;
};



#endif  // GG_MATCH_CORE_TRIVIAL_TU144_METHODS_H
