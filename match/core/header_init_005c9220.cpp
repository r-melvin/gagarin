// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group at 0x5C9220, 0x5C9240 and 0x5C93C0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order. The divisor at 0x7EE5E0 reads 60.0 (ghidra memory read).
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0xABF8F8
extern double DAT_00ABF8F8;
// GLOBAL: GAMEMD 0x7EE5E0
const double DAT_007EE5E0 = 60.0;

// SYNTHETIC: GAMEMD 0x5C9220
// GLOBAL: GAMEMD 0xABF948
double DAT_00ABF948 = DAT_00ABF8F8 / DAT_007EE5E0;
// SYNTHETIC: GAMEMD 0x5C9240
// GLOBAL: GAMEMD 0xABF930
double DAT_00ABF930 = 1.0 / DAT_00ABF948;
// SYNTHETIC: GAMEMD 0x5C93C0
// GLOBAL: GAMEMD 0xABF938
HeaderCoordInit DAT_00ABF938(128, 128, 0);
