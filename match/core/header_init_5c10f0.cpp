// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5C10F0-0x5C12E0 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7EE268
extern const double DAT_007EE268;
// GLOBAL: GAMEMD 0x7EE270
const double DAT_007EE270 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5C10F0
// GLOBAL: GAMEMD 0xABF420
double DAT_00ABF420 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5C1120
// GLOBAL: GAMEMD 0xABF490
double DAT_00ABF490 = DAT_00ABF420 / DAT_007EE268;
// SYNTHETIC: GAMEMD 0x5C1140
// GLOBAL: GAMEMD 0xABF458
double DAT_00ABF458 = 1.0 / DAT_00ABF490;
// SYNTHETIC: GAMEMD 0x5C1160
// GLOBAL: GAMEMD 0xABF450
double DAT_00ABF450 = DAT_007EE270 * 45.0;
// SYNTHETIC: GAMEMD 0x5C1180
// GLOBAL: GAMEMD 0xABF428
double DAT_00ABF428 = DAT_007EE270 * 60.0;
// SYNTHETIC: GAMEMD 0x5C11A0
// GLOBAL: GAMEMD 0xABF400
double DAT_00ABF400 = DAT_007EE270 * 90.0;
// SYNTHETIC: GAMEMD 0x5C11C0
// GLOBAL: GAMEMD 0xABF498
int DAT_00ABF498 = (int)(FUN_004CAD50(DAT_00ABF400 - DAT_00ABF428) * DAT_00ABF420 * 0.5);
// SYNTHETIC: GAMEMD 0x5C1200
// GLOBAL: GAMEMD 0xABF430
double DAT_00ABF430 = FUN_004CADE0(DAT_00ABF498 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5C1230
// GLOBAL: GAMEMD 0xABF448
double DAT_00ABF448 = FUN_004CADE0((DAT_00ABF498 * 2) / DAT_00ABF420);
// SYNTHETIC: GAMEMD 0x5C1260
// GLOBAL: GAMEMD 0xABF48C
int DAT_00ABF48C = (int)(DAT_00ABF498 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5C1290
// GLOBAL: GAMEMD 0xABF418
HeaderCellInit DAT_00ABF418(0, 0);
// SYNTHETIC: GAMEMD 0x5C12A0
// GLOBAL: GAMEMD 0xABF438
HeaderCoordInit DAT_00ABF438(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5C12C0
// GLOBAL: GAMEMD 0xABF480
HeaderCoordInit DAT_00ABF480(128, 128, 0);
// SYNTHETIC: GAMEMD 0x5C12E0
// GLOBAL: GAMEMD 0xABF408
MathTblZero4 DAT_00ABF408;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EE268
extern const double DAT_007EE268 = 60.0;
// END defined globals
