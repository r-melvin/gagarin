// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x54EC40-0x54EE30 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7ECEB8
const double DAT_007ECEB8 = 60.0;
// GLOBAL: GAMEMD 0x7ECEC0
const double DAT_007ECEC0 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x54EC40
// GLOBAL: GAMEMD 0xABC6A0
MathTblZero4 DAT_00ABC6A0;
// SYNTHETIC: GAMEMD 0x54EC60
// GLOBAL: GAMEMD 0xABC6B8
double DAT_00ABC6B8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x54EC90
// GLOBAL: GAMEMD 0xABC708
double DAT_00ABC708 = DAT_00ABC6B8 / DAT_007ECEB8;
// SYNTHETIC: GAMEMD 0x54ECB0
// GLOBAL: GAMEMD 0xABC6F0
double DAT_00ABC6F0 = 1.0 / DAT_00ABC708;
// SYNTHETIC: GAMEMD 0x54ECD0
// GLOBAL: GAMEMD 0xABC6E8
double DAT_00ABC6E8 = DAT_007ECEC0 * 45.0;
// SYNTHETIC: GAMEMD 0x54ECF0
// GLOBAL: GAMEMD 0xABC6C0
double DAT_00ABC6C0 = DAT_007ECEC0 * 60.0;
// SYNTHETIC: GAMEMD 0x54ED10
// GLOBAL: GAMEMD 0xABC698
double DAT_00ABC698 = DAT_007ECEC0 * 90.0;
// SYNTHETIC: GAMEMD 0x54ED30
// GLOBAL: GAMEMD 0xABC710
int DAT_00ABC710 = (int)(FUN_004CAD50(DAT_00ABC698 - DAT_00ABC6C0) * DAT_00ABC6B8 * 0.5);
// SYNTHETIC: GAMEMD 0x54ED70
// GLOBAL: GAMEMD 0xABC6C8
double DAT_00ABC6C8 = FUN_004CADE0(DAT_00ABC710 * 0.00390625);
// SYNTHETIC: GAMEMD 0x54EDA0
// GLOBAL: GAMEMD 0xABC6E0
double DAT_00ABC6E0 = FUN_004CADE0((DAT_00ABC710 * 2) / DAT_00ABC6B8);
// SYNTHETIC: GAMEMD 0x54EDD0
// GLOBAL: GAMEMD 0xABC704
int DAT_00ABC704 = (int)(DAT_00ABC710 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x54EE00
// GLOBAL: GAMEMD 0xABC6B0
HeaderCellInit DAT_00ABC6B0(0, 0);
// SYNTHETIC: GAMEMD 0x54EE10
// GLOBAL: GAMEMD 0xABC6D0
HeaderCoordInit DAT_00ABC6D0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x54EE30
// GLOBAL: GAMEMD 0xABC6F8
HeaderCoordInit DAT_00ABC6F8(128, 128, 0);
