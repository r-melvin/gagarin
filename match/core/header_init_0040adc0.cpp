// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40ADC0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x87F550
extern double DAT_0087F550;
// GLOBAL: GAMEMD 0x7E1768
const double DAT_007E1768 = 60.0;

// SYNTHETIC: GAMEMD 0x40ADC0
// GLOBAL: GAMEMD 0x87F5A0
double DAT_0087F5A0 = DAT_0087F550 / DAT_007E1768;
// SYNTHETIC: GAMEMD 0x40ADE0
// GLOBAL: GAMEMD 0x87F588
double DAT_0087F588 = 1.0 / DAT_0087F5A0;
// SYNTHETIC: GAMEMD 0x40AF60
// GLOBAL: GAMEMD 0x87F590
HeaderCoordInit DAT_0087F590(128, 128, 0);
