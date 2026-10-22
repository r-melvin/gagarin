// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40FF90
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x887668
extern double DAT_00887668;
// GLOBAL: GAMEMD 0x7E1F10
const double DAT_007E1F10 = 60.0;

// SYNTHETIC: GAMEMD 0x40FF90
// GLOBAL: GAMEMD 0x8876B8
double DAT_008876B8 = DAT_00887668 / DAT_007E1F10;
// SYNTHETIC: GAMEMD 0x40FFB0
// GLOBAL: GAMEMD 0x8876A0
double DAT_008876A0 = 1.0 / DAT_008876B8;
// SYNTHETIC: GAMEMD 0x410130
// GLOBAL: GAMEMD 0x8876A8
HeaderCoordInit DAT_008876A8(128, 128, 0);
