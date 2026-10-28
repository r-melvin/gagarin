// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5C5AD0-0x5C5CC0 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7EE410
extern const double DAT_007EE410;
// GLOBAL: GAMEMD 0x7EE418
const double DAT_007EE418 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5C5AD0
// GLOBAL: GAMEMD 0xABF4A8
MathTblZero4 DAT_00ABF4A8;
// SYNTHETIC: GAMEMD 0x5C5AF0
// GLOBAL: GAMEMD 0xABF4C0
double DAT_00ABF4C0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5C5B20
// GLOBAL: GAMEMD 0xABF510
double DAT_00ABF510 = DAT_00ABF4C0 / DAT_007EE410;
// SYNTHETIC: GAMEMD 0x5C5B40
// GLOBAL: GAMEMD 0xABF4F8
double DAT_00ABF4F8 = 1.0 / DAT_00ABF510;
// SYNTHETIC: GAMEMD 0x5C5B60
// GLOBAL: GAMEMD 0xABF4F0
double DAT_00ABF4F0 = DAT_007EE418 * 45.0;
// SYNTHETIC: GAMEMD 0x5C5B80
// GLOBAL: GAMEMD 0xABF4C8
double DAT_00ABF4C8 = DAT_007EE418 * 60.0;
// SYNTHETIC: GAMEMD 0x5C5BA0
// GLOBAL: GAMEMD 0xABF4A0
double DAT_00ABF4A0 = DAT_007EE418 * 90.0;
// SYNTHETIC: GAMEMD 0x5C5BC0
// GLOBAL: GAMEMD 0xABF518
int DAT_00ABF518 = (int)(FUN_004CAD50(DAT_00ABF4A0 - DAT_00ABF4C8) * DAT_00ABF4C0 * 0.5);
// SYNTHETIC: GAMEMD 0x5C5C00
// GLOBAL: GAMEMD 0xABF4D0
double DAT_00ABF4D0 = FUN_004CADE0(DAT_00ABF518 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5C5C30
// GLOBAL: GAMEMD 0xABF4E8
double DAT_00ABF4E8 = FUN_004CADE0((DAT_00ABF518 * 2) / DAT_00ABF4C0);
// SYNTHETIC: GAMEMD 0x5C5C60
// GLOBAL: GAMEMD 0xABF50C
int DAT_00ABF50C = (int)(DAT_00ABF518 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5C5C90
// GLOBAL: GAMEMD 0xABF4B8
HeaderCellInit DAT_00ABF4B8(0, 0);
// SYNTHETIC: GAMEMD 0x5C5CA0
// GLOBAL: GAMEMD 0xABF4D8
HeaderCoordInit DAT_00ABF4D8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5C5CC0
// GLOBAL: GAMEMD 0xABF500
HeaderCoordInit DAT_00ABF500(128, 128, 0);
