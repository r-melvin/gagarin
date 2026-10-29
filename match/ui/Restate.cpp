// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Original translation unit Restate.cpp. The name is the source-file string at 0x839740
//   in retail gamemd.exe v1.001, passed by the assert at 0x65f611 inside this object's
//   code range (0x65f330-0x65f79f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F0970
extern const double DAT_007F0970;
// GLOBAL: GAMEMD 0xB04CC8
extern double DAT_00B04CC8;
// GLOBAL: GAMEMD 0xB04D00
extern double DAT_00B04D00;
// GLOBAL: GAMEMD 0xB04D18
extern double DAT_00B04D18;

// SYNTHETIC: GAMEMD 0x0065F360
// dynamic initializer for DAT_00B04D18

// GLOBAL: GAMEMD 0x00B04D18
double DAT_00B04D18 = DAT_00B04CC8 / DAT_007F0970;

// SYNTHETIC: GAMEMD 0x0065F380
// dynamic initializer for DAT_00B04D00

// GLOBAL: GAMEMD 0x00B04D00
double DAT_00B04D00 = DAT_007E1718 / DAT_00B04D18;

// SYNTHETIC: GAMEMD 0x0065F500
// GLOBAL: GAMEMD 0x00B04D08
MathTblCoord DAT_00B04D08;
