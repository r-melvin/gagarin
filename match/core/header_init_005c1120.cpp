// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group at 0x5C1120, 0x5C1140 and 0x5C12C0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order. The divisor at 0x7EE268 reads 60.0 (ghidra memory read).
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0xABF420
extern double DAT_00ABF420;
// GLOBAL: GAMEMD 0x7EE268
const double DAT_007EE268 = 60.0;

// SYNTHETIC: GAMEMD 0x5C1120
// GLOBAL: GAMEMD 0xABF490
double DAT_00ABF490 = DAT_00ABF420 / DAT_007EE268;
// SYNTHETIC: GAMEMD 0x5C1140
// GLOBAL: GAMEMD 0xABF458
double DAT_00ABF458 = 1.0 / DAT_00ABF490;
// SYNTHETIC: GAMEMD 0x5C12C0
// GLOBAL: GAMEMD 0xABF480
HeaderCoordInit DAT_00ABF480(128, 128, 0);
