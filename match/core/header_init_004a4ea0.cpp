// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4A4EA0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E5E28
const double DAT_007E5E28 = 60.0;
// GLOBAL: GAMEMD 0x7E5E30 -- degrees to radians
const double DAT_007E5E30 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4A4EA0
// GLOBAL: GAMEMD 0x8A00D8
double DAT_008A00D8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4A4ED0
// GLOBAL: GAMEMD 0x8A0128
double DAT_008A0128 = DAT_008A00D8 / DAT_007E5E28;
// SYNTHETIC: GAMEMD 0x4A4EF0
// GLOBAL: GAMEMD 0x8A0110
double DAT_008A0110 = 1.0 / DAT_008A0128;
// SYNTHETIC: GAMEMD 0x4A4F10
// GLOBAL: GAMEMD 0x8A0108
double DAT_008A0108 = DAT_007E5E30 * 45.0;
// SYNTHETIC: GAMEMD 0x4A4F30
// GLOBAL: GAMEMD 0x8A00E0
double DAT_008A00E0 = DAT_007E5E30 * 60.0;
// SYNTHETIC: GAMEMD 0x4A4F50
// GLOBAL: GAMEMD 0x8A00B8
double DAT_008A00B8 = DAT_007E5E30 * 90.0;
// SYNTHETIC: GAMEMD 0x4A4F70
// GLOBAL: GAMEMD 0x8A0130
int DAT_008A0130 = (int)(FUN_004CAD50(DAT_008A00B8 - DAT_008A00E0) * DAT_008A00D8 * 0.5);
// SYNTHETIC: GAMEMD 0x4A4FB0
// GLOBAL: GAMEMD 0x8A00E8
double DAT_008A00E8 = FUN_004CADE0(DAT_008A0130 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4A4FE0
// GLOBAL: GAMEMD 0x8A0100
double DAT_008A0100 = FUN_004CADE0((DAT_008A0130 * 2) / DAT_008A00D8);
// SYNTHETIC: GAMEMD 0x4A5010
// GLOBAL: GAMEMD 0x8A0124
int DAT_008A0124 = (int)(DAT_008A0130 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4A5040
// GLOBAL: GAMEMD 0x8A00D0
HeaderCellInit DAT_008A00D0(0, 0);
// SYNTHETIC: GAMEMD 0x4A5050
// GLOBAL: GAMEMD 0x8A00F0
HeaderCoordInit DAT_008A00F0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4A5070
// GLOBAL: GAMEMD 0x8A0118
HeaderCoordInit DAT_008A0118(128, 128, 0);
