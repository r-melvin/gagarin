// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x55C9E0-0x55CBD0 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7ED3A0
const double DAT_007ED3A0 = 60.0;
// GLOBAL: GAMEMD 0x7ED3A8
const double DAT_007ED3A8 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x55C9E0
// GLOBAL: GAMEMD 0xABCD68
MathTblZero4 DAT_00ABCD68;
// SYNTHETIC: GAMEMD 0x55CA00
// GLOBAL: GAMEMD 0xABCD80
double DAT_00ABCD80 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x55CA30
// GLOBAL: GAMEMD 0xABCDF0
double DAT_00ABCDF0 = DAT_00ABCD80 / DAT_007ED3A0;
// SYNTHETIC: GAMEMD 0x55CA50
// GLOBAL: GAMEMD 0xABCDD0
double DAT_00ABCDD0 = 1.0 / DAT_00ABCDF0;
// SYNTHETIC: GAMEMD 0x55CA70
// GLOBAL: GAMEMD 0xABCDC8
double DAT_00ABCDC8 = DAT_007ED3A8 * 45.0;
// SYNTHETIC: GAMEMD 0x55CA90
// GLOBAL: GAMEMD 0xABCD98
double DAT_00ABCD98 = DAT_007ED3A8 * 60.0;
// SYNTHETIC: GAMEMD 0x55CAB0
// GLOBAL: GAMEMD 0xABCD60
double DAT_00ABCD60 = DAT_007ED3A8 * 90.0;
// SYNTHETIC: GAMEMD 0x55CAD0
// GLOBAL: GAMEMD 0xABCDF8
int DAT_00ABCDF8 = (int)(FUN_004CAD50(DAT_00ABCD60 - DAT_00ABCD98) * DAT_00ABCD80 * 0.5);
// SYNTHETIC: GAMEMD 0x55CB10
// GLOBAL: GAMEMD 0xABCDA0
double DAT_00ABCDA0 = FUN_004CADE0(DAT_00ABCDF8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x55CB40
// GLOBAL: GAMEMD 0xABCDC0
double DAT_00ABCDC0 = FUN_004CADE0((DAT_00ABCDF8 * 2) / DAT_00ABCD80);
// SYNTHETIC: GAMEMD 0x55CB70
// GLOBAL: GAMEMD 0xABCDEC
int DAT_00ABCDEC = (int)(DAT_00ABCDF8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x55CBA0
// GLOBAL: GAMEMD 0xABCD78
HeaderCellInit DAT_00ABCD78(0, 0);
// SYNTHETIC: GAMEMD 0x55CBB0
// GLOBAL: GAMEMD 0xABCDB0
HeaderCoordInit DAT_00ABCDB0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x55CBD0
// GLOBAL: GAMEMD 0xABCDE0
HeaderCoordInit DAT_00ABCDE0(128, 128, 0);
