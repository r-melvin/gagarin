// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4C35A0
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
// GLOBAL: GAMEMD 0x7E86C8
const double DAT_007E86C8 = 60.0;
// GLOBAL: GAMEMD 0x7E86D0 -- degrees to radians
const double DAT_007E86D0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4C35A0
// GLOBAL: GAMEMD 0x8A0EE8
double DAT_008A0EE8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4C3610
// GLOBAL: GAMEMD 0x8A0F18
double DAT_008A0F18 = DAT_007E86D0 * 45.0;
// SYNTHETIC: GAMEMD 0x4C3630
// GLOBAL: GAMEMD 0x8A0EF0
double DAT_008A0EF0 = DAT_007E86D0 * 60.0;
// SYNTHETIC: GAMEMD 0x4C3650
// GLOBAL: GAMEMD 0x8A0EC8
double DAT_008A0EC8 = DAT_007E86D0 * 90.0;
// SYNTHETIC: GAMEMD 0x4C3670
// GLOBAL: GAMEMD 0x8A0F40
int DAT_008A0F40 = (int)(FUN_004CAD50(DAT_008A0EC8 - DAT_008A0EF0) * DAT_008A0EE8 * 0.5);
// SYNTHETIC: GAMEMD 0x4C36B0
// GLOBAL: GAMEMD 0x8A0EF8
double DAT_008A0EF8 = FUN_004CADE0(DAT_008A0F40 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4C36E0
// GLOBAL: GAMEMD 0x8A0F10
double DAT_008A0F10 = FUN_004CADE0((DAT_008A0F40 * 2) / DAT_008A0EE8);
// SYNTHETIC: GAMEMD 0x4C3710
// GLOBAL: GAMEMD 0x8A0F34
int DAT_008A0F34 = (int)(DAT_008A0F40 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4C3740
// GLOBAL: GAMEMD 0x8A0EE0
HeaderCellInit DAT_008A0EE0(0, 0);
// SYNTHETIC: GAMEMD 0x4C3750
// GLOBAL: GAMEMD 0x8A0F00
HeaderCoordInit DAT_008A0F00(0, 0, 0);
