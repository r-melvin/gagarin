// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x55F760-0x55F950 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
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
// GLOBAL: GAMEMD 0x7ED3B0
const double DAT_007ED3B0 = 60.0;
// GLOBAL: GAMEMD 0x7ED3B8
const double DAT_007ED3B8 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x55F760
// GLOBAL: GAMEMD 0xABCE28
MathTblZero4 DAT_00ABCE28;
// SYNTHETIC: GAMEMD 0x55F780
// GLOBAL: GAMEMD 0xABCE40
double DAT_00ABCE40 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x55F7B0
// GLOBAL: GAMEMD 0xABCF48
double DAT_00ABCF48 = DAT_00ABCE40 / DAT_007ED3B0;
// SYNTHETIC: GAMEMD 0x55F7D0
// GLOBAL: GAMEMD 0xABCF30
double DAT_00ABCF30 = 1.0 / DAT_00ABCF48;
// SYNTHETIC: GAMEMD 0x55F7F0
// GLOBAL: GAMEMD 0xABCF28
double DAT_00ABCF28 = DAT_007ED3B8 * 45.0;
// SYNTHETIC: GAMEMD 0x55F810
// GLOBAL: GAMEMD 0xABCE48
double DAT_00ABCE48 = DAT_007ED3B8 * 60.0;
// SYNTHETIC: GAMEMD 0x55F830
// GLOBAL: GAMEMD 0xABCE20
double DAT_00ABCE20 = DAT_007ED3B8 * 90.0;
// SYNTHETIC: GAMEMD 0x55F850
// GLOBAL: GAMEMD 0xABCF50
int DAT_00ABCF50 = (int)(FUN_004CAD50(DAT_00ABCE20 - DAT_00ABCE48) * DAT_00ABCE40 * 0.5);
// SYNTHETIC: GAMEMD 0x55F890
// GLOBAL: GAMEMD 0xABCE50
double DAT_00ABCE50 = FUN_004CADE0(DAT_00ABCF50 * 0.00390625);
// SYNTHETIC: GAMEMD 0x55F8C0
// GLOBAL: GAMEMD 0xABCE68
double DAT_00ABCE68 = FUN_004CADE0((DAT_00ABCF50 * 2) / DAT_00ABCE40);
// SYNTHETIC: GAMEMD 0x55F8F0
// GLOBAL: GAMEMD 0xABCF44
int DAT_00ABCF44 = (int)(DAT_00ABCF50 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x55F920
// GLOBAL: GAMEMD 0xABCE38
HeaderCellInit DAT_00ABCE38(0, 0);
// SYNTHETIC: GAMEMD 0x55F930
// GLOBAL: GAMEMD 0xABCE58
HeaderCoordInit DAT_00ABCE58(0, 0, 0);
// SYNTHETIC: GAMEMD 0x55F950
// GLOBAL: GAMEMD 0xABCF38
HeaderCoordInit DAT_00ABCF38(128, 128, 0);
