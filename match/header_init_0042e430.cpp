// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x42E430
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
// GLOBAL: GAMEMD 0x7E3868
const double DAT_007E3868 = 60.0;
// GLOBAL: GAMEMD 0x7E3870 -- degrees to radians
const double DAT_007E3870 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x42E430
// GLOBAL: GAMEMD 0x89C318
double DAT_0089C318 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x42E460
// GLOBAL: GAMEMD 0x89C368
double DAT_0089C368 = DAT_0089C318 / DAT_007E3868;
// SYNTHETIC: GAMEMD 0x42E480
// GLOBAL: GAMEMD 0x89C350
double DAT_0089C350 = 1.0 / DAT_0089C368;
// SYNTHETIC: GAMEMD 0x42E4A0
// GLOBAL: GAMEMD 0x89C348
double DAT_0089C348 = DAT_007E3870 * 45.0;
// SYNTHETIC: GAMEMD 0x42E4C0
// GLOBAL: GAMEMD 0x89C320
double DAT_0089C320 = DAT_007E3870 * 60.0;
// SYNTHETIC: GAMEMD 0x42E4E0
// GLOBAL: GAMEMD 0x89C2F8
double DAT_0089C2F8 = DAT_007E3870 * 90.0;
// SYNTHETIC: GAMEMD 0x42E500
// GLOBAL: GAMEMD 0x89C370
int DAT_0089C370 = (int)(FUN_004CAD50(DAT_0089C2F8 - DAT_0089C320) * DAT_0089C318 * 0.5);
// SYNTHETIC: GAMEMD 0x42E540
// GLOBAL: GAMEMD 0x89C328
double DAT_0089C328 = FUN_004CADE0(DAT_0089C370 * 0.00390625);
// SYNTHETIC: GAMEMD 0x42E570
// GLOBAL: GAMEMD 0x89C340
double DAT_0089C340 = FUN_004CADE0((DAT_0089C370 * 2) / DAT_0089C318);
// SYNTHETIC: GAMEMD 0x42E5A0
// GLOBAL: GAMEMD 0x89C364
int DAT_0089C364 = (int)(DAT_0089C370 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x42E5D0
// GLOBAL: GAMEMD 0x89C310
HeaderCellInit DAT_0089C310(0, 0);
// SYNTHETIC: GAMEMD 0x42E5E0
// GLOBAL: GAMEMD 0x89C330
HeaderCoordInit DAT_0089C330(0, 0, 0);
// SYNTHETIC: GAMEMD 0x42E600
// GLOBAL: GAMEMD 0x89C358
HeaderCoordInit DAT_0089C358(128, 128, 0);
