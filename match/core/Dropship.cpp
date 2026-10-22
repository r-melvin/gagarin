// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Dropship.cpp. The name is the source-file string at 0x8204a8
//   in retail gamemd.exe v1.001, passed by the assert at 0x4b8c61 inside this object's
//   code range (0x4b67a0-0x4ba3af). Functions are in ascending retail address order.

#include "empty_function_family_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E8370
extern const double DAT_007E8370;
// GLOBAL: GAMEMD 0x8A08A8
extern double DAT_008A08A8;
// GLOBAL: GAMEMD 0x8A0900
extern double DAT_008A0900;
// GLOBAL: GAMEMD 0x8A0908
extern int DAT_008A0908;
// GLOBAL: GAMEMD 0x8A090C
extern int DAT_008A090C;
// GLOBAL: GAMEMD 0x8A0910
extern int DAT_008A0910;
// GLOBAL: GAMEMD 0x8A0918
extern double DAT_008A0918;

// FUNCTION: GAMEMD 0x4B67D0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_004B67D0()
{
    DAT_008A0918 = DAT_008A08A8 / DAT_007E8370;
}

// FUNCTION: GAMEMD 0x4B67F0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_004B67F0()
{
    DAT_008A0900 = DAT_007E1718 / DAT_008A0918;
}

// FUNCTION: GAMEMD 0x4B6970
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_004B6970()
{
    DAT_008A0910 = 0;
    DAT_008A0908 = 0x80;
    DAT_008A090C = 0x80;
}

// FUNCTION: GAMEMD 0x004B69D0
void FUN_004B69D0()
{
}
