// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x554430-0x554620 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7ECF68
const double DAT_007ECF68 = 60.0;
// GLOBAL: GAMEMD 0x7ECF70
const double DAT_007ECF70 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x554430
// GLOBAL: GAMEMD 0xABC9E8
double DAT_00ABC9E8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x554460
// GLOBAL: GAMEMD 0xABCA68
double DAT_00ABCA68 = DAT_00ABC9E8 / DAT_007ECF68;
// SYNTHETIC: GAMEMD 0x554480
// GLOBAL: GAMEMD 0xABCA38
double DAT_00ABCA38 = 1.0 / DAT_00ABCA68;
// SYNTHETIC: GAMEMD 0x5544A0
// GLOBAL: GAMEMD 0xABCA30
double DAT_00ABCA30 = DAT_007ECF70 * 45.0;
// SYNTHETIC: GAMEMD 0x5544C0
// GLOBAL: GAMEMD 0xABC9F0
double DAT_00ABC9F0 = DAT_007ECF70 * 60.0;
// SYNTHETIC: GAMEMD 0x5544E0
// GLOBAL: GAMEMD 0xABC9C8
double DAT_00ABC9C8 = DAT_007ECF70 * 90.0;
// SYNTHETIC: GAMEMD 0x554500
// GLOBAL: GAMEMD 0xABCA70
int DAT_00ABCA70 = (int)(FUN_004CAD50(DAT_00ABC9C8 - DAT_00ABC9F0) * DAT_00ABC9E8 * 0.5);
// SYNTHETIC: GAMEMD 0x554540
// GLOBAL: GAMEMD 0xABC9F8
double DAT_00ABC9F8 = FUN_004CADE0(DAT_00ABCA70 * 0.00390625);
// SYNTHETIC: GAMEMD 0x554570
// GLOBAL: GAMEMD 0xABCA28
double DAT_00ABCA28 = FUN_004CADE0((DAT_00ABCA70 * 2) / DAT_00ABC9E8);
// SYNTHETIC: GAMEMD 0x5545A0
// GLOBAL: GAMEMD 0xABCA64
int DAT_00ABCA64 = (int)(DAT_00ABCA70 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5545D0
// GLOBAL: GAMEMD 0xABC9E0
HeaderCellInit DAT_00ABC9E0(0, 0);
// SYNTHETIC: GAMEMD 0x5545E0
// GLOBAL: GAMEMD 0xABCA00
HeaderCoordInit DAT_00ABCA00(0, 0, 0);
// SYNTHETIC: GAMEMD 0x554600
// GLOBAL: GAMEMD 0xABCA58
HeaderCoordInit DAT_00ABCA58(128, 128, 0);
// SYNTHETIC: GAMEMD 0x554620
// GLOBAL: GAMEMD 0xABC9D0
MathTblZero4 DAT_00ABC9D0;
