// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x403CE0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E16F8
const double DAT_007E16F8 = 60.0;
// GLOBAL: GAMEMD 0x7E1700 -- degrees to radians
const double DAT_007E1700 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x403CE0
// GLOBAL: GAMEMD 0x87E1A0
double DAT_0087E1A0 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x403D10
// GLOBAL: GAMEMD 0x87E280
double DAT_0087E280 = DAT_0087E1A0 / DAT_007E16F8;
// SYNTHETIC: GAMEMD 0x403D30
// GLOBAL: GAMEMD 0x87E268
double DAT_0087E268 = 1.0 / DAT_0087E280;
// SYNTHETIC: GAMEMD 0x403D50
// GLOBAL: GAMEMD 0x87E260
double DAT_0087E260 = DAT_007E1700 * 45.0;
// SYNTHETIC: GAMEMD 0x403D70
// GLOBAL: GAMEMD 0x87E1A8
double DAT_0087E1A8 = DAT_007E1700 * 60.0;
// SYNTHETIC: GAMEMD 0x403D90
// GLOBAL: GAMEMD 0x87E190
double DAT_0087E190 = DAT_007E1700 * 90.0;
// SYNTHETIC: GAMEMD 0x403DB0
// GLOBAL: GAMEMD 0x87E288
int DAT_0087E288 = (int)(FUN_004CAD50(DAT_0087E190 - DAT_0087E1A8) * DAT_0087E1A0 * 0.5);
// SYNTHETIC: GAMEMD 0x403DF0
// GLOBAL: GAMEMD 0x87E1B0
double DAT_0087E1B0 = FUN_004CADE0(DAT_0087E288 * 0.00390625);
// SYNTHETIC: GAMEMD 0x403E20
// GLOBAL: GAMEMD 0x87E248
double DAT_0087E248 = FUN_004CADE0((DAT_0087E288 * 2) / DAT_0087E1A0);
// SYNTHETIC: GAMEMD 0x403E50
// GLOBAL: GAMEMD 0x87E27C
int DAT_0087E27C = (int)(DAT_0087E288 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x403E80
// GLOBAL: GAMEMD 0x87E198
HeaderCellInit DAT_0087E198(0, 0);
// SYNTHETIC: GAMEMD 0x403E90
// GLOBAL: GAMEMD 0x87E238
HeaderCoordInit DAT_0087E238(0, 0, 0);
// SYNTHETIC: GAMEMD 0x403EB0
// GLOBAL: GAMEMD 0x87E270
HeaderCoordInit DAT_0087E270(128, 128, 0);
