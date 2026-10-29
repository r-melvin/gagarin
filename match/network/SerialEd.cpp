// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Original translation unit SerialEd.cpp. The name is the source-file string at 0x83ec28
//   in retail gamemd.exe v1.001, passed by the assert at 0x695f23 inside this object's
//   code range (0x6954e0-0x696d1f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7F1180
extern const double DAT_007F1180;
// GLOBAL: GAMEMD 0xB05768
extern double DAT_00B05768;
// GLOBAL: GAMEMD 0xB057A0
extern double DAT_00B057A0;
// GLOBAL: GAMEMD 0xB057B8
extern double DAT_00B057B8;

// SYNTHETIC: GAMEMD 0x00695510
// dynamic initializer for DAT_00B057B8

// GLOBAL: GAMEMD 0x00B057B8
double DAT_00B057B8 = DAT_00B05768 / DAT_007F1180;

// SYNTHETIC: GAMEMD 0x00695530
// dynamic initializer for DAT_00B057A0

// GLOBAL: GAMEMD 0x00B057A0
double DAT_00B057A0 = 1.0 / DAT_00B057B8;

// SYNTHETIC: GAMEMD 0x006956B0
// GLOBAL: GAMEMD 0x00B057A8
MathTblCoord DAT_00B057A8;
