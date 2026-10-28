// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x5BF5C0
// (header_init_shapes.h): a zero 4-int block and pow-derived base double, then the same twelve initialisers as the block at 0x40ADC0, in
// __xc order: two derived doubles, three angle doubles, the derived ints/doubles,
// a zero cell, a zero coordinate and a {128, 128, 0} coordinate.
#include <math.h>
#pragma intrinsic(pow)
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// GLOBAL: GAMEMD 0x7EE0A0
const double DAT_007EE0A0 = 60.0;
// GLOBAL: GAMEMD 0x7EE0A8 -- degrees to radians
const double DAT_007EE0A8 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5BF5C0
// GLOBAL: GAMEMD 0xABF368
MathTblZero4 DAT_00ABF368;
// SYNTHETIC: GAMEMD 0x5BF5E0
// GLOBAL: GAMEMD 0xABF380
double DAT_00ABF380 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5BF610
// GLOBAL: GAMEMD 0xABF3E8
double DAT_00ABF3E8 = DAT_00ABF380 / DAT_007EE0A0;
// SYNTHETIC: GAMEMD 0x5BF630
// GLOBAL: GAMEMD 0xABF3D0
double DAT_00ABF3D0 = 1.0 / DAT_00ABF3E8;
// SYNTHETIC: GAMEMD 0x5BF650
// GLOBAL: GAMEMD 0xABF3C8
double DAT_00ABF3C8 = DAT_007EE0A8 * 45.0;
// SYNTHETIC: GAMEMD 0x5BF670
// GLOBAL: GAMEMD 0xABF388
double DAT_00ABF388 = DAT_007EE0A8 * 60.0;
// SYNTHETIC: GAMEMD 0x5BF690
// GLOBAL: GAMEMD 0xABF360
double DAT_00ABF360 = DAT_007EE0A8 * 90.0;
// SYNTHETIC: GAMEMD 0x5BF6B0
// GLOBAL: GAMEMD 0xABF3F0
int DAT_00ABF3F0 = (int)(FUN_004CAD50(DAT_00ABF360 - DAT_00ABF388) * DAT_00ABF380 * 0.5);
// SYNTHETIC: GAMEMD 0x5BF6F0
// GLOBAL: GAMEMD 0xABF3A8
double DAT_00ABF3A8 = FUN_004CADE0(DAT_00ABF3F0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5BF720
// GLOBAL: GAMEMD 0xABF3C0
double DAT_00ABF3C0 = FUN_004CADE0((DAT_00ABF3F0 * 2) / DAT_00ABF380);
// SYNTHETIC: GAMEMD 0x5BF750
// GLOBAL: GAMEMD 0xABF3E4
int DAT_00ABF3E4 = (int)(DAT_00ABF3F0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5BF780
// GLOBAL: GAMEMD 0xABF378
HeaderCellInit DAT_00ABF378(0, 0);
// SYNTHETIC: GAMEMD 0x5BF790
// GLOBAL: GAMEMD 0xABF3B0
HeaderCoordInit DAT_00ABF3B0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5BF7B0
// GLOBAL: GAMEMD 0xABF3D8
HeaderCoordInit DAT_00ABF3D8(128, 128, 0);
