// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Original translation unit NullDlg.CPP. The name is the source-file string at 0x831e84
//   in retail gamemd.exe v1.001, passed by the assert at 0x5ef768 inside this object's
//   code range (0x5ef2f0-0x5f13cf). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../core/mathtbl_init_shapes.h"
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7EEFB8
extern const double DAT_007EEFB8;
// GLOBAL: GAMEMD 0xAC1210
extern double DAT_00AC1210;
// GLOBAL: GAMEMD 0xAC1248
extern double DAT_00AC1248;
// GLOBAL: GAMEMD 0xAC1260
extern double DAT_00AC1260;

// SYNTHETIC: GAMEMD 0x005EF320
// dynamic initializer for DAT_00AC1260

// GLOBAL: GAMEMD 0x00AC1260
double DAT_00AC1260 = DAT_00AC1210 / DAT_007EEFB8;

// SYNTHETIC: GAMEMD 0x005EF340
// dynamic initializer for DAT_00AC1248

// GLOBAL: GAMEMD 0x00AC1248
double DAT_00AC1248 = 1.0 / DAT_00AC1260;

// SYNTHETIC: GAMEMD 0x005EF4C0
// GLOBAL: GAMEMD 0x00AC1250
MathTblCoord DAT_00AC1250;
