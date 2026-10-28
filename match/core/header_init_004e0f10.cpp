// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4E0F10
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E92A8
const double DAT_007E92A8 = 60.0;
// GLOBAL: GAMEMD 0x7E92B0 -- degrees to radians
const double DAT_007E92B0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4E0F10
// GLOBAL: GAMEMD 0x8B3E18
double DAT_008B3E18 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4E0F40
// GLOBAL: GAMEMD 0x8B3E68
double DAT_008B3E68 = DAT_008B3E18 / DAT_007E92A8;
// SYNTHETIC: GAMEMD 0x4E0F60
// GLOBAL: GAMEMD 0x8B3E50
double DAT_008B3E50 = 1.0 / DAT_008B3E68;
// SYNTHETIC: GAMEMD 0x4E0F80
// GLOBAL: GAMEMD 0x8B3E48
double DAT_008B3E48 = DAT_007E92B0 * 45.0;
// SYNTHETIC: GAMEMD 0x4E0FA0
// GLOBAL: GAMEMD 0x8B3E20
double DAT_008B3E20 = DAT_007E92B0 * 60.0;
// SYNTHETIC: GAMEMD 0x4E0FC0
// GLOBAL: GAMEMD 0x8B3E08
double DAT_008B3E08 = DAT_007E92B0 * 90.0;
// SYNTHETIC: GAMEMD 0x4E0FE0
// GLOBAL: GAMEMD 0x8B3E70
int DAT_008B3E70 = (int)(FUN_004CAD50(DAT_008B3E08 - DAT_008B3E20) * DAT_008B3E18 * 0.5);
// SYNTHETIC: GAMEMD 0x4E1020
// GLOBAL: GAMEMD 0x8B3E28
double DAT_008B3E28 = FUN_004CADE0(DAT_008B3E70 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4E1050
// GLOBAL: GAMEMD 0x8B3E40
double DAT_008B3E40 = FUN_004CADE0((DAT_008B3E70 * 2) / DAT_008B3E18);
// SYNTHETIC: GAMEMD 0x4E1080
// GLOBAL: GAMEMD 0x8B3E64
int DAT_008B3E64 = (int)(DAT_008B3E70 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4E10B0
// GLOBAL: GAMEMD 0x8B3E10
HeaderCellInit DAT_008B3E10(0, 0);
// SYNTHETIC: GAMEMD 0x4E10C0
// GLOBAL: GAMEMD 0x8B3E30
HeaderCoordInit DAT_008B3E30(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4E10E0
// GLOBAL: GAMEMD 0x8B3E58
HeaderCoordInit DAT_008B3E58(128, 128, 0);
