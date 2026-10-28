// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x488F90
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E5128
const double DAT_007E5128 = 60.0;
// GLOBAL: GAMEMD 0x7E5130 -- degrees to radians
const double DAT_007E5130 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x488F90
// GLOBAL: GAMEMD 0x89E818
double DAT_0089E818 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x488FC0
// GLOBAL: GAMEMD 0x89E868
double DAT_0089E868 = DAT_0089E818 / DAT_007E5128;
// SYNTHETIC: GAMEMD 0x488FE0
// GLOBAL: GAMEMD 0x89E850
double DAT_0089E850 = 1.0 / DAT_0089E868;
// SYNTHETIC: GAMEMD 0x489000
// GLOBAL: GAMEMD 0x89E848
double DAT_0089E848 = DAT_007E5130 * 45.0;
// SYNTHETIC: GAMEMD 0x489020
// GLOBAL: GAMEMD 0x89E820
double DAT_0089E820 = DAT_007E5130 * 60.0;
// SYNTHETIC: GAMEMD 0x489040
// GLOBAL: GAMEMD 0x89E7F8
double DAT_0089E7F8 = DAT_007E5130 * 90.0;
// SYNTHETIC: GAMEMD 0x489060
// GLOBAL: GAMEMD 0x89E870
int DAT_0089E870 = (int)(FUN_004CAD50(DAT_0089E7F8 - DAT_0089E820) * DAT_0089E818 * 0.5);
// SYNTHETIC: GAMEMD 0x4890A0
// GLOBAL: GAMEMD 0x89E828
double DAT_0089E828 = FUN_004CADE0(DAT_0089E870 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4890D0
// GLOBAL: GAMEMD 0x89E840
double DAT_0089E840 = FUN_004CADE0((DAT_0089E870 * 2) / DAT_0089E818);
// SYNTHETIC: GAMEMD 0x489100
// GLOBAL: GAMEMD 0x89E864
int DAT_0089E864 = (int)(DAT_0089E870 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x489130
// GLOBAL: GAMEMD 0x89E810
HeaderCellInit DAT_0089E810(0, 0);
// SYNTHETIC: GAMEMD 0x489140
// GLOBAL: GAMEMD 0x89E830
HeaderCoordInit DAT_0089E830(0, 0, 0);
// SYNTHETIC: GAMEMD 0x489160
// GLOBAL: GAMEMD 0x89E858
HeaderCoordInit DAT_0089E858(128, 128, 0);
