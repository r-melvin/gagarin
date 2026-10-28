// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x421CB0
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
// GLOBAL: GAMEMD 0x7E3308
const double DAT_007E3308 = 60.0;
// GLOBAL: GAMEMD 0x7E3310 -- degrees to radians
const double DAT_007E3310 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x421CB0
// GLOBAL: GAMEMD 0x89A158
double DAT_0089A158 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x421CE0
// GLOBAL: GAMEMD 0x89A1B8
double DAT_0089A1B8 = DAT_0089A158 / DAT_007E3308;
// SYNTHETIC: GAMEMD 0x421D00
// GLOBAL: GAMEMD 0x89A1A0
double DAT_0089A1A0 = 1.0 / DAT_0089A1B8;
// SYNTHETIC: GAMEMD 0x421D20
// GLOBAL: GAMEMD 0x89A198
double DAT_0089A198 = DAT_007E3310 * 45.0;
// SYNTHETIC: GAMEMD 0x421D40
// GLOBAL: GAMEMD 0x89A168
double DAT_0089A168 = DAT_007E3310 * 60.0;
// SYNTHETIC: GAMEMD 0x421D60
// GLOBAL: GAMEMD 0x89A138
double DAT_0089A138 = DAT_007E3310 * 90.0;
// SYNTHETIC: GAMEMD 0x421D80
// GLOBAL: GAMEMD 0x89A1C0
int DAT_0089A1C0 = (int)(FUN_004CAD50(DAT_0089A138 - DAT_0089A168) * DAT_0089A158 * 0.5);
// SYNTHETIC: GAMEMD 0x421DC0
// GLOBAL: GAMEMD 0x89A170
double DAT_0089A170 = FUN_004CADE0(DAT_0089A1C0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x421DF0
// GLOBAL: GAMEMD 0x89A188
double DAT_0089A188 = FUN_004CADE0((DAT_0089A1C0 * 2) / DAT_0089A158);
// SYNTHETIC: GAMEMD 0x421E20
// GLOBAL: GAMEMD 0x89A1B4
int DAT_0089A1B4 = (int)(DAT_0089A1C0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x421E50
// GLOBAL: GAMEMD 0x89A150
HeaderCellInit DAT_0089A150(0, 0);
// SYNTHETIC: GAMEMD 0x421E60
// GLOBAL: GAMEMD 0x89A178
HeaderCoordInit DAT_0089A178(0, 0, 0);
// SYNTHETIC: GAMEMD 0x421E80
// GLOBAL: GAMEMD 0x89A1A8
HeaderCoordInit DAT_0089A1A8(128, 128, 0);
