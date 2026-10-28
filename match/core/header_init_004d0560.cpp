// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4D0560
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
// GLOBAL: GAMEMD 0x7E8AF8
const double DAT_007E8AF8 = 60.0;
// GLOBAL: GAMEMD 0x7E8B00 -- degrees to radians
const double DAT_007E8B00 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4D0560
// GLOBAL: GAMEMD 0x8B3CF8
double DAT_008B3CF8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4D0590
// GLOBAL: GAMEMD 0x8B3D60
double DAT_008B3D60 = DAT_008B3CF8 / DAT_007E8AF8;
// SYNTHETIC: GAMEMD 0x4D05B0
// GLOBAL: GAMEMD 0x8B3D48
double DAT_008B3D48 = 1.0 / DAT_008B3D60;
// SYNTHETIC: GAMEMD 0x4D05D0
// GLOBAL: GAMEMD 0x8B3D40
double DAT_008B3D40 = DAT_007E8B00 * 45.0;
// SYNTHETIC: GAMEMD 0x4D05F0
// GLOBAL: GAMEMD 0x8B3D00
double DAT_008B3D00 = DAT_007E8B00 * 60.0;
// SYNTHETIC: GAMEMD 0x4D0610
// GLOBAL: GAMEMD 0x8B3CD8
double DAT_008B3CD8 = DAT_007E8B00 * 90.0;
// SYNTHETIC: GAMEMD 0x4D0630
// GLOBAL: GAMEMD 0x8B3D68
int DAT_008B3D68 = (int)(FUN_004CAD50(DAT_008B3CD8 - DAT_008B3D00) * DAT_008B3CF8 * 0.5);
// SYNTHETIC: GAMEMD 0x4D0670
// GLOBAL: GAMEMD 0x8B3D08
double DAT_008B3D08 = FUN_004CADE0(DAT_008B3D68 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4D06A0
// GLOBAL: GAMEMD 0x8B3D38
double DAT_008B3D38 = FUN_004CADE0((DAT_008B3D68 * 2) / DAT_008B3CF8);
// SYNTHETIC: GAMEMD 0x4D06D0
// GLOBAL: GAMEMD 0x8B3D5C
int DAT_008B3D5C = (int)(DAT_008B3D68 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4D0700
// GLOBAL: GAMEMD 0x8B3CF0
HeaderCellInit DAT_008B3CF0(0, 0);
// SYNTHETIC: GAMEMD 0x4D0710
// GLOBAL: GAMEMD 0x8B3D28
HeaderCoordInit DAT_008B3D28(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4D0730
// GLOBAL: GAMEMD 0x8B3D50
HeaderCoordInit DAT_008B3D50(128, 128, 0);
