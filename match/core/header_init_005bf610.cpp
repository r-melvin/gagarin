// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x5BF610
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0xABF380
extern double DAT_00ABF380;
// GLOBAL: GAMEMD 0x7EE0A0
const double DAT_007EE0A0 = 60.0;

// SYNTHETIC: GAMEMD 0x5BF610
// GLOBAL: GAMEMD 0xABF3E8
double DAT_00ABF3E8 = DAT_00ABF380 / DAT_007EE0A0;
// SYNTHETIC: GAMEMD 0x5BF630
// GLOBAL: GAMEMD 0xABF3D0
double DAT_00ABF3D0 = 1.0 / DAT_00ABF3E8;
// SYNTHETIC: GAMEMD 0x5BF7B0
// GLOBAL: GAMEMD 0xABF3D8
HeaderCoordInit DAT_00ABF3D8(128, 128, 0);
