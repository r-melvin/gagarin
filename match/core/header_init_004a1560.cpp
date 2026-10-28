// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4A1560
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
// GLOBAL: GAMEMD 0x7E5D68
const double DAT_007E5D68 = 60.0;
// GLOBAL: GAMEMD 0x7E5D70 -- degrees to radians
const double DAT_007E5D70 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4A1560
// GLOBAL: GAMEMD 0x89F800
double DAT_0089F800 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4A1590
// GLOBAL: GAMEMD 0x89F850
double DAT_0089F850 = DAT_0089F800 / DAT_007E5D68;
// SYNTHETIC: GAMEMD 0x4A15B0
// GLOBAL: GAMEMD 0x89F838
double DAT_0089F838 = 1.0 / DAT_0089F850;
// SYNTHETIC: GAMEMD 0x4A15D0
// GLOBAL: GAMEMD 0x89F830
double DAT_0089F830 = DAT_007E5D70 * 45.0;
// SYNTHETIC: GAMEMD 0x4A15F0
// GLOBAL: GAMEMD 0x89F808
double DAT_0089F808 = DAT_007E5D70 * 60.0;
// SYNTHETIC: GAMEMD 0x4A1610
// GLOBAL: GAMEMD 0x89F7E0
double DAT_0089F7E0 = DAT_007E5D70 * 90.0;
// SYNTHETIC: GAMEMD 0x4A1630
// GLOBAL: GAMEMD 0x89F858
int DAT_0089F858 = (int)(FUN_004CAD50(DAT_0089F7E0 - DAT_0089F808) * DAT_0089F800 * 0.5);
// SYNTHETIC: GAMEMD 0x4A1670
// GLOBAL: GAMEMD 0x89F810
double DAT_0089F810 = FUN_004CADE0(DAT_0089F858 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4A16A0
// GLOBAL: GAMEMD 0x89F828
double DAT_0089F828 = FUN_004CADE0((DAT_0089F858 * 2) / DAT_0089F800);
// SYNTHETIC: GAMEMD 0x4A16D0
// GLOBAL: GAMEMD 0x89F84C
int DAT_0089F84C = (int)(DAT_0089F858 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4A1700
// GLOBAL: GAMEMD 0x89F7F8
HeaderCellInit DAT_0089F7F8(0, 0);
// SYNTHETIC: GAMEMD 0x4A1710
// GLOBAL: GAMEMD 0x89F818
HeaderCoordInit DAT_0089F818(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4A1730
// GLOBAL: GAMEMD 0x89F840
HeaderCoordInit DAT_0089F840(128, 128, 0);
