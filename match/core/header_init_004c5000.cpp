// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4C5000
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
// GLOBAL: GAMEMD 0x7E8728
const double DAT_007E8728 = 60.0;
// GLOBAL: GAMEMD 0x7E8730 -- degrees to radians
const double DAT_007E8730 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4C5000
// GLOBAL: GAMEMD 0x8A3840
double DAT_008A3840 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4C5070
// GLOBAL: GAMEMD 0x8A3888
double DAT_008A3888 = DAT_007E8730 * 45.0;
// SYNTHETIC: GAMEMD 0x4C5090
// GLOBAL: GAMEMD 0x8A3848
double DAT_008A3848 = DAT_007E8730 * 60.0;
// SYNTHETIC: GAMEMD 0x4C50B0
// GLOBAL: GAMEMD 0x8A3820
double DAT_008A3820 = DAT_007E8730 * 90.0;
// SYNTHETIC: GAMEMD 0x4C50D0
// GLOBAL: GAMEMD 0x8A38B0
int DAT_008A38B0 = (int)(FUN_004CAD50(DAT_008A3820 - DAT_008A3848) * DAT_008A3840 * 0.5);
// SYNTHETIC: GAMEMD 0x4C5110
// GLOBAL: GAMEMD 0x8A3850
double DAT_008A3850 = FUN_004CADE0(DAT_008A38B0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4C5140
// GLOBAL: GAMEMD 0x8A3868
double DAT_008A3868 = FUN_004CADE0((DAT_008A38B0 * 2) / DAT_008A3840);
// SYNTHETIC: GAMEMD 0x4C5170
// GLOBAL: GAMEMD 0x8A38A4
int DAT_008A38A4 = (int)(DAT_008A38B0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4C51A0
// GLOBAL: GAMEMD 0x8A3838
HeaderCellInit DAT_008A3838(0, 0);
// SYNTHETIC: GAMEMD 0x4C51B0
// GLOBAL: GAMEMD 0x8A3858
HeaderCoordInit DAT_008A3858(0, 0, 0);
