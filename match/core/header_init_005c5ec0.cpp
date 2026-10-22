// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group at 0x5C5EC0, 0x5C5EE0 and 0x5C6060
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order. The divisor at 0x7EE4F8 reads 60.0 (ghidra memory read).
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0xABF540
extern double DAT_00ABF540;
// GLOBAL: GAMEMD 0x7EE4F8
const double DAT_007EE4F8 = 60.0;

// SYNTHETIC: GAMEMD 0x5C5EC0
// GLOBAL: GAMEMD 0xABF590
double DAT_00ABF590 = DAT_00ABF540 / DAT_007EE4F8;
// SYNTHETIC: GAMEMD 0x5C5EE0
// GLOBAL: GAMEMD 0xABF578
double DAT_00ABF578 = 1.0 / DAT_00ABF590;
// SYNTHETIC: GAMEMD 0x5C6060
// GLOBAL: GAMEMD 0xABF580
HeaderCoordInit DAT_00ABF580(128, 128, 0);
