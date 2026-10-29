// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU230_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU230_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_006E0ED0;
struct Arg1_006E3300;
struct Arg1_006E3320;
struct Arg1_006E3340;
struct Arg1_006E3360;
struct Arg1_006E3B40;
struct Obj_006E0250;
struct Obj_006E0270;
struct Obj_006E0290;
struct Obj_006E0ED0;
struct Obj_006E0FA0;
struct Obj_006E0FC0;
struct Obj_006E1720;
struct Obj_006E1740;
struct Obj_006E1B90;
struct Obj_006E1BB0;
struct Obj_006E1F90;
struct Obj_006E1F90_30;
struct Obj_006E1FB0;
struct Obj_006E1FD0;
struct Obj_006E2BE0;
struct Obj_006E2C00;
struct Obj_006E2E20;
struct Obj_006E2E40;
struct Obj_006E3300;
struct Obj_006E3320;
struct Obj_006E3340;
struct Obj_006E3360;
struct Obj_006E3890;
struct Obj_006E3B40;
struct Obj_006E4020;

// GLOBAL: GAMEMD 0x87F7E8
extern char DAT_0087F7E8[];
// GLOBAL: GAMEMD 0xA83D10
extern char DAT_00A83D10[];

// FUNCTION: GAMEMD 0x577C90 (declaration)
void FUN_00577C90(void*, int, int);
// FUNCTION: GAMEMD 0x5BF390 (declaration)
void FUN_005BF390(int, bool);
// FUNCTION: GAMEMD 0x65D8E0 (declaration)
bool FUN_0065D8E0(int, int);
// FUNCTION: GAMEMD 0x65EC30 (declaration)
bool FUN_0065EC30(int, int);
// FUNCTION: GAMEMD 0x6F1F30 (declaration)
void FUN_006F1F30(int, int, int);
// FUNCTION: GAMEMD 0x720B20 (declaration)
void FUN_00720B20(void*, int, int);
// FUNCTION: GAMEMD 0x752480 (declaration)
void FUN_00752480(int, int, int);

struct Arg1_006E0ED0
{
    char unknown_00[0x54EC];
    int unknown_54EC;   // +0x54EC
};
GG_STATIC_ASSERT(offsetof(Arg1_006E0ED0, unknown_54EC) == 0x54EC);

struct Arg1_006E3300
{
    char unknown_00[0x565C];
    int unknown_565C;   // +0x565C
};
GG_STATIC_ASSERT(offsetof(Arg1_006E3300, unknown_565C) == 0x565C);

struct Arg1_006E3320
{
    char unknown_00[0x5660];
    int unknown_5660;   // +0x5660
};
GG_STATIC_ASSERT(offsetof(Arg1_006E3320, unknown_5660) == 0x5660);

struct Arg1_006E3340
{
    char unknown_00[0x5664];
    int unknown_5664;   // +0x5664
};
GG_STATIC_ASSERT(offsetof(Arg1_006E3340, unknown_5664) == 0x5664);

struct Arg1_006E3360
{
    char unknown_00[0x5668];
    int unknown_5668;   // +0x5668
};
GG_STATIC_ASSERT(offsetof(Arg1_006E3360, unknown_5668) == 0x5668);

struct Arg1_006E3B40
{
    // FUNCTION: GAMEMD 0x50BCD0
    void FUN_0050BCD0(int);
};

struct Obj_006E0250
{
    char unknown_00[0x90];
    bool unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E0250
    bool FUN_006E0250(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E0250, unknown_90) == 0x90);

struct Obj_006E0270
{
    char unknown_00[0x90];
    bool unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E0270
    bool FUN_006E0270(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E0270, unknown_90) == 0x90);

struct Obj_006E0290
{
    char unknown_00[0x90];
    bool unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E0290
    bool FUN_006E0290(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E0290, unknown_90) == 0x90);

struct Obj_006E0ED0
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E0ED0
    unsigned char FUN_006E0ED0(Arg1_006E0ED0* a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E0ED0, unknown_90) == 0x90);

struct Obj_006E0FA0
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E0FA0
    bool FUN_006E0FA0(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E0FA0, unknown_90) == 0x90);

struct Obj_006E0FC0
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E0FC0
    bool FUN_006E0FC0(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E0FC0, unknown_90) == 0x90);

struct Obj_006E1720
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E1720
    bool FUN_006E1720(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E1720, unknown_90) == 0x90);

