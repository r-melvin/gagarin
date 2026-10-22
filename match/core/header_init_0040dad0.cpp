// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40DAD0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x886FE0
extern double DAT_00886FE0;
// GLOBAL: GAMEMD 0x7E1AD0
const double DAT_007E1AD0 = 60.0;

// SYNTHETIC: GAMEMD 0x40DAD0
// GLOBAL: GAMEMD 0x887030
double DAT_00887030 = DAT_00886FE0 / DAT_007E1AD0;
// SYNTHETIC: GAMEMD 0x40DAF0
// GLOBAL: GAMEMD 0x887018
double DAT_00887018 = 1.0 / DAT_00887030;
// SYNTHETIC: GAMEMD 0x40DC70
// GLOBAL: GAMEMD 0x887020
HeaderCoordInit DAT_00887020(128, 128, 0);
