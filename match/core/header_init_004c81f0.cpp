// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4C81F0
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
// GLOBAL: GAMEMD 0x7E8828
const double DAT_007E8828 = 60.0;
// GLOBAL: GAMEMD 0x7E8830 -- degrees to radians
const double DAT_007E8830 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4C81F0
// GLOBAL: GAMEMD 0x8B3A20
double DAT_008B3A20 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4C8220
// GLOBAL: GAMEMD 0x8B3A70
double DAT_008B3A70 = DAT_008B3A20 / DAT_007E8828;
// SYNTHETIC: GAMEMD 0x4C8240
// GLOBAL: GAMEMD 0x8B3A58
double DAT_008B3A58 = 1.0 / DAT_008B3A70;
// SYNTHETIC: GAMEMD 0x4C8260
// GLOBAL: GAMEMD 0x8B3A50
double DAT_008B3A50 = DAT_007E8830 * 45.0;
// SYNTHETIC: GAMEMD 0x4C8280
// GLOBAL: GAMEMD 0x8B3A28
double DAT_008B3A28 = DAT_007E8830 * 60.0;
// SYNTHETIC: GAMEMD 0x4C82A0
// GLOBAL: GAMEMD 0x8A3A00
double DAT_008A3A00 = DAT_007E8830 * 90.0;
// SYNTHETIC: GAMEMD 0x4C82C0
// GLOBAL: GAMEMD 0x8B3A78
int DAT_008B3A78 = (int)(FUN_004CAD50(DAT_008A3A00 - DAT_008B3A28) * DAT_008B3A20 * 0.5);
// SYNTHETIC: GAMEMD 0x4C8300
// GLOBAL: GAMEMD 0x8B3A30
double DAT_008B3A30 = FUN_004CADE0(DAT_008B3A78 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4C8330
// GLOBAL: GAMEMD 0x8B3A48
double DAT_008B3A48 = FUN_004CADE0((DAT_008B3A78 * 2) / DAT_008B3A20);
// SYNTHETIC: GAMEMD 0x4C8360
// GLOBAL: GAMEMD 0x8B3A6C
int DAT_008B3A6C = (int)(DAT_008B3A78 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4C8390
// GLOBAL: GAMEMD 0x8B3A18
HeaderCellInit DAT_008B3A18(0, 0);
// SYNTHETIC: GAMEMD 0x4C83A0
// GLOBAL: GAMEMD 0x8B3A38
HeaderCoordInit DAT_008B3A38(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4C83C0
// GLOBAL: GAMEMD 0x8B3A60
HeaderCoordInit DAT_008B3A60(128, 128, 0);
