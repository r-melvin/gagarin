// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x5BEB00
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0xABF300
extern double DAT_00ABF300;
// GLOBAL: GAMEMD 0x7EE090
const double DAT_007EE090 = 60.0;

// SYNTHETIC: GAMEMD 0x5BEB00
// GLOBAL: GAMEMD 0xABF350
double DAT_00ABF350 = DAT_00ABF300 / DAT_007EE090;
// SYNTHETIC: GAMEMD 0x5BEB20
// GLOBAL: GAMEMD 0xABF338
double DAT_00ABF338 = 1.0 / DAT_00ABF350;
// SYNTHETIC: GAMEMD 0x5BECA0
// GLOBAL: GAMEMD 0xABF340
HeaderCoordInit DAT_00ABF340(128, 128, 0);
