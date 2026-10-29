// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4F0EF0
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
// GLOBAL: GAMEMD 0x7EA5E0
const double DAT_007EA5E0 = 60.0;
// GLOBAL: GAMEMD 0x7EA5E8 -- degrees to radians
const double DAT_007EA5E8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4F0EF0
// GLOBAL: GAMEMD 0xA8EE00
double DAT_00A8EE00 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4F0F60
// GLOBAL: GAMEMD 0xA8EE50
double DAT_00A8EE50 = DAT_007EA5E8 * 45.0;
// SYNTHETIC: GAMEMD 0x4F0F80
// GLOBAL: GAMEMD 0xA8EE08
double DAT_00A8EE08 = DAT_007EA5E8 * 60.0;
// SYNTHETIC: GAMEMD 0x4F0FA0
// GLOBAL: GAMEMD 0xA8EDE0
double DAT_00A8EDE0 = DAT_007EA5E8 * 90.0;
// SYNTHETIC: GAMEMD 0x4F0FC0
// GLOBAL: GAMEMD 0xA8EE78
int DAT_00A8EE78 = (int)(FUN_004CAD50(DAT_00A8EDE0 - DAT_00A8EE08) * DAT_00A8EE00 * 0.5);
// SYNTHETIC: GAMEMD 0x4F1000
// GLOBAL: GAMEMD 0xA8EE10
double DAT_00A8EE10 = FUN_004CADE0(DAT_00A8EE78 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4F1030
// GLOBAL: GAMEMD 0xA8EE28
double DAT_00A8EE28 = FUN_004CADE0((DAT_00A8EE78 * 2) / DAT_00A8EE00);
// SYNTHETIC: GAMEMD 0x4F1060
// GLOBAL: GAMEMD 0xA8EE6C
int DAT_00A8EE6C = (int)(DAT_00A8EE78 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4F1090
// GLOBAL: GAMEMD 0xA8EDFC
HeaderCellInit DAT_00A8EDFC(0, 0);
// SYNTHETIC: GAMEMD 0x4F10A0
// GLOBAL: GAMEMD 0xA8EE18
HeaderCoordInit DAT_00A8EE18(0, 0, 0);
