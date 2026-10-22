// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_AI_TRIVIAL_TU235_B_METHODS_H
#define GG_MATCH_AI_TRIVIAL_TU235_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_006EDA90;
struct Arg1_006EDAC0;
struct Arg1_006EDAF0;
struct Arg1_006EDB20;
struct Arg1_006EDE10;
struct Arg1_006EDEC0;
struct Gptr_00A8B230;
struct Obj_006EDA90;
struct Obj_006EDAC0;
struct Obj_006EDAF0;
struct Obj_006EDB20;
struct Obj_006EDE10;
struct Obj_006EDE10_28;
struct Obj_006EDE60;
struct Obj_006EDEC0;

// GLOBAL: GAMEMD 0xA83D4C
extern int DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8B230
extern Gptr_00A8B230* DAT_00A8B230;

// FUNCTION: GAMEMD 0x4FCBD0 (declaration)
void FUN_004FCBD0(int, int, int);
// FUNCTION: GAMEMD 0x5BF260 (declaration)
void FUN_005BF260(int, int, int, int, int);

struct Arg1_006EDA90
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDA90, unknown_04) == 0x4);

struct Arg1_006EDAC0
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDAC0, unknown_04) == 0x4);

struct Arg1_006EDAF0
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDAF0, unknown_04) == 0x4);

struct Arg1_006EDB20
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDB20, unknown_04) == 0x4);

struct Arg1_006EDE10
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDE10, unknown_04) == 0x4);

struct Arg1_006EDEC0
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDEC0, unknown_04) == 0x4);

struct Gptr_00A8B230
{
    // FUNCTION: GAMEMD 0x689670
    void FUN_00689670(int, int);
    // FUNCTION: GAMEMD 0x689910
    void FUN_00689910(int, int);
};

struct Obj_006EDA90
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDA90
    void FUN_006EDA90(Arg1_006EDA90* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDA90, unknown_80) == 0x80);

struct Obj_006EDAC0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDAC0
    void FUN_006EDAC0(Arg1_006EDAC0* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDAC0, unknown_80) == 0x80);

struct Obj_006EDAF0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDAF0
    void FUN_006EDAF0(Arg1_006EDAF0* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDAF0, unknown_80) == 0x80);

struct Obj_006EDB20
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDB20
    void FUN_006EDB20(Arg1_006EDB20* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDB20, unknown_80) == 0x80);

struct Obj_006EDE10
{
    char unknown_00[0x28];
    Obj_006EDE10_28* unknown_28;   // +0x0028
    char unknown_2C[0x54];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDE10
    void FUN_006EDE10(Arg1_006EDE10* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDE10, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_006EDE10, unknown_80) == 0x80);

struct Obj_006EDE10_28
{
    // FUNCTION: GAMEMD 0x6915A0
    void FUN_006915A0(int);
};

struct Obj_006EDE60
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EDE60, unknown_80) == 0x80);

struct Obj_006EDEC0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EDEC0, unknown_80) == 0x80);


// FUNCTION: GAMEMD 0x6EDE60
void FUN_006EDE60(Obj_006EDE60* a1, int a2, int a3, int a4);
// FUNCTION: GAMEMD 0x6EDEC0
void FUN_006EDEC0(Obj_006EDEC0* a1, int a2, Arg1_006EDEC0* a3, int a4);

#endif  // GG_MATCH_AI_TRIVIAL_TU235_B_METHODS_H
