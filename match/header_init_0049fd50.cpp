// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x49FD50
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
// GLOBAL: GAMEMD 0x7E5C70
const double DAT_007E5C70 = 60.0;
// GLOBAL: GAMEMD 0x7E5C78 -- degrees to radians
const double DAT_007E5C78 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x49FD50
// GLOBAL: GAMEMD 0x89F780
double DAT_0089F780 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x49FD80
// GLOBAL: GAMEMD 0x89F7D0
double DAT_0089F7D0 = DAT_0089F780 / DAT_007E5C70;
// SYNTHETIC: GAMEMD 0x49FDA0
// GLOBAL: GAMEMD 0x89F7B8
double DAT_0089F7B8 = 1.0 / DAT_0089F7D0;
// SYNTHETIC: GAMEMD 0x49FDC0
// GLOBAL: GAMEMD 0x89F7B0
double DAT_0089F7B0 = DAT_007E5C78 * 45.0;
// SYNTHETIC: GAMEMD 0x49FDE0
// GLOBAL: GAMEMD 0x89F788
double DAT_0089F788 = DAT_007E5C78 * 60.0;
// SYNTHETIC: GAMEMD 0x49FE00
// GLOBAL: GAMEMD 0x89F760
double DAT_0089F760 = DAT_007E5C78 * 90.0;
// SYNTHETIC: GAMEMD 0x49FE20
// GLOBAL: GAMEMD 0x89F7D8
int DAT_0089F7D8 = (int)(FUN_004CAD50(DAT_0089F760 - DAT_0089F788) * DAT_0089F780 * 0.5);
// SYNTHETIC: GAMEMD 0x49FE60
// GLOBAL: GAMEMD 0x89F790
double DAT_0089F790 = FUN_004CADE0(DAT_0089F7D8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x49FE90
// GLOBAL: GAMEMD 0x89F7A8
double DAT_0089F7A8 = FUN_004CADE0((DAT_0089F7D8 * 2) / DAT_0089F780);
// SYNTHETIC: GAMEMD 0x49FEC0
// GLOBAL: GAMEMD 0x89F7CC
int DAT_0089F7CC = (int)(DAT_0089F7D8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x49FEF0
// GLOBAL: GAMEMD 0x89F778
HeaderCellInit DAT_0089F778(0, 0);
// SYNTHETIC: GAMEMD 0x49FF00
// GLOBAL: GAMEMD 0x89F798
HeaderCoordInit DAT_0089F798(0, 0, 0);
// SYNTHETIC: GAMEMD 0x49FF20
// GLOBAL: GAMEMD 0x89F7C0
HeaderCoordInit DAT_0089F7C0(128, 128, 0);
