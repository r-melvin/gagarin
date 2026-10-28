// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x558530-0x558720 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7ED2D0
const double DAT_007ED2D0 = 60.0;
// GLOBAL: GAMEMD 0x7ED2D8
const double DAT_007ED2D8 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x558530
// GLOBAL: GAMEMD 0xABCBC8
MathTblZero4 DAT_00ABCBC8;
// SYNTHETIC: GAMEMD 0x558550
// GLOBAL: GAMEMD 0xABCBE0
double DAT_00ABCBE0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x558580
// GLOBAL: GAMEMD 0xABCC30
double DAT_00ABCC30 = DAT_00ABCBE0 / DAT_007ED2D0;
// SYNTHETIC: GAMEMD 0x5585A0
// GLOBAL: GAMEMD 0xABCC18
double DAT_00ABCC18 = 1.0 / DAT_00ABCC30;
// SYNTHETIC: GAMEMD 0x5585C0
// GLOBAL: GAMEMD 0xABCC10
double DAT_00ABCC10 = DAT_007ED2D8 * 45.0;
// SYNTHETIC: GAMEMD 0x5585E0
// GLOBAL: GAMEMD 0xABCBE8
double DAT_00ABCBE8 = DAT_007ED2D8 * 60.0;
// SYNTHETIC: GAMEMD 0x558600
// GLOBAL: GAMEMD 0xABCBC0
double DAT_00ABCBC0 = DAT_007ED2D8 * 90.0;
// SYNTHETIC: GAMEMD 0x558620
// GLOBAL: GAMEMD 0xABCC38
int DAT_00ABCC38 = (int)(FUN_004CAD50(DAT_00ABCBC0 - DAT_00ABCBE8) * DAT_00ABCBE0 * 0.5);
// SYNTHETIC: GAMEMD 0x558660
// GLOBAL: GAMEMD 0xABCBF0
double DAT_00ABCBF0 = FUN_004CADE0(DAT_00ABCC38 * 0.00390625);
// SYNTHETIC: GAMEMD 0x558690
// GLOBAL: GAMEMD 0xABCC08
double DAT_00ABCC08 = FUN_004CADE0((DAT_00ABCC38 * 2) / DAT_00ABCBE0);
// SYNTHETIC: GAMEMD 0x5586C0
// GLOBAL: GAMEMD 0xABCC2C
int DAT_00ABCC2C = (int)(DAT_00ABCC38 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5586F0
// GLOBAL: GAMEMD 0xABCBD8
HeaderCellInit DAT_00ABCBD8(0, 0);
// SYNTHETIC: GAMEMD 0x558700
// GLOBAL: GAMEMD 0xABCBF8
HeaderCoordInit DAT_00ABCBF8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x558720
// GLOBAL: GAMEMD 0xABCC20
HeaderCoordInit DAT_00ABCC20(128, 128, 0);
