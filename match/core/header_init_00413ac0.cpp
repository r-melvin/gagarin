// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x413AC0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E2238
const double DAT_007E2238 = 60.0;
// GLOBAL: GAMEMD 0x7E2240 -- degrees to radians
const double DAT_007E2240 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x413AC0
// GLOBAL: GAMEMD 0x889E70
double DAT_00889E70 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x413AF0
// GLOBAL: GAMEMD 0x889EC0
double DAT_00889EC0 = DAT_00889E70 / DAT_007E2238;
// SYNTHETIC: GAMEMD 0x413B10
// GLOBAL: GAMEMD 0x889EA8
double DAT_00889EA8 = 1.0 / DAT_00889EC0;
// SYNTHETIC: GAMEMD 0x413B30
// GLOBAL: GAMEMD 0x889EA0
double DAT_00889EA0 = DAT_007E2240 * 45.0;
// SYNTHETIC: GAMEMD 0x413B50
// GLOBAL: GAMEMD 0x889E78
double DAT_00889E78 = DAT_007E2240 * 60.0;
// SYNTHETIC: GAMEMD 0x413B70
// GLOBAL: GAMEMD 0x889E50
double DAT_00889E50 = DAT_007E2240 * 90.0;
// SYNTHETIC: GAMEMD 0x413B90
// GLOBAL: GAMEMD 0x889EC8
int DAT_00889EC8 = (int)(FUN_004CAD50(DAT_00889E50 - DAT_00889E78) * DAT_00889E70 * 0.5);
// SYNTHETIC: GAMEMD 0x413BD0
// GLOBAL: GAMEMD 0x889E80
double DAT_00889E80 = FUN_004CADE0(DAT_00889EC8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x413C00
// GLOBAL: GAMEMD 0x889E98
double DAT_00889E98 = FUN_004CADE0((DAT_00889EC8 * 2) / DAT_00889E70);
// SYNTHETIC: GAMEMD 0x413C30
// GLOBAL: GAMEMD 0x889EBC
int DAT_00889EBC = (int)(DAT_00889EC8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x413C60
// GLOBAL: GAMEMD 0x889E68
HeaderCellInit DAT_00889E68(0, 0);
// SYNTHETIC: GAMEMD 0x413C70
// GLOBAL: GAMEMD 0x889E88
HeaderCoordInit DAT_00889E88(0, 0, 0);
// SYNTHETIC: GAMEMD 0x413C90
// GLOBAL: GAMEMD 0x889EB0
HeaderCoordInit DAT_00889EB0(128, 128, 0);
