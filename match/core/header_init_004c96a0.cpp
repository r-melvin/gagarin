// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4C96A0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E8890
const double DAT_007E8890 = 60.0;
// GLOBAL: GAMEMD 0x7E8898 -- degrees to radians
const double DAT_007E8898 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4C96A0
// GLOBAL: GAMEMD 0x8B3AD0
double DAT_008B3AD0 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4C96D0
// GLOBAL: GAMEMD 0x8B3B20
double DAT_008B3B20 = DAT_008B3AD0 / DAT_007E8890;
// SYNTHETIC: GAMEMD 0x4C96F0
// GLOBAL: GAMEMD 0x8B3B08
double DAT_008B3B08 = 1.0 / DAT_008B3B20;
// SYNTHETIC: GAMEMD 0x4C9710
// GLOBAL: GAMEMD 0x8B3B00
double DAT_008B3B00 = DAT_007E8898 * 45.0;
// SYNTHETIC: GAMEMD 0x4C9730
// GLOBAL: GAMEMD 0x8B3AD8
double DAT_008B3AD8 = DAT_007E8898 * 60.0;
// SYNTHETIC: GAMEMD 0x4C9750
// GLOBAL: GAMEMD 0x8B3AB0
double DAT_008B3AB0 = DAT_007E8898 * 90.0;
// SYNTHETIC: GAMEMD 0x4C9770
// GLOBAL: GAMEMD 0x8B3B28
int DAT_008B3B28 = (int)(FUN_004CAD50(DAT_008B3AB0 - DAT_008B3AD8) * DAT_008B3AD0 * 0.5);
// SYNTHETIC: GAMEMD 0x4C97B0
// GLOBAL: GAMEMD 0x8B3AE0
double DAT_008B3AE0 = FUN_004CADE0(DAT_008B3B28 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4C97E0
// GLOBAL: GAMEMD 0x8B3AF8
double DAT_008B3AF8 = FUN_004CADE0((DAT_008B3B28 * 2) / DAT_008B3AD0);
// SYNTHETIC: GAMEMD 0x4C9810
// GLOBAL: GAMEMD 0x8B3B1C
int DAT_008B3B1C = (int)(DAT_008B3B28 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4C9840
// GLOBAL: GAMEMD 0x8B3AC8
HeaderCellInit DAT_008B3AC8(0, 0);
// SYNTHETIC: GAMEMD 0x4C9850
// GLOBAL: GAMEMD 0x8B3AE8
HeaderCoordInit DAT_008B3AE8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4C9870
// GLOBAL: GAMEMD 0x8B3B10
HeaderCoordInit DAT_008B3B10(128, 128, 0);
