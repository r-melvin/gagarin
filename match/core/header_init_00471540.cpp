// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x471540
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
// GLOBAL: GAMEMD 0x7E4AC0
const double DAT_007E4AC0 = 60.0;
// GLOBAL: GAMEMD 0x7E4AC8 -- degrees to radians
const double DAT_007E4AC8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x471540
// GLOBAL: GAMEMD 0x89E120
double DAT_0089E120 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4715B0
// GLOBAL: GAMEMD 0x89E150
double DAT_0089E150 = DAT_007E4AC8 * 45.0;
// SYNTHETIC: GAMEMD 0x4715D0
// GLOBAL: GAMEMD 0x89E128
double DAT_0089E128 = DAT_007E4AC8 * 60.0;
// SYNTHETIC: GAMEMD 0x4715F0
// GLOBAL: GAMEMD 0x89E0E8
double DAT_0089E0E8 = DAT_007E4AC8 * 90.0;
// SYNTHETIC: GAMEMD 0x471610
// GLOBAL: GAMEMD 0x89E178
int DAT_0089E178 = (int)(FUN_004CAD50(DAT_0089E0E8 - DAT_0089E128) * DAT_0089E120 * 0.5);
// SYNTHETIC: GAMEMD 0x471650
// GLOBAL: GAMEMD 0x89E130
double DAT_0089E130 = FUN_004CADE0(DAT_0089E178 * 0.00390625);
// SYNTHETIC: GAMEMD 0x471680
// GLOBAL: GAMEMD 0x89E148
double DAT_0089E148 = FUN_004CADE0((DAT_0089E178 * 2) / DAT_0089E120);
// SYNTHETIC: GAMEMD 0x4716B0
// GLOBAL: GAMEMD 0x89E16C
int DAT_0089E16C = (int)(DAT_0089E178 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4716E0
// GLOBAL: GAMEMD 0x89E118
HeaderCellInit DAT_0089E118(0, 0);
// SYNTHETIC: GAMEMD 0x4716F0
// GLOBAL: GAMEMD 0x89E138
HeaderCoordInit DAT_0089E138(0, 0, 0);
// SYNTHETIC: GAMEMD 0x471710
// GLOBAL: GAMEMD 0x89E160
HeaderCoordInit DAT_0089E160(128, 128, 0);
