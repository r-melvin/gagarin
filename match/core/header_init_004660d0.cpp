// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4660D0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E4660
const double DAT_007E4660 = 60.0;
// GLOBAL: GAMEMD 0x7E4668 -- degrees to radians
const double DAT_007E4668 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4660D0
// GLOBAL: GAMEMD 0x89DDF8
double DAT_0089DDF8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x466100
// GLOBAL: GAMEMD 0x89DE68
double DAT_0089DE68 = DAT_0089DDF8 / DAT_007E4660;
// SYNTHETIC: GAMEMD 0x466120
// GLOBAL: GAMEMD 0x89DE50
double DAT_0089DE50 = 1.0 / DAT_0089DE68;
// SYNTHETIC: GAMEMD 0x466140
// GLOBAL: GAMEMD 0x89DE48
double DAT_0089DE48 = DAT_007E4668 * 45.0;
// SYNTHETIC: GAMEMD 0x466160
// GLOBAL: GAMEMD 0x89DE00
double DAT_0089DE00 = DAT_007E4668 * 60.0;
// SYNTHETIC: GAMEMD 0x466180
// GLOBAL: GAMEMD 0x89DDD8
double DAT_0089DDD8 = DAT_007E4668 * 90.0;
// SYNTHETIC: GAMEMD 0x4661A0
// GLOBAL: GAMEMD 0x89DE70
int DAT_0089DE70 = (int)(FUN_004CAD50(DAT_0089DDD8 - DAT_0089DE00) * DAT_0089DDF8 * 0.5);
// SYNTHETIC: GAMEMD 0x4661E0
// GLOBAL: GAMEMD 0x89DE08
double DAT_0089DE08 = FUN_004CADE0(DAT_0089DE70 * 0.00390625);
// SYNTHETIC: GAMEMD 0x466210
// GLOBAL: GAMEMD 0x89DE40
double DAT_0089DE40 = FUN_004CADE0((DAT_0089DE70 * 2) / DAT_0089DDF8);
// SYNTHETIC: GAMEMD 0x466240
// GLOBAL: GAMEMD 0x89DE64
int DAT_0089DE64 = (int)(DAT_0089DE70 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x466270
// GLOBAL: GAMEMD 0x89DDF0
HeaderCellInit DAT_0089DDF0(0, 0);
// SYNTHETIC: GAMEMD 0x466280
// GLOBAL: GAMEMD 0x89DE30
HeaderCoordInit DAT_0089DE30(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4662A0
// GLOBAL: GAMEMD 0x89DE58
HeaderCoordInit DAT_0089DE58(128, 128, 0);
