// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40C5C0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x87F6F8
extern double DAT_0087F6F8;
// GLOBAL: GAMEMD 0x7E18A8
const double DAT_007E18A8 = 60.0;

// SYNTHETIC: GAMEMD 0x40C5C0
// GLOBAL: GAMEMD 0x87F748
double DAT_0087F748 = DAT_0087F6F8 / DAT_007E18A8;
// SYNTHETIC: GAMEMD 0x40C5E0
// GLOBAL: GAMEMD 0x87F730
double DAT_0087F730 = 1.0 / DAT_0087F748;
// SYNTHETIC: GAMEMD 0x40C760
// GLOBAL: GAMEMD 0x87F738
HeaderCoordInit DAT_0087F738(128, 128, 0);
