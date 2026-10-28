// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4A6A60
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E5EC8
const double DAT_007E5EC8 = 60.0;
// GLOBAL: GAMEMD 0x7E5ED0 -- degrees to radians
const double DAT_007E5ED0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4A6A60
// GLOBAL: GAMEMD 0x8A0238
double DAT_008A0238 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4A6AD0
// GLOBAL: GAMEMD 0x8A0268
double DAT_008A0268 = DAT_007E5ED0 * 45.0;
// SYNTHETIC: GAMEMD 0x4A6AF0
// GLOBAL: GAMEMD 0x8A0240
double DAT_008A0240 = DAT_007E5ED0 * 60.0;
// SYNTHETIC: GAMEMD 0x4A6B10
// GLOBAL: GAMEMD 0x8A0200
double DAT_008A0200 = DAT_007E5ED0 * 90.0;
// SYNTHETIC: GAMEMD 0x4A6B30
// GLOBAL: GAMEMD 0x8A0290
int DAT_008A0290 = (int)(FUN_004CAD50(DAT_008A0200 - DAT_008A0240) * DAT_008A0238 * 0.5);
// SYNTHETIC: GAMEMD 0x4A6B70
// GLOBAL: GAMEMD 0x8A0248
double DAT_008A0248 = FUN_004CADE0(DAT_008A0290 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4A6BA0
// GLOBAL: GAMEMD 0x8A0260
double DAT_008A0260 = FUN_004CADE0((DAT_008A0290 * 2) / DAT_008A0238);
// SYNTHETIC: GAMEMD 0x4A6BD0
// GLOBAL: GAMEMD 0x8A0284
int DAT_008A0284 = (int)(DAT_008A0290 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4A6C00
// GLOBAL: GAMEMD 0x8A0230
HeaderCellInit DAT_008A0230(0, 0);
// SYNTHETIC: GAMEMD 0x4A6C10
// GLOBAL: GAMEMD 0x8A0250
HeaderCoordInit DAT_008A0250(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4A6C30
// GLOBAL: GAMEMD 0x8A0278
HeaderCoordInit DAT_008A0278(128, 128, 0);