struct Obj_006E1740
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E1740
    bool FUN_006E1740(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E1740, unknown_90) == 0x90);

struct Obj_006E1B90
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
};
GG_STATIC_ASSERT(offsetof(Obj_006E1B90, unknown_90) == 0x90);

struct Obj_006E1BB0
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E1BB0
    bool FUN_006E1BB0(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E1BB0, unknown_90) == 0x90);

struct Obj_006E1F90
{
    char unknown_00[0x30];
    Obj_006E1F90_30* unknown_30;   // +0x0030
    // FUNCTION: GAMEMD 0x6E1F90
    unsigned char FUN_006E1F90(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E1F90, unknown_30) == 0x30);

struct Obj_006E1F90_30
{
    // FUNCTION: GAMEMD 0x6F0A70
    void FUN_006F0A70();
};

struct Obj_006E1FB0
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
};
GG_STATIC_ASSERT(offsetof(Obj_006E1FB0, unknown_30) == 0x30);

struct Obj_006E1FD0
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
    char unknown_34[0x10];
    int unknown_44;   // +0x0044
    // FUNCTION: GAMEMD 0x6E1FD0
    unsigned char FUN_006E1FD0(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E1FD0, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_006E1FD0, unknown_44) == 0x44);

struct Obj_006E2BE0
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E2BE0
    bool FUN_006E2BE0(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E2BE0, unknown_90) == 0x90);

struct Obj_006E2C00
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E2C00
    bool FUN_006E2C00(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E2C00, unknown_90) == 0x90);

struct Obj_006E2E20
{
    char unknown_00[0x90];
    float unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E2E20
    bool FUN_006E2E20(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E2E20, unknown_90) == 0x90);

struct Obj_006E2E40
{
    char unknown_00[0x90];
    float unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E2E40
    bool FUN_006E2E40(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E2E40, unknown_90) == 0x90);

struct Obj_006E3300
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E3300
    unsigned char FUN_006E3300(Arg1_006E3300* a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E3300, unknown_90) == 0x90);

struct Obj_006E3320
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E3320
    unsigned char FUN_006E3320(Arg1_006E3320* a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E3320, unknown_90) == 0x90);

struct Obj_006E3340
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E3340
    unsigned char FUN_006E3340(Arg1_006E3340* a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E3340, unknown_90) == 0x90);

struct Obj_006E3360
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E3360
    unsigned char FUN_006E3360(Arg1_006E3360* a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E3360, unknown_90) == 0x90);

struct Obj_006E3890
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
    char unknown_34[0x10];
    int unknown_44;   // +0x0044
    // FUNCTION: GAMEMD 0x6E3890
    unsigned char FUN_006E3890(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E3890, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_006E3890, unknown_44) == 0x44);

struct Obj_006E3B40
{
    char unknown_00[0x90];
    int unknown_90;   // +0x0090
    // FUNCTION: GAMEMD 0x6E3B40
    unsigned char FUN_006E3B40(Arg1_006E3B40* a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_006E3B40, unknown_90) == 0x90);

struct Obj_006E4020
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
    char unknown_34[0x5C];
    int unknown_90;   // +0x0090
};
GG_STATIC_ASSERT(offsetof(Obj_006E4020, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_006E4020, unknown_90) == 0x90);



// FUNCTION: GAMEMD 0x6E0040
bool __stdcall FUN_006E0040(int a1, int a2, int a3, int a4);
// FUNCTION: GAMEMD 0x6E1B90
bool FUN_006E1B90(Obj_006E1B90* a1, int a2, int a3, int a4, int a5, int a6);
// FUNCTION: GAMEMD 0x6E1FB0
unsigned char FUN_006E1FB0(Obj_006E1FB0* a1, int a2, int a3, int a4, int a5, int a6);
// FUNCTION: GAMEMD 0x6E21D0
bool __stdcall FUN_006E21D0(int a1, int a2, int a3, int a4);
// FUNCTION: GAMEMD 0x6E2950
bool FUN_006E2950(int a1, int a2, int a3, int a4, int a5, int a6);
// FUNCTION: GAMEMD 0x6E3B20
bool __stdcall FUN_006E3B20(int a1, int a2, int a3, int a4);
// FUNCTION: GAMEMD 0x6E4020
unsigned char FUN_006E4020(Obj_006E4020* a1, int a2, int a3, int a4, int a5, int a6);

#endif  // GG_MATCH_CORE_TRIVIAL_TU230_METHODS_H
