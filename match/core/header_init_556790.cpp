// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x556790-0x556980 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7ED0B8
const double DAT_007ED0B8 = 60.0;
// GLOBAL: GAMEMD 0x7ED0C0
const double DAT_007ED0C0 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x556790
// GLOBAL: GAMEMD 0xABCB38
double DAT_00ABCB38 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5567C0
// GLOBAL: GAMEMD 0xABCBA0
double DAT_00ABCBA0 = DAT_00ABCB38 / DAT_007ED0B8;
// SYNTHETIC: GAMEMD 0x5567E0
// GLOBAL: GAMEMD 0xABCB70
double DAT_00ABCB70 = 1.0 / DAT_00ABCBA0;
// SYNTHETIC: GAMEMD 0x556800
// GLOBAL: GAMEMD 0xABCB68
double DAT_00ABCB68 = DAT_007ED0C0 * 45.0;
// SYNTHETIC: GAMEMD 0x556820
// GLOBAL: GAMEMD 0xABCB40
double DAT_00ABCB40 = DAT_007ED0C0 * 60.0;
// SYNTHETIC: GAMEMD 0x556840
// GLOBAL: GAMEMD 0xABCB18
double DAT_00ABCB18 = DAT_007ED0C0 * 90.0;
// SYNTHETIC: GAMEMD 0x556860
// GLOBAL: GAMEMD 0xABCBA8
int DAT_00ABCBA8 = (int)(FUN_004CAD50(DAT_00ABCB18 - DAT_00ABCB40) * DAT_00ABCB38 * 0.5);
// SYNTHETIC: GAMEMD 0x5568A0
// GLOBAL: GAMEMD 0xABCB48
double DAT_00ABCB48 = FUN_004CADE0(DAT_00ABCBA8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5568D0
// GLOBAL: GAMEMD 0xABCB60
double DAT_00ABCB60 = FUN_004CADE0((DAT_00ABCBA8 * 2) / DAT_00ABCB38);
// SYNTHETIC: GAMEMD 0x556900
// GLOBAL: GAMEMD 0xABCB9C
int DAT_00ABCB9C = (int)(DAT_00ABCBA8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x556930
// GLOBAL: GAMEMD 0xABCB30
HeaderCellInit DAT_00ABCB30(0, 0);
// SYNTHETIC: GAMEMD 0x556940
// GLOBAL: GAMEMD 0xABCB50
HeaderCoordInit DAT_00ABCB50(0, 0, 0);
// SYNTHETIC: GAMEMD 0x556960
// GLOBAL: GAMEMD 0xABCB90
HeaderCoordInit DAT_00ABCB90(128, 128, 0);
// SYNTHETIC: GAMEMD 0x556980
// GLOBAL: GAMEMD 0xABCB20
MathTblZero4 DAT_00ABCB20;
