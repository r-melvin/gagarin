// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4A2160
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
// GLOBAL: GAMEMD 0x7E5D80
const double DAT_007E5D80 = 60.0;
// GLOBAL: GAMEMD 0x7E5D88 -- degrees to radians
const double DAT_007E5D88 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4A2160
// GLOBAL: GAMEMD 0x89F900
double DAT_0089F900 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4A21D0
// GLOBAL: GAMEMD 0x89F930
double DAT_0089F930 = DAT_007E5D88 * 45.0;
// SYNTHETIC: GAMEMD 0x4A21F0
// GLOBAL: GAMEMD 0x89F908
double DAT_0089F908 = DAT_007E5D88 * 60.0;
// SYNTHETIC: GAMEMD 0x4A2210
// GLOBAL: GAMEMD 0x89F8E0
double DAT_0089F8E0 = DAT_007E5D88 * 90.0;
// SYNTHETIC: GAMEMD 0x4A2230
// GLOBAL: GAMEMD 0x89F958
int DAT_0089F958 = (int)(FUN_004CAD50(DAT_0089F8E0 - DAT_0089F908) * DAT_0089F900 * 0.5);
// SYNTHETIC: GAMEMD 0x4A2270
// GLOBAL: GAMEMD 0x89F910
double DAT_0089F910 = FUN_004CADE0(DAT_0089F958 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4A22A0
// GLOBAL: GAMEMD 0x89F928
double DAT_0089F928 = FUN_004CADE0((DAT_0089F958 * 2) / DAT_0089F900);
// SYNTHETIC: GAMEMD 0x4A22D0
// GLOBAL: GAMEMD 0x89F94C
int DAT_0089F94C = (int)(DAT_0089F958 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4A2300
// GLOBAL: GAMEMD 0x89F8F8
HeaderCellInit DAT_0089F8F8(0, 0);
// SYNTHETIC: GAMEMD 0x4A2310
// GLOBAL: GAMEMD 0x89F918
HeaderCoordInit DAT_0089F918(0, 0, 0);
