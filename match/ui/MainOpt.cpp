// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit MainOpt.cpp. The name is the source-file string at 0x82a2a8
//   in retail gamemd.exe v1.001, passed by the assert at 0x55f9c4 inside this object's
//   code range (0x55f780-0x56170f). Functions are in ascending retail address order.

#include "../core/trivial_tu126_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7ED3B0
extern const double DAT_007ED3B0;
// GLOBAL: GAMEMD 0xABCE40
extern double DAT_00ABCE40;
// GLOBAL: GAMEMD 0xABCF30
extern double DAT_00ABCF30;
// GLOBAL: GAMEMD 0xABCF38
extern int DAT_00ABCF38;
// GLOBAL: GAMEMD 0xABCF3C
extern int DAT_00ABCF3C;
// GLOBAL: GAMEMD 0xABCF40
extern int DAT_00ABCF40;
// GLOBAL: GAMEMD 0xABCF48
extern double DAT_00ABCF48;

// FUNCTION: GAMEMD 0x55F7B0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0055F7B0()
{
    DAT_00ABCF48 = DAT_00ABCE40 / DAT_007ED3B0;
}

// FUNCTION: GAMEMD 0x55F7D0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0055F7D0()
{
    DAT_00ABCF30 = DAT_007E1718 / DAT_00ABCF48;
}

// FUNCTION: GAMEMD 0x55F950
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0055F950()
{
    DAT_00ABCF40 = 0;
    DAT_00ABCF38 = 0x80;
    DAT_00ABCF3C = 0x80;
}

// FUNCTION: GAMEMD 0x55F970
// Tail-calls a method on a global object.
void __cdecl FUN_0055F970()
{
    DAT_00ABCE70.FUN_005FA350();
}
