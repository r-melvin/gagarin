// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x427320
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
// GLOBAL: GAMEMD 0x7E35C8
const double DAT_007E35C8 = 60.0;
// GLOBAL: GAMEMD 0x7E35D0 -- degrees to radians
const double DAT_007E35D0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x427320
// GLOBAL: GAMEMD 0x89A1F8
double DAT_0089A1F8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x427350
// GLOBAL: GAMEMD 0x89A248
double DAT_0089A248 = DAT_0089A1F8 / DAT_007E35C8;
// SYNTHETIC: GAMEMD 0x427370
// GLOBAL: GAMEMD 0x89A230
double DAT_0089A230 = 1.0 / DAT_0089A248;
// SYNTHETIC: GAMEMD 0x427390
// GLOBAL: GAMEMD 0x89A228
double DAT_0089A228 = DAT_007E35D0 * 45.0;
// SYNTHETIC: GAMEMD 0x4273B0
// GLOBAL: GAMEMD 0x89A200
double DAT_0089A200 = DAT_007E35D0 * 60.0;
// SYNTHETIC: GAMEMD 0x4273D0
// GLOBAL: GAMEMD 0x89A1D8
double DAT_0089A1D8 = DAT_007E35D0 * 90.0;
// SYNTHETIC: GAMEMD 0x4273F0
// GLOBAL: GAMEMD 0x89A250
int DAT_0089A250 = (int)(FUN_004CAD50(DAT_0089A1D8 - DAT_0089A200) * DAT_0089A1F8 * 0.5);
// SYNTHETIC: GAMEMD 0x427430
// GLOBAL: GAMEMD 0x89A208
double DAT_0089A208 = FUN_004CADE0(DAT_0089A250 * 0.00390625);
// SYNTHETIC: GAMEMD 0x427460
// GLOBAL: GAMEMD 0x89A220
double DAT_0089A220 = FUN_004CADE0((DAT_0089A250 * 2) / DAT_0089A1F8);
// SYNTHETIC: GAMEMD 0x427490
// GLOBAL: GAMEMD 0x89A244
int DAT_0089A244 = (int)(DAT_0089A250 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4274C0
// GLOBAL: GAMEMD 0x89A1F0
HeaderCellInit DAT_0089A1F0(0, 0);
// SYNTHETIC: GAMEMD 0x4274D0
// GLOBAL: GAMEMD 0x89A210
HeaderCoordInit DAT_0089A210(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4274F0
// GLOBAL: GAMEMD 0x89A238
HeaderCoordInit DAT_0089A238(128, 128, 0);
