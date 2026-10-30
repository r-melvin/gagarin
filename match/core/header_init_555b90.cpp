// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x555B90-0x555D80 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
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
// GLOBAL: GAMEMD 0x7ED090
const double DAT_007ED090 = 60.0;
// GLOBAL: GAMEMD 0x7ED098
const double DAT_007ED098 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x555B90
// GLOBAL: GAMEMD 0xABCAA0
MathTblZero4 DAT_00ABCAA0;
// SYNTHETIC: GAMEMD 0x555BB0
// GLOBAL: GAMEMD 0xABCAB8
double DAT_00ABCAB8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x555BE0
// GLOBAL: GAMEMD 0xABCB08
double DAT_00ABCB08 = DAT_00ABCAB8 / DAT_007ED090;
// SYNTHETIC: GAMEMD 0x555C00
// GLOBAL: GAMEMD 0xABCAF0
double DAT_00ABCAF0 = 1.0 / DAT_00ABCB08;
// SYNTHETIC: GAMEMD 0x555C20
// GLOBAL: GAMEMD 0xABCAE8
double DAT_00ABCAE8 = DAT_007ED098 * 45.0;
// SYNTHETIC: GAMEMD 0x555C40
// GLOBAL: GAMEMD 0xABCAC0
double DAT_00ABCAC0 = DAT_007ED098 * 60.0;
// SYNTHETIC: GAMEMD 0x555C60
// GLOBAL: GAMEMD 0xABCA98
double DAT_00ABCA98 = DAT_007ED098 * 90.0;
// SYNTHETIC: GAMEMD 0x555C80
// GLOBAL: GAMEMD 0xABCB10
int DAT_00ABCB10 = (int)(FUN_004CAD50(DAT_00ABCA98 - DAT_00ABCAC0) * DAT_00ABCAB8 * 0.5);
// SYNTHETIC: GAMEMD 0x555CC0
// GLOBAL: GAMEMD 0xABCAC8
double DAT_00ABCAC8 = FUN_004CADE0(DAT_00ABCB10 * 0.00390625);
// SYNTHETIC: GAMEMD 0x555CF0
// GLOBAL: GAMEMD 0xABCAE0
double DAT_00ABCAE0 = FUN_004CADE0((DAT_00ABCB10 * 2) / DAT_00ABCAB8);
// SYNTHETIC: GAMEMD 0x555D20
// GLOBAL: GAMEMD 0xABCB04
int DAT_00ABCB04 = (int)(DAT_00ABCB10 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x555D50
// GLOBAL: GAMEMD 0xABCAB0
HeaderCellInit DAT_00ABCAB0(0, 0);
// SYNTHETIC: GAMEMD 0x555D60
// GLOBAL: GAMEMD 0xABCAD0
HeaderCoordInit DAT_00ABCAD0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x555D80
// GLOBAL: GAMEMD 0xABCAF8
HeaderCoordInit DAT_00ABCAF8(128, 128, 0);
