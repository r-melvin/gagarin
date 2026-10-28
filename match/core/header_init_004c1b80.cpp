// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4C1B80
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E8678
const double DAT_007E8678 = 60.0;
// GLOBAL: GAMEMD 0x7E8680 -- degrees to radians
const double DAT_007E8680 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4C1B80
// GLOBAL: GAMEMD 0x8A0E38
double DAT_008A0E38 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4C1BF0
// GLOBAL: GAMEMD 0x8A0E68
double DAT_008A0E68 = DAT_007E8680 * 45.0;
// SYNTHETIC: GAMEMD 0x4C1C10
// GLOBAL: GAMEMD 0x8A0E40
double DAT_008A0E40 = DAT_007E8680 * 60.0;
// SYNTHETIC: GAMEMD 0x4C1C30
// GLOBAL: GAMEMD 0x8A0E18
double DAT_008A0E18 = DAT_007E8680 * 90.0;
// SYNTHETIC: GAMEMD 0x4C1C50
// GLOBAL: GAMEMD 0x8A0EB0
int DAT_008A0EB0 = (int)(FUN_004CAD50(DAT_008A0E18 - DAT_008A0E40) * DAT_008A0E38 * 0.5);
// SYNTHETIC: GAMEMD 0x4C1C90
// GLOBAL: GAMEMD 0x8A0E48
double DAT_008A0E48 = FUN_004CADE0(DAT_008A0EB0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4C1CC0
// GLOBAL: GAMEMD 0x8A0E60
double DAT_008A0E60 = FUN_004CADE0((DAT_008A0EB0 * 2) / DAT_008A0E38);
// SYNTHETIC: GAMEMD 0x4C1CF0
// GLOBAL: GAMEMD 0x8A0EA0
int DAT_008A0EA0 = (int)(DAT_008A0EB0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4C1D20
// GLOBAL: GAMEMD 0x8A0E30
HeaderCellInit DAT_008A0E30(0, 0);
// SYNTHETIC: GAMEMD 0x4C1D30
// GLOBAL: GAMEMD 0x8A0E50
HeaderCoordInit DAT_008A0E50(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4C1D50
// GLOBAL: GAMEMD 0x8A0E78
HeaderCoordInit DAT_008A0E78(128, 128, 0);
