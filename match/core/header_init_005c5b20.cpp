// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group at 0x5C5B20, 0x5C5B40 and 0x5C5CC0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order. The divisor at 0x7EE410 reads 60.0 (ghidra memory read).
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0xABF4C0
extern double DAT_00ABF4C0;
// GLOBAL: GAMEMD 0x7EE410
const double DAT_007EE410 = 60.0;

// SYNTHETIC: GAMEMD 0x5C5B20
// GLOBAL: GAMEMD 0xABF510
double DAT_00ABF510 = DAT_00ABF4C0 / DAT_007EE410;
// SYNTHETIC: GAMEMD 0x5C5B40
// GLOBAL: GAMEMD 0xABF4F8
double DAT_00ABF4F8 = 1.0 / DAT_00ABF510;
// SYNTHETIC: GAMEMD 0x5C5CC0
// GLOBAL: GAMEMD 0xABF500
HeaderCoordInit DAT_00ABF500(128, 128, 0);
