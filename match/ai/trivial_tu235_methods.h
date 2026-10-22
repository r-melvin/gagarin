// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_AI_TRIVIAL_TU235_METHODS_H
#define GG_MATCH_AI_TRIVIAL_TU235_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_006EDEF0;
struct Obj_006EDE40;
struct Obj_006EDE80;
struct Obj_006EDEF0;
struct Obj_006EDF90;
struct Obj_006EDF90_2C;
struct Obj_006EDFB0;
struct Obj_006EDFB0_2C;
struct Obj_006EE1B0;
struct Obj_006EE1D0;
struct Obj_006F0430;
struct Obj_006F0440;

// GLOBAL: GAMEMD 0x87F7E8
extern char DAT_0087F7E8[];
// GLOBAL: GAMEMD 0xA83D10
extern char DAT_00A83D10[];
// GLOBAL: GAMEMD 0xA83D4C
extern int DAT_00A83D4C;

// FUNCTION: GAMEMD 0x4FC9E0 (declaration)
void FUN_004FC9E0(int, int, int);
// FUNCTION: GAMEMD 0x577BB0 (declaration)
void FUN_00577BB0(void*, int, int);
// FUNCTION: GAMEMD 0x577F30 (declaration)
void FUN_00577F30(void*, int, int);
// FUNCTION: GAMEMD 0x720B20 (declaration)
void FUN_00720B20(void*, int, int);

struct Arg1_006EDEF0
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDEF0, unknown_04) == 0x4);

struct Obj_006EDE40
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EDE40, unknown_80) == 0x80);

struct Obj_006EDE80
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDE80
    void FUN_006EDE80(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDE80, unknown_80) == 0x80);

struct Obj_006EDEF0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EDEF0, unknown_80) == 0x80);

struct Obj_006EDF90
{
    char unknown_00[0x2C];
    Obj_006EDF90_2C* unknown_2C;   // +0x002C
    char unknown_30[0x50];
    bool unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDF90
    void FUN_006EDF90(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDF90, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(Obj_006EDF90, unknown_80) == 0x80);

struct Obj_006EDF90_2C
{
    char unknown_00[0x1EE];
    bool unknown_1EE;   // +0x01EE
};
GG_STATIC_ASSERT(offsetof(Obj_006EDF90_2C, unknown_1EE) == 0x1EE);

struct Obj_006EDFB0
{
    char unknown_00[0x2C];
    Obj_006EDFB0_2C* unknown_2C;   // +0x002C
    char unknown_30[0x50];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDFB0
    void FUN_006EDFB0(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDFB0, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(Obj_006EDFB0, unknown_80) == 0x80);

struct Obj_006EDFB0_2C
{
    char unknown_00[0x250];
    int unknown_250;   // +0x0250
};
GG_STATIC_ASSERT(offsetof(Obj_006EDFB0_2C, unknown_250) == 0x250);

struct Obj_006EE1B0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EE1B0, unknown_80) == 0x80);

struct Obj_006EE1D0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EE1D0, unknown_80) == 0x80);

struct Obj_006F0430
{
    // FUNCTION: GAMEMD 0x6F0430
    int FUN_006F0430() const;
};

struct Obj_006F0440
{
    // FUNCTION: GAMEMD 0x6F0440
    int FUN_006F0440() const;
};


// FUNCTION: GAMEMD 0x6EDE40
void FUN_006EDE40(Obj_006EDE40* a1, int a2, int a3, int a4);
// FUNCTION: GAMEMD 0x6EDEF0
void FUN_006EDEF0(Obj_006EDEF0* a1, int a2, Arg1_006EDEF0* a3, int a4);
// FUNCTION: GAMEMD 0x6EE1B0
void FUN_006EE1B0(Obj_006EE1B0* a1, int a2, int a3, int a4);
// FUNCTION: GAMEMD 0x6EE1D0
void FUN_006EE1D0(Obj_006EE1D0* a1, int a2, int a3, int a4);

#endif  // GG_MATCH_AI_TRIVIAL_TU235_METHODS_H
