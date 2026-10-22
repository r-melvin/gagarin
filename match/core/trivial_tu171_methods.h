// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU171_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU171_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00600660;
struct Obj_00624080;
struct Obj_00624090;
struct Obj_006241C0;
struct Obj_006241E0;

// GLOBAL: GAMEMD 0xAC4848
extern char DAT_00AC4848[];

// FUNCTION: GAMEMD 0x6B9530 (declaration)
void FUN_006B9530(void*, int);

struct Obj_00600660
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x600660
    int FUN_00600660() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00600660, unknown_00) == 0x0);

struct Obj_00624080
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x624080
    Obj_00624080* FUN_00624080();
};
GG_STATIC_ASSERT(offsetof(Obj_00624080, unknown_00) == 0x0);

struct Obj_00624090
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x624090
    void FUN_00624090();
};
GG_STATIC_ASSERT(offsetof(Obj_00624090, unknown_00) == 0x0);

struct Obj_006241C0
{
    char unknown_00[0x8];
    unsigned char unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x6241C0
    unsigned char FUN_006241C0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_006241C0, unknown_08) == 0x8);

struct Obj_006241E0
{
    // FUNCTION: GAMEMD 0x6241E0
    bool FUN_006241E0() const;
};


// FUNCTION: GAMEMD 0x600550
void FUN_00600550(int a1, int a2);
// FUNCTION: GAMEMD 0x603DB0

#endif  // GG_MATCH_CORE_TRIVIAL_TU171_METHODS_H
