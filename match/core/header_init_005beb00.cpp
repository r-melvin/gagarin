// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x5BEB00
// (header_init_shapes.h): the same twelve initialisers as the block at 0x40ADC0, in
// __xc order: two derived doubles, three angle doubles, the derived ints/doubles,
// a zero cell, a zero coordinate and a {128, 128, 0} coordinate.
#include "header_init_shapes.h"

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// GLOBAL: GAMEMD 0xABF300
extern double DAT_00ABF300;
// GLOBAL: GAMEMD 0x7EE090
const double DAT_007EE090 = 60.0;
// GLOBAL: GAMEMD 0x7EE098 -- degrees to radians
const double DAT_007EE098 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5BEB00
// GLOBAL: GAMEMD 0xABF350
double DAT_00ABF350 = DAT_00ABF300 / DAT_007EE090;
// SYNTHETIC: GAMEMD 0x5BEB20
// GLOBAL: GAMEMD 0xABF338
double DAT_00ABF338 = 1.0 / DAT_00ABF350;
// SYNTHETIC: GAMEMD 0x5BEB40
// GLOBAL: GAMEMD 0xABF330
double DAT_00ABF330 = DAT_007EE098 * 45.0;
// SYNTHETIC: GAMEMD 0x5BEB60
// GLOBAL: GAMEMD 0xABF308
double DAT_00ABF308 = DAT_007EE098 * 60.0;
// SYNTHETIC: GAMEMD 0x5BEB80
// GLOBAL: GAMEMD 0xABF2E0
double DAT_00ABF2E0 = DAT_007EE098 * 90.0;
// SYNTHETIC: GAMEMD 0x5BEBA0
// GLOBAL: GAMEMD 0xABF358
int DAT_00ABF358 = (int)(FUN_004CAD50(DAT_00ABF2E0 - DAT_00ABF308) * DAT_00ABF300 * 0.5);
// SYNTHETIC: GAMEMD 0x5BEBE0
// GLOBAL: GAMEMD 0xABF310
double DAT_00ABF310 = FUN_004CADE0(DAT_00ABF358 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5BEC10
// GLOBAL: GAMEMD 0xABF328
double DAT_00ABF328 = FUN_004CADE0((DAT_00ABF358 * 2) / DAT_00ABF300);
// SYNTHETIC: GAMEMD 0x5BEC40
// GLOBAL: GAMEMD 0xABF34C
int DAT_00ABF34C = (int)(DAT_00ABF358 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5BEC70
// GLOBAL: GAMEMD 0xABF2F8
HeaderCellInit DAT_00ABF2F8(0, 0);
// SYNTHETIC: GAMEMD 0x5BEC80
// GLOBAL: GAMEMD 0xABF318
HeaderCoordInit DAT_00ABF318(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5BECA0
// GLOBAL: GAMEMD 0xABF340
HeaderCoordInit DAT_00ABF340(128, 128, 0);
