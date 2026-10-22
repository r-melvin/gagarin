// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit SerialEd.cpp. The name is the source-file string at 0x83ec28
//   in retail gamemd.exe v1.001, passed by the assert at 0x695f23 inside this object's
//   code range (0x6954e0-0x696d1f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F1180
extern const double DAT_007F1180;
// GLOBAL: GAMEMD 0xB05768
extern double DAT_00B05768;
// GLOBAL: GAMEMD 0xB057A0
extern double DAT_00B057A0;
// GLOBAL: GAMEMD 0xB057A8
extern int DAT_00B057A8;
// GLOBAL: GAMEMD 0xB057AC
extern int DAT_00B057AC;
// GLOBAL: GAMEMD 0xB057B0
extern int DAT_00B057B0;
// GLOBAL: GAMEMD 0xB057B8
extern double DAT_00B057B8;

// FUNCTION: GAMEMD 0x695510
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00695510()
{
    DAT_00B057B8 = DAT_00B05768 / DAT_007F1180;
}

// FUNCTION: GAMEMD 0x695530
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00695530()
{
    DAT_00B057A0 = DAT_007E1718 / DAT_00B057B8;
}

// FUNCTION: GAMEMD 0x6956B0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_006956B0()
{
    DAT_00B057B0 = 0;
    DAT_00B057A8 = 0x80;
    DAT_00B057AC = 0x80;
}
