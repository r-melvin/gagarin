// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4C6360
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
// GLOBAL: GAMEMD 0x7E8818
const double DAT_007E8818 = 60.0;
// GLOBAL: GAMEMD 0x7E8820 -- degrees to radians
const double DAT_007E8820 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4C6360
// GLOBAL: GAMEMD 0x8A39A0
double DAT_008A39A0 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4C63D0
// GLOBAL: GAMEMD 0x8A39D0
double DAT_008A39D0 = DAT_007E8820 * 45.0;
// SYNTHETIC: GAMEMD 0x4C63F0
// GLOBAL: GAMEMD 0x8A39A8
double DAT_008A39A8 = DAT_007E8820 * 60.0;
// SYNTHETIC: GAMEMD 0x4C6410
// GLOBAL: GAMEMD 0x8A3980
double DAT_008A3980 = DAT_007E8820 * 90.0;
// SYNTHETIC: GAMEMD 0x4C6430
// GLOBAL: GAMEMD 0x8A39F8
int DAT_008A39F8 = (int)(FUN_004CAD50(DAT_008A3980 - DAT_008A39A8) * DAT_008A39A0 * 0.5);
// SYNTHETIC: GAMEMD 0x4C6470
// GLOBAL: GAMEMD 0x8A39B0
double DAT_008A39B0 = FUN_004CADE0(DAT_008A39F8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4C64A0
// GLOBAL: GAMEMD 0x8A39C8
double DAT_008A39C8 = FUN_004CADE0((DAT_008A39F8 * 2) / DAT_008A39A0);
// SYNTHETIC: GAMEMD 0x4C64D0
// GLOBAL: GAMEMD 0x8A39EC
int DAT_008A39EC = (int)(DAT_008A39F8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4C6500
// GLOBAL: GAMEMD 0x8A3998
HeaderCellInit DAT_008A3998(0, 0);
// SYNTHETIC: GAMEMD 0x4C6510
// GLOBAL: GAMEMD 0x8A39B8
HeaderCoordInit DAT_008A39B8(0, 0, 0);
