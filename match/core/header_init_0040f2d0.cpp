// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40F2D0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x887490
extern double DAT_00887490;
// GLOBAL: GAMEMD 0x7E1E70
const double DAT_007E1E70 = 60.0;

// SYNTHETIC: GAMEMD 0x40F2D0
// GLOBAL: GAMEMD 0x8874F8
double DAT_008874F8 = DAT_00887490 / DAT_007E1E70;
// SYNTHETIC: GAMEMD 0x40F2F0
// GLOBAL: GAMEMD 0x8874E0
double DAT_008874E0 = 1.0 / DAT_008874F8;
// SYNTHETIC: GAMEMD 0x40F470
// GLOBAL: GAMEMD 0x8874E8
HeaderCoordInit DAT_008874E8(128, 128, 0);
