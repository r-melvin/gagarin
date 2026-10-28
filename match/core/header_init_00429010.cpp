// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x429010
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E36B0
const double DAT_007E36B0 = 60.0;
// GLOBAL: GAMEMD 0x7E36B8 -- degrees to radians
const double DAT_007E36B8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x429010
// GLOBAL: GAMEMD 0x89A278
double DAT_0089A278 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x429040
// GLOBAL: GAMEMD 0x89A2C8
double DAT_0089A2C8 = DAT_0089A278 / DAT_007E36B0;
// SYNTHETIC: GAMEMD 0x429060
// GLOBAL: GAMEMD 0x89A2B0
double DAT_0089A2B0 = 1.0 / DAT_0089A2C8;
// SYNTHETIC: GAMEMD 0x429080
// GLOBAL: GAMEMD 0x89A2A8
double DAT_0089A2A8 = DAT_007E36B8 * 45.0;
// SYNTHETIC: GAMEMD 0x4290A0
// GLOBAL: GAMEMD 0x89A280
double DAT_0089A280 = DAT_007E36B8 * 60.0;
// SYNTHETIC: GAMEMD 0x4290C0
// GLOBAL: GAMEMD 0x89A258
double DAT_0089A258 = DAT_007E36B8 * 90.0;
// SYNTHETIC: GAMEMD 0x4290E0
// GLOBAL: GAMEMD 0x89A2D0
int DAT_0089A2D0 = (int)(FUN_004CAD50(DAT_0089A258 - DAT_0089A280) * DAT_0089A278 * 0.5);
// SYNTHETIC: GAMEMD 0x429120
// GLOBAL: GAMEMD 0x89A288
double DAT_0089A288 = FUN_004CADE0(DAT_0089A2D0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x429150
// GLOBAL: GAMEMD 0x89A2A0
double DAT_0089A2A0 = FUN_004CADE0((DAT_0089A2D0 * 2) / DAT_0089A278);
// SYNTHETIC: GAMEMD 0x429180
// GLOBAL: GAMEMD 0x89A2C4
int DAT_0089A2C4 = (int)(DAT_0089A2D0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4291B0
// GLOBAL: GAMEMD 0x89A270
HeaderCellInit DAT_0089A270(0, 0);
// SYNTHETIC: GAMEMD 0x4291C0
// GLOBAL: GAMEMD 0x89A290
HeaderCoordInit DAT_0089A290(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4291E0
// GLOBAL: GAMEMD 0x89A2B8
HeaderCoordInit DAT_0089A2B8(128, 128, 0);
