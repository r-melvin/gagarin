// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4BA3B0
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
// GLOBAL: GAMEMD 0x7E85A8
const double DAT_007E85A8 = 60.0;
// GLOBAL: GAMEMD 0x7E85B0 -- degrees to radians
const double DAT_007E85B0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4BA3B0
// GLOBAL: GAMEMD 0x8A0968
double DAT_008A0968 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4BA420
// GLOBAL: GAMEMD 0x8A0DA0
double DAT_008A0DA0 = DAT_007E85B0 * 45.0;
// SYNTHETIC: GAMEMD 0x4BA440
// GLOBAL: GAMEMD 0x8A0970
double DAT_008A0970 = DAT_007E85B0 * 60.0;
// SYNTHETIC: GAMEMD 0x4BA460
// GLOBAL: GAMEMD 0x8A0928
double DAT_008A0928 = DAT_007E85B0 * 90.0;
// SYNTHETIC: GAMEMD 0x4BA480
// GLOBAL: GAMEMD 0x8A0DC8
int DAT_008A0DC8 = (int)(FUN_004CAD50(DAT_008A0928 - DAT_008A0970) * DAT_008A0968 * 0.5);
// SYNTHETIC: GAMEMD 0x4BA4C0
// GLOBAL: GAMEMD 0x8A0978
double DAT_008A0978 = FUN_004CADE0(DAT_008A0DC8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4BA4F0
// GLOBAL: GAMEMD 0x8A0D98
double DAT_008A0D98 = FUN_004CADE0((DAT_008A0DC8 * 2) / DAT_008A0968);
// SYNTHETIC: GAMEMD 0x4BA520
// GLOBAL: GAMEMD 0x8A0DBC
int DAT_008A0DBC = (int)(DAT_008A0DC8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4BA550
// GLOBAL: GAMEMD 0x8A0940
HeaderCellInit DAT_008A0940(0, 0);
// SYNTHETIC: GAMEMD 0x4BA560
// GLOBAL: GAMEMD 0x8A0D88
HeaderCoordInit DAT_008A0D88(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4BA580
// GLOBAL: GAMEMD 0x8A0DB0
HeaderCoordInit DAT_008A0DB0(128, 128, 0);
