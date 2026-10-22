// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40DDF0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x887050
extern double DAT_00887050;
// GLOBAL: GAMEMD 0x7E1AE0
const double DAT_007E1AE0 = 60.0;

// SYNTHETIC: GAMEMD 0x40DDF0
// GLOBAL: GAMEMD 0x887268
double DAT_00887268 = DAT_00887050 / DAT_007E1AE0;
// SYNTHETIC: GAMEMD 0x40DE10
// GLOBAL: GAMEMD 0x8871F0
double DAT_008871F0 = 1.0 / DAT_00887268;
// SYNTHETIC: GAMEMD 0x40DF90
// GLOBAL: GAMEMD 0x8871F8
HeaderCoordInit DAT_008871F8(128, 128, 0);
