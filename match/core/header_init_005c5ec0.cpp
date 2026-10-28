// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x5C5E70
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

// GLOBAL: GAMEMD 0x7EE4F8
const double DAT_007EE4F8 = 60.0;
// GLOBAL: GAMEMD 0x7EE500 -- degrees to radians
const double DAT_007EE500 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5C5E70
// GLOBAL: GAMEMD 0xABF528
MathTblZero4 DAT_00ABF528;
// SYNTHETIC: GAMEMD 0x5C5E90
// GLOBAL: GAMEMD 0xABF540
double DAT_00ABF540 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5C5EC0
// GLOBAL: GAMEMD 0xABF590
double DAT_00ABF590 = DAT_00ABF540 / DAT_007EE4F8;
// SYNTHETIC: GAMEMD 0x5C5EE0
// GLOBAL: GAMEMD 0xABF578
double DAT_00ABF578 = 1.0 / DAT_00ABF590;
// SYNTHETIC: GAMEMD 0x5C5F00
// GLOBAL: GAMEMD 0xABF570
double DAT_00ABF570 = DAT_007EE500 * 45.0;
// SYNTHETIC: GAMEMD 0x5C5F20
// GLOBAL: GAMEMD 0xABF548
double DAT_00ABF548 = DAT_007EE500 * 60.0;
// SYNTHETIC: GAMEMD 0x5C5F40
// GLOBAL: GAMEMD 0xABF520
double DAT_00ABF520 = DAT_007EE500 * 90.0;
// SYNTHETIC: GAMEMD 0x5C5F60
// GLOBAL: GAMEMD 0xABF598
int DAT_00ABF598 = (int)(FUN_004CAD50(DAT_00ABF520 - DAT_00ABF548) * DAT_00ABF540 * 0.5);
// SYNTHETIC: GAMEMD 0x5C5FA0
// GLOBAL: GAMEMD 0xABF550
double DAT_00ABF550 = FUN_004CADE0(DAT_00ABF598 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5C5FD0
// GLOBAL: GAMEMD 0xABF568
double DAT_00ABF568 = FUN_004CADE0((DAT_00ABF598 * 2) / DAT_00ABF540);
// SYNTHETIC: GAMEMD 0x5C6000
// GLOBAL: GAMEMD 0xABF58C
int DAT_00ABF58C = (int)(DAT_00ABF598 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5C6030
// GLOBAL: GAMEMD 0xABF538
HeaderCellInit DAT_00ABF538(0, 0);
// SYNTHETIC: GAMEMD 0x5C6040
// GLOBAL: GAMEMD 0xABF558
HeaderCoordInit DAT_00ABF558(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5C6060
// GLOBAL: GAMEMD 0xABF580
HeaderCoordInit DAT_00ABF580(128, 128, 0);
