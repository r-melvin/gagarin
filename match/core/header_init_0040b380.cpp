// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40B380
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x87F5C0
extern double DAT_0087F5C0;
// GLOBAL: GAMEMD 0x7E1798
const double DAT_007E1798 = 60.0;

// SYNTHETIC: GAMEMD 0x40B380
// GLOBAL: GAMEMD 0x87F648
double DAT_0087F648 = DAT_0087F5C0 / DAT_007E1798;
// SYNTHETIC: GAMEMD 0x40B3A0
// GLOBAL: GAMEMD 0x87F630
double DAT_0087F630 = 1.0 / DAT_0087F648;
// SYNTHETIC: GAMEMD 0x40B520
// GLOBAL: GAMEMD 0x87F638
HeaderCoordInit DAT_0087F638(128, 128, 0);
