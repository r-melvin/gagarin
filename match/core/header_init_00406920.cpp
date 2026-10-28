// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x406920
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E1750
const double DAT_007E1750 = 60.0;
// GLOBAL: GAMEMD 0x7E1758 -- degrees to radians
const double DAT_007E1758 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x406920
// GLOBAL: GAMEMD 0x87E448
double DAT_0087E448 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x406950
// GLOBAL: GAMEMD 0x87E698
double DAT_0087E698 = DAT_0087E448 / DAT_007E1750;
// SYNTHETIC: GAMEMD 0x406970
// GLOBAL: GAMEMD 0x87E680
double DAT_0087E680 = 1.0 / DAT_0087E698;
// SYNTHETIC: GAMEMD 0x406990
// GLOBAL: GAMEMD 0x87E678
double DAT_0087E678 = DAT_007E1758 * 45.0;
// SYNTHETIC: GAMEMD 0x4069B0
// GLOBAL: GAMEMD 0x87E4D0
double DAT_0087E4D0 = DAT_007E1758 * 60.0;
// SYNTHETIC: GAMEMD 0x4069D0
// GLOBAL: GAMEMD 0x87E2B8
double DAT_0087E2B8 = DAT_007E1758 * 90.0;
// SYNTHETIC: GAMEMD 0x4069F0
// GLOBAL: GAMEMD 0x87E720
int DAT_0087E720 = (int)(FUN_004CAD50(DAT_0087E2B8 - DAT_0087E4D0) * DAT_0087E448 * 0.5);
// SYNTHETIC: GAMEMD 0x406A30
// GLOBAL: GAMEMD 0x87E4D8
double DAT_0087E4D8 = FUN_004CADE0(DAT_0087E720 * 0.00390625);
// SYNTHETIC: GAMEMD 0x406A60
// GLOBAL: GAMEMD 0x87E570
double DAT_0087E570 = FUN_004CADE0((DAT_0087E720 * 2) / DAT_0087E448);
// SYNTHETIC: GAMEMD 0x406A90
// GLOBAL: GAMEMD 0x87E694
int DAT_0087E694 = (int)(DAT_0087E720 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x406AC0
// GLOBAL: GAMEMD 0x87E440
HeaderCellInit DAT_0087E440(0, 0);
// SYNTHETIC: GAMEMD 0x406AD0
// GLOBAL: GAMEMD 0x87E560
HeaderCoordInit DAT_0087E560(0, 0, 0);
// SYNTHETIC: GAMEMD 0x406AF0
// GLOBAL: GAMEMD 0x87E688
HeaderCoordInit DAT_0087E688(128, 128, 0);
