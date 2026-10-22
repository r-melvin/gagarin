// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Restate.cpp. The name is the source-file string at 0x839740
//   in retail gamemd.exe v1.001, passed by the assert at 0x65f611 inside this object's
//   code range (0x65f330-0x65f79f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F0970
extern const double DAT_007F0970;
// GLOBAL: GAMEMD 0xB04CC8
extern double DAT_00B04CC8;
// GLOBAL: GAMEMD 0xB04D00
extern double DAT_00B04D00;
// GLOBAL: GAMEMD 0xB04D08
extern int DAT_00B04D08;
// GLOBAL: GAMEMD 0xB04D0C
extern int DAT_00B04D0C;
// GLOBAL: GAMEMD 0xB04D10
extern int DAT_00B04D10;
// GLOBAL: GAMEMD 0xB04D18
extern double DAT_00B04D18;

// FUNCTION: GAMEMD 0x65F360
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0065F360()
{
    DAT_00B04D18 = DAT_00B04CC8 / DAT_007F0970;
}

// FUNCTION: GAMEMD 0x65F380
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0065F380()
{
    DAT_00B04D00 = DAT_007E1718 / DAT_00B04D18;
}

// FUNCTION: GAMEMD 0x65F500
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0065F500()
{
    DAT_00B04D10 = 0;
    DAT_00B04D08 = 0x80;
    DAT_00B04D0C = 0x80;
}
