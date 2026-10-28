// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x543C40-0x543E30 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7EC440
const double DAT_007EC440 = 60.0;
// GLOBAL: GAMEMD 0x7EC448
const double DAT_007EC448 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x543C40
// GLOBAL: GAMEMD 0xAA1040
MathTblZero4 DAT_00AA1040;
// SYNTHETIC: GAMEMD 0x543C60
// GLOBAL: GAMEMD 0xAA1070
double DAT_00AA1070 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x543C90
// GLOBAL: GAMEMD 0xABC2C0
double DAT_00ABC2C0 = DAT_00AA1070 / DAT_007EC440;
// SYNTHETIC: GAMEMD 0x543CB0
// GLOBAL: GAMEMD 0xABC1F0
double DAT_00ABC1F0 = 1.0 / DAT_00ABC2C0;
// SYNTHETIC: GAMEMD 0x543CD0
// GLOBAL: GAMEMD 0xABC1E0
double DAT_00ABC1E0 = DAT_007EC448 * 45.0;
// SYNTHETIC: GAMEMD 0x543CF0
// GLOBAL: GAMEMD 0xAA1128
double DAT_00AA1128 = DAT_007EC448 * 60.0;
// SYNTHETIC: GAMEMD 0x543D10
// GLOBAL: GAMEMD 0xAA0E30
double DAT_00AA0E30 = DAT_007EC448 * 90.0;
// SYNTHETIC: GAMEMD 0x543D30
// GLOBAL: GAMEMD 0xABC550
int DAT_00ABC550 = (int)(FUN_004CAD50(DAT_00AA0E30 - DAT_00AA1128) * DAT_00AA1070 * 0.5);
// SYNTHETIC: GAMEMD 0x543D70
// GLOBAL: GAMEMD 0xAA1138
double DAT_00AA1138 = FUN_004CADE0(DAT_00ABC550 * 0.00390625);
// SYNTHETIC: GAMEMD 0x543DA0
// GLOBAL: GAMEMD 0xABB118
double DAT_00ABB118 = FUN_004CADE0((DAT_00ABC550 * 2) / DAT_00AA1070);
// SYNTHETIC: GAMEMD 0x543DD0
// GLOBAL: GAMEMD 0xABC2BC
int DAT_00ABC2BC = (int)(DAT_00ABC550 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x543E00
// GLOBAL: GAMEMD 0xAA105C
HeaderCellInit DAT_00AA105C(0, 0);
// SYNTHETIC: GAMEMD 0x543E10
// GLOBAL: GAMEMD 0xABB0F8
HeaderCoordInit DAT_00ABB0F8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x543E30
// GLOBAL: GAMEMD 0xABC200
HeaderCoordInit DAT_00ABC200(128, 128, 0);
