// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU207_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU207_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0069ACC0;
struct Obj_0069ACC0_18C;
struct Obj_0069ADE0;
struct Obj_0069B700;
struct Obj_0069B740;

struct Obj_0069ACC0
{
    char unknown_00[0x18C];
    Obj_0069ACC0_18C* unknown_18C;   // +0x018C
    // FUNCTION: GAMEMD 0x69ACC0
    int FUN_0069ACC0() const;
    bool FUN_0069AC30(int value); // GAMEMD 0x69AC30; one stack argument at0x683BB6
};
GG_STATIC_ASSERT(offsetof(Obj_0069ACC0, unknown_18C) == 0x18C);

struct Obj_0069ACC0_18C
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Obj_0069ACC0_18C, unknown_00) == 0x0);

struct Obj_0069ADE0
{
    char unknown_00[0x17C];
    unsigned char unknown_17C;   // +0x017C
    // FUNCTION: GAMEMD 0x69ADE0
    void FUN_0069ADE0(unsigned char a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0069ADE0, unknown_17C) == 0x17C);

struct Obj_0069B700
{
    char unknown_00[0x174];
    int unknown_174;   // +0x0174
    int unknown_178;   // +0x0178
    // FUNCTION: GAMEMD 0x69B700
    int FUN_0069B700();
};
GG_STATIC_ASSERT(offsetof(Obj_0069B700, unknown_174) == 0x174);
GG_STATIC_ASSERT(offsetof(Obj_0069B700, unknown_178) == 0x178);

struct Obj_0069B740
{
    char unknown_00[0x164];
    int unknown_164;   // +0x0164
    int unknown_168;   // +0x0168
    // FUNCTION: GAMEMD 0x69B740
    int FUN_0069B740();
};
GG_STATIC_ASSERT(offsetof(Obj_0069B740, unknown_164) == 0x164);
GG_STATIC_ASSERT(offsetof(Obj_0069B740, unknown_168) == 0x168);


// FUNCTION: GAMEMD 0x697B60
void __cdecl FUN_00697B60();
// FUNCTION: GAMEMD 0x69B8B0
void __stdcall FUN_0069B8B0(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU207_METHODS_H
