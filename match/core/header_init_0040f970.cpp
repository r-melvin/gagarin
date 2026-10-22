// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40F970
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x887518
extern double DAT_00887518;
// GLOBAL: GAMEMD 0x7E1EC0
const double DAT_007E1EC0 = 60.0;

// SYNTHETIC: GAMEMD 0x40F970
// GLOBAL: GAMEMD 0x887588
double DAT_00887588 = DAT_00887518 / DAT_007E1EC0;
// SYNTHETIC: GAMEMD 0x40F990
// GLOBAL: GAMEMD 0x887550
double DAT_00887550 = 1.0 / DAT_00887588;
// SYNTHETIC: GAMEMD 0x40FB10
// GLOBAL: GAMEMD 0x887558
HeaderCoordInit DAT_00887558(128, 128, 0);
