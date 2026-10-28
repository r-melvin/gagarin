// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x429590
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
// GLOBAL: GAMEMD 0x7E3700
const double DAT_007E3700 = 60.0;
// GLOBAL: GAMEMD 0x7E3708 -- degrees to radians
const double DAT_007E3708 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x429590
// GLOBAL: GAMEMD 0x89C280
double DAT_0089C280 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4295C0
// GLOBAL: GAMEMD 0x89C2D0
double DAT_0089C2D0 = DAT_0089C280 / DAT_007E3700;
// SYNTHETIC: GAMEMD 0x4295E0
// GLOBAL: GAMEMD 0x89C2B8
double DAT_0089C2B8 = 1.0 / DAT_0089C2D0;
// SYNTHETIC: GAMEMD 0x429600
// GLOBAL: GAMEMD 0x89C2B0
double DAT_0089C2B0 = DAT_007E3708 * 45.0;
// SYNTHETIC: GAMEMD 0x429620
// GLOBAL: GAMEMD 0x89C288
double DAT_0089C288 = DAT_007E3708 * 60.0;
// SYNTHETIC: GAMEMD 0x429640
// GLOBAL: GAMEMD 0x89A2F8
double DAT_0089A2F8 = DAT_007E3708 * 90.0;
// SYNTHETIC: GAMEMD 0x429660
// GLOBAL: GAMEMD 0x89C2D8
int DAT_0089C2D8 = (int)(FUN_004CAD50(DAT_0089A2F8 - DAT_0089C288) * DAT_0089C280 * 0.5);
// SYNTHETIC: GAMEMD 0x4296A0
// GLOBAL: GAMEMD 0x89C290
double DAT_0089C290 = FUN_004CADE0(DAT_0089C2D8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4296D0
// GLOBAL: GAMEMD 0x89C2A8
double DAT_0089C2A8 = FUN_004CADE0((DAT_0089C2D8 * 2) / DAT_0089C280);
// SYNTHETIC: GAMEMD 0x429700
// GLOBAL: GAMEMD 0x89C2CC
int DAT_0089C2CC = (int)(DAT_0089C2D8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x429730
// GLOBAL: GAMEMD 0x89C278
HeaderCellInit DAT_0089C278(0, 0);
// SYNTHETIC: GAMEMD 0x429740
// GLOBAL: GAMEMD 0x89C298
HeaderCoordInit DAT_0089C298(0, 0, 0);
// SYNTHETIC: GAMEMD 0x429760
// GLOBAL: GAMEMD 0x89C2C0
HeaderCoordInit DAT_0089C2C0(128, 128, 0);
