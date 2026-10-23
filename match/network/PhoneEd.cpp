// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit PhoneEd.cpp. The name is the source-file string at 0x836778
//   in retail gamemd.exe v1.001, passed by the assert at 0x630f61 inside this object's
//   code range (0x6309a0-0x631c7f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EFD90
extern const double DAT_007EFD90;
// GLOBAL: GAMEMD 0xAC4AD0
extern double DAT_00AC4AD0;
// GLOBAL: GAMEMD 0xAC4B08
extern double DAT_00AC4B08;
// GLOBAL: GAMEMD 0xAC4B10
extern int DAT_00AC4B10;
// GLOBAL: GAMEMD 0xAC4B14
extern int DAT_00AC4B14;
// GLOBAL: GAMEMD 0xAC4B18
extern int DAT_00AC4B18;
// GLOBAL: GAMEMD 0xAC4B20
extern double DAT_00AC4B20;

// FUNCTION: GAMEMD 0x6309D0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006309D0()
{
    DAT_00AC4B20 = DAT_00AC4AD0 / DAT_007EFD90;
}

// FUNCTION: GAMEMD 0x6309F0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006309F0()
{
    DAT_00AC4B08 = DAT_007E1718 / DAT_00AC4B20;
}

// FUNCTION: GAMEMD 0x630B70
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00630B70()
{
    DAT_00AC4B18 = 0;
    DAT_00AC4B10 = 0x80;
    DAT_00AC4B14 = 0x80;
}
