// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4F4030
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7EA6D8
const double DAT_007EA6D8 = 60.0;
// GLOBAL: GAMEMD 0x7EA6E0 -- degrees to radians
const double DAT_007EA6E0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4F4030
// GLOBAL: GAMEMD 0xA8EEF8
double DAT_00A8EEF8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4F4060
// GLOBAL: GAMEMD 0xA8EF48
double DAT_00A8EF48 = DAT_00A8EEF8 / DAT_007EA6D8;
// SYNTHETIC: GAMEMD 0x4F4080
// GLOBAL: GAMEMD 0xA8EF30
double DAT_00A8EF30 = 1.0 / DAT_00A8EF48;
// SYNTHETIC: GAMEMD 0x4F40A0
// GLOBAL: GAMEMD 0xA8EF28
double DAT_00A8EF28 = DAT_007EA6E0 * 45.0;
// SYNTHETIC: GAMEMD 0x4F40C0
// GLOBAL: GAMEMD 0xA8EF00
double DAT_00A8EF00 = DAT_007EA6E0 * 60.0;
// SYNTHETIC: GAMEMD 0x4F40E0
// GLOBAL: GAMEMD 0xA8EED8
double DAT_00A8EED8 = DAT_007EA6E0 * 90.0;
// SYNTHETIC: GAMEMD 0x4F4100
// GLOBAL: GAMEMD 0xA8EF50
int DAT_00A8EF50 = (int)(FUN_004CAD50(DAT_00A8EED8 - DAT_00A8EF00) * DAT_00A8EEF8 * 0.5);
// SYNTHETIC: GAMEMD 0x4F4140
// GLOBAL: GAMEMD 0xA8EF08
double DAT_00A8EF08 = FUN_004CADE0(DAT_00A8EF50 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4F4170
// GLOBAL: GAMEMD 0xA8EF20
double DAT_00A8EF20 = FUN_004CADE0((DAT_00A8EF50 * 2) / DAT_00A8EEF8);
// SYNTHETIC: GAMEMD 0x4F41A0
// GLOBAL: GAMEMD 0xA8EF44
int DAT_00A8EF44 = (int)(DAT_00A8EF50 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4F41D0
// GLOBAL: GAMEMD 0xA8EEF0
HeaderCellInit DAT_00A8EEF0(0, 0);
// SYNTHETIC: GAMEMD 0x4F41E0
// GLOBAL: GAMEMD 0xA8EF10
HeaderCoordInit DAT_00A8EF10(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4F4200
// GLOBAL: GAMEMD 0xA8EF38
HeaderCoordInit DAT_00A8EF38(128, 128, 0);
