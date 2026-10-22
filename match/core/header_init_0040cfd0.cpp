// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40CFD0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order, then the shared random generator seeded with 0.
#include "header_init_shapes.h"
#include "randomizer.h"

// GLOBAL: GAMEMD 0x87F7B0
extern double DAT_0087F7B0;
// GLOBAL: GAMEMD 0x7E1948
const double DAT_007E1948 = 60.0;

// SYNTHETIC: GAMEMD 0x40CFD0
// GLOBAL: GAMEMD 0x884D78
double DAT_00884D78 = DAT_0087F7B0 / DAT_007E1948;
// SYNTHETIC: GAMEMD 0x40CFF0
// GLOBAL: GAMEMD 0x884D60
double DAT_00884D60 = 1.0 / DAT_00884D78;
// SYNTHETIC: GAMEMD 0x40D170
// GLOBAL: GAMEMD 0x884D68
HeaderCoordInit DAT_00884D68(128, 128, 0);

// SYNTHETIC: GAMEMD 0x40D9F0
// GLOBAL: GAMEMD 0x886B88
Randomizer DAT_00886B88(0);
