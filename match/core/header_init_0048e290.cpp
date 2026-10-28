// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x48E290
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E5200
const double DAT_007E5200 = 60.0;
// GLOBAL: GAMEMD 0x7E5208 -- degrees to radians
const double DAT_007E5208 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x48E290
// GLOBAL: GAMEMD 0x89E9D8
double DAT_0089E9D8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x48E2C0
// GLOBAL: GAMEMD 0x89EC18
double DAT_0089EC18 = DAT_0089E9D8 / DAT_007E5200;
// SYNTHETIC: GAMEMD 0x48E2E0
// GLOBAL: GAMEMD 0x89EC00
double DAT_0089EC00 = 1.0 / DAT_0089EC18;
// SYNTHETIC: GAMEMD 0x48E300
// GLOBAL: GAMEMD 0x89EBF8
double DAT_0089EBF8 = DAT_007E5208 * 45.0;
// SYNTHETIC: GAMEMD 0x48E320
// GLOBAL: GAMEMD 0x89E9E0
double DAT_0089E9E0 = DAT_007E5208 * 60.0;
// SYNTHETIC: GAMEMD 0x48E340
// GLOBAL: GAMEMD 0x89E9B8
double DAT_0089E9B8 = DAT_007E5208 * 90.0;
// SYNTHETIC: GAMEMD 0x48E360
// GLOBAL: GAMEMD 0x89EC20
int DAT_0089EC20 = (int)(FUN_004CAD50(DAT_0089E9B8 - DAT_0089E9E0) * DAT_0089E9D8 * 0.5);
// SYNTHETIC: GAMEMD 0x48E3A0
// GLOBAL: GAMEMD 0x89E9E8
double DAT_0089E9E8 = FUN_004CADE0(DAT_0089EC20 * 0.00390625);
// SYNTHETIC: GAMEMD 0x48E3D0
// GLOBAL: GAMEMD 0x89EBF0
double DAT_0089EBF0 = FUN_004CADE0((DAT_0089EC20 * 2) / DAT_0089E9D8);
// SYNTHETIC: GAMEMD 0x48E400
// GLOBAL: GAMEMD 0x89EC14
int DAT_0089EC14 = (int)(DAT_0089EC20 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x48E430
// GLOBAL: GAMEMD 0x89E9D0
HeaderCellInit DAT_0089E9D0(0, 0);
// SYNTHETIC: GAMEMD 0x48E440
// GLOBAL: GAMEMD 0x89EA30
HeaderCoordInit DAT_0089EA30(0, 0, 0);
// SYNTHETIC: GAMEMD 0x48E460
// GLOBAL: GAMEMD 0x89EC08
HeaderCoordInit DAT_0089EC08(128, 128, 0);
