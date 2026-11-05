// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU237_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU237_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

struct Arg1_0070F000;
struct Obj_006F9DB0_21C;
struct Obj_00705D30;
struct Obj_00705D30_514;
struct Obj_007094E0;
struct Obj_0070C5D0_274;
struct Obj_0070DCE0;
struct Obj_0070DE20;
struct Obj_0070F000;
struct Obj_0070FE40;

#include "_layout/map_0087f7e8.h"

// FUNCTION: GAMEMD 0x6562D0 (declaration)
void FUN_006562D0(void*, int, int);

struct Arg1_0070F000
{
    char unknown_00[0xC];
    char unknown_0C;   // +0x000C
};
GG_STATIC_ASSERT(offsetof(Arg1_0070F000, unknown_0C) == 0xC);



struct Obj_006F9DB0_21C
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
};
GG_STATIC_ASSERT(offsetof(Obj_006F9DB0_21C, unknown_30) == 0x30);





struct Obj_00705D30
{
    char unknown_00[0x514];
    Obj_00705D30_514* unknown_514;   // +0x0514
    // FUNCTION: GAMEMD 0x705D30
    unsigned char FUN_00705D30();
};
GG_STATIC_ASSERT(offsetof(Obj_00705D30, unknown_514) == 0x514);

struct Obj_00705D30_514
{
    // FUNCTION: GAMEMD 0x636DC0
    int FUN_00636DC0();
};


struct Obj_007094E0
{
    char unknown_00[0xAC];
    int unknown_AC;   // +0x00AC
    // FUNCTION: GAMEMD 0x7094E0
    int FUN_007094E0();
};
GG_STATIC_ASSERT(offsetof(Obj_007094E0, unknown_AC) == 0xAC);






struct Obj_0070C5D0_274
{
    char unknown_00[0x28];
    int unknown_28;   // +0x0028
};
GG_STATIC_ASSERT(offsetof(Obj_0070C5D0_274, unknown_28) == 0x28);




struct Obj_0070DCE0
{
    char unknown_00[0x124];
    int unknown_124;   // +0x0124
    // FUNCTION: GAMEMD 0x70DCE0
    bool FUN_0070DCE0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0070DCE0, unknown_124) == 0x124);


struct Obj_0070DE20
{
    char unknown_00[0x144];
    int unknown_144;   // +0x0144
    // FUNCTION: GAMEMD 0x70DE20
    void FUN_0070DE20(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0070DE20, unknown_144) == 0x144);

struct Obj_0070F000
{
    // FUNCTION: GAMEMD 0x70F000
    int FUN_0070F000(Arg1_0070F000* a1) const;
};








struct Obj_0070FE40
{
    char unknown_00[0x1D0];
    int unknown_1D0;   // +0x01D0
    // FUNCTION: GAMEMD 0x70FE40
    void FUN_0070FE40(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0070FE40, unknown_1D0) == 0x1D0);


// FUNCTION: GAMEMD 0x6FF950
void __cdecl FUN_006FF950();
// FUNCTION: GAMEMD 0x709460
int __stdcall FUN_00709460(int a1);
// FUNCTION: GAMEMD 0x709800
int __stdcall FUN_00709800(int a1);
// FUNCTION: GAMEMD 0x70CCF0
void FUN_0070CCF0(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU237_METHODS_H
