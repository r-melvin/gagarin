// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4E62D0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E9B50
const double DAT_007E9B50 = 60.0;
// GLOBAL: GAMEMD 0x7E9B58 -- degrees to radians
const double DAT_007E9B58 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4E62D0
// GLOBAL: GAMEMD 0xA83D40
double DAT_00A83D40 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4E6340
// GLOBAL: GAMEMD 0xA8EB20
double DAT_00A8EB20 = DAT_007E9B58 * 45.0;
// SYNTHETIC: GAMEMD 0x4E6360
// GLOBAL: GAMEMD 0xA83DB0
double DAT_00A83DB0 = DAT_007E9B58 * 60.0;
// SYNTHETIC: GAMEMD 0x4E6380
// GLOBAL: GAMEMD 0x8B4168
double DAT_008B4168 = DAT_007E9B58 * 90.0;
// SYNTHETIC: GAMEMD 0x4E63A0
// GLOBAL: GAMEMD 0xA8ED58
int DAT_00A8ED58 = (int)(FUN_004CAD50(DAT_008B4168 - DAT_00A83DB0) * DAT_00A83D40 * 0.5);
// SYNTHETIC: GAMEMD 0x4E63E0
// GLOBAL: GAMEMD 0xA83DE0
double DAT_00A83DE0 = FUN_004CADE0(DAT_00A8ED58 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4E6410
// GLOBAL: GAMEMD 0xA8E958
double DAT_00A8E958 = FUN_004CADE0((DAT_00A8ED58 * 2) / DAT_00A83D40);
// SYNTHETIC: GAMEMD 0x4E6440
// GLOBAL: GAMEMD 0xA8EC94
int DAT_00A8EC94 = (int)(DAT_00A8ED58 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4E6470
// GLOBAL: GAMEMD 0xA83CD0
HeaderCellInit DAT_00A83CD0(0, 0);
// SYNTHETIC: GAMEMD 0x4E6480
// GLOBAL: GAMEMD 0xA8E380
HeaderCoordInit DAT_00A8E380(0, 0, 0);
