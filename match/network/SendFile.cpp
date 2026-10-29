// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit SendFile.CPP. The name is the source-file string at 0x83e9c8
//   in retail gamemd.exe v1.001, passed by the assert at 0x6942b7 inside this object's
//   code range (0x693960-0x6954df). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7F1170
extern const double DAT_007F1170;
// GLOBAL: GAMEMD 0xB056E8
extern double DAT_00B056E8;
// GLOBAL: GAMEMD 0xB05720
extern double DAT_00B05720;
// GLOBAL: GAMEMD 0xB05738
extern double DAT_00B05738;

// SYNTHETIC: GAMEMD 0x00693990
// dynamic initializer for DAT_00B05738

// GLOBAL: GAMEMD 0x00B05738
double DAT_00B05738 = DAT_00B056E8 / DAT_007F1170;

// SYNTHETIC: GAMEMD 0x006939B0
// dynamic initializer for DAT_00B05720

// GLOBAL: GAMEMD 0x00B05720
double DAT_00B05720 = 1.0 / DAT_00B05738;

// SYNTHETIC: GAMEMD 0x00693B30
// GLOBAL: GAMEMD 0x00B05728
MathTblCoord DAT_00B05728;
