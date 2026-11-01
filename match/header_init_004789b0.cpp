// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4789B0
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
// GLOBAL: GAMEMD 0x7E4E98
const double DAT_007E4E98 = 60.0;
// GLOBAL: GAMEMD 0x7E4EA0 -- degrees to radians
const double DAT_007E4EA0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4789B0
// GLOBAL: GAMEMD 0x89E330
double DAT_0089E330 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4789E0
// GLOBAL: GAMEMD 0x89E380
double DAT_0089E380 = DAT_0089E330 / DAT_007E4E98;
// SYNTHETIC: GAMEMD 0x478A00
// GLOBAL: GAMEMD 0x89E368
double DAT_0089E368 = 1.0 / DAT_0089E380;
// SYNTHETIC: GAMEMD 0x478A20
// GLOBAL: GAMEMD 0x89E360
double DAT_0089E360 = DAT_007E4EA0 * 45.0;
// SYNTHETIC: GAMEMD 0x478A40
// GLOBAL: GAMEMD 0x89E338
double DAT_0089E338 = DAT_007E4EA0 * 60.0;
// SYNTHETIC: GAMEMD 0x478A60
// GLOBAL: GAMEMD 0x89E310
double DAT_0089E310 = DAT_007E4EA0 * 90.0;
// SYNTHETIC: GAMEMD 0x478A80
// GLOBAL: GAMEMD 0x89E388
int DAT_0089E388 = (int)(FUN_004CAD50(DAT_0089E310 - DAT_0089E338) * DAT_0089E330 * 0.5);
// SYNTHETIC: GAMEMD 0x478AC0
// GLOBAL: GAMEMD 0x89E340
double DAT_0089E340 = FUN_004CADE0(DAT_0089E388 * 0.00390625);
// SYNTHETIC: GAMEMD 0x478AF0
// GLOBAL: GAMEMD 0x89E358
double DAT_0089E358 = FUN_004CADE0((DAT_0089E388 * 2) / DAT_0089E330);
// SYNTHETIC: GAMEMD 0x478B20
// GLOBAL: GAMEMD 0x89E37C
int DAT_0089E37C = (int)(DAT_0089E388 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x478B50
// GLOBAL: GAMEMD 0x89E328
HeaderCellInit DAT_0089E328(0, 0);
// SYNTHETIC: GAMEMD 0x478B60
// GLOBAL: GAMEMD 0x89E348
HeaderCoordInit DAT_0089E348(0, 0, 0);
// SYNTHETIC: GAMEMD 0x478B80
// GLOBAL: GAMEMD 0x89E370
HeaderCoordInit DAT_0089E370(128, 128, 0);
