// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Skirmish.cpp. The name is the source-file string at 0x83fc4c
//   in retail gamemd.exe v1.001, passed by the assert at 0x6acc2a inside this object's
//   code range (0x6ac970-0x6aef0f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7F3138
extern const double DAT_007F3138;
// GLOBAL: GAMEMD 0xB0B540
extern double DAT_00B0B540;
// GLOBAL: GAMEMD 0xB0B578
extern double DAT_00B0B578;
// GLOBAL: GAMEMD 0xB0B590
extern double DAT_00B0B590;

// SYNTHETIC: GAMEMD 0x006AC9A0
// dynamic initializer for DAT_00B0B590

// GLOBAL: GAMEMD 0x00B0B590
double DAT_00B0B590 = DAT_00B0B540 / DAT_007F3138;

// SYNTHETIC: GAMEMD 0x006AC9C0
// dynamic initializer for DAT_00B0B578

// GLOBAL: GAMEMD 0x00B0B578
double DAT_00B0B578 = 1.0 / DAT_00B0B590;

// SYNTHETIC: GAMEMD 0x006ACB40
// GLOBAL: GAMEMD 0x00B0B580
MathTblCoord DAT_00B0B580;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F3138
extern const double DAT_007F3138 = 60.0;
// END defined globals
