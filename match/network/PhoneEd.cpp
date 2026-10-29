// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Original translation unit PhoneEd.cpp. The name is the source-file string at 0x836778
//   in retail gamemd.exe v1.001, passed by the assert at 0x630f61 inside this object's
//   code range (0x6309a0-0x631c7f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EFD90
extern const double DAT_007EFD90;
// GLOBAL: GAMEMD 0xAC4AD0
extern double DAT_00AC4AD0;
// GLOBAL: GAMEMD 0xAC4B08
extern double DAT_00AC4B08;
// GLOBAL: GAMEMD 0xAC4B20
extern double DAT_00AC4B20;

// SYNTHETIC: GAMEMD 0x006309D0
// dynamic initializer for DAT_00AC4B20

// GLOBAL: GAMEMD 0x00AC4B20
double DAT_00AC4B20 = DAT_00AC4AD0 / DAT_007EFD90;

// SYNTHETIC: GAMEMD 0x006309F0
// dynamic initializer for DAT_00AC4B08

// GLOBAL: GAMEMD 0x00AC4B08
double DAT_00AC4B08 = DAT_007E1718 / DAT_00AC4B20;

// SYNTHETIC: GAMEMD 0x00630B70
// GLOBAL: GAMEMD 0x00AC4B10
MathTblCoord DAT_00AC4B10;
