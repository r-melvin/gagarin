// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5CAC00-0x5CADF0 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
#include "header_init_shapes.h"
#include "header_tuning_globals.h"
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
// GLOBAL: GAMEMD 0x7EE7D0
extern const double DAT_007EE7D0;
// GLOBAL: GAMEMD 0x7EE7D8
const double DAT_007EE7D8 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5CAC00
// GLOBAL: GAMEMD 0xABFA88
MathTblZero4 DAT_00ABFA88;
// SYNTHETIC: GAMEMD 0x5CAC20
// GLOBAL: GAMEMD 0xABFAA0
double DAT_00ABFAA0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5CAC50
// GLOBAL: GAMEMD 0xABFAF0
double DAT_00ABFAF0 = DAT_00ABFAA0 / DAT_007EE7D0;
// SYNTHETIC: GAMEMD 0x5CAC70
// GLOBAL: GAMEMD 0xABFAD8
double DAT_00ABFAD8 = 1.0 / DAT_00ABFAF0;
// SYNTHETIC: GAMEMD 0x5CAC90
// GLOBAL: GAMEMD 0xABFAD0
double DAT_00ABFAD0 = DAT_007EE7D8 * 45.0;
// SYNTHETIC: GAMEMD 0x5CACB0
// GLOBAL: GAMEMD 0xABFAA8
double DAT_00ABFAA8 = DAT_007EE7D8 * 60.0;
// SYNTHETIC: GAMEMD 0x5CACD0
// GLOBAL: GAMEMD 0xABFA80
double DAT_00ABFA80 = DAT_007EE7D8 * 90.0;
// SYNTHETIC: GAMEMD 0x5CACF0
// GLOBAL: GAMEMD 0xABFAF8
int DAT_00ABFAF8 = (int)(FUN_004CAD50(DAT_00ABFA80 - DAT_00ABFAA8) * DAT_00ABFAA0 * 0.5);
// SYNTHETIC: GAMEMD 0x5CAD30
// GLOBAL: GAMEMD 0xABFAB0
double DAT_00ABFAB0 = FUN_004CADE0(DAT_00ABFAF8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5CAD60
// GLOBAL: GAMEMD 0xABFAC8
double DAT_00ABFAC8 = FUN_004CADE0((DAT_00ABFAF8 * 2) / DAT_00ABFAA0);
// SYNTHETIC: GAMEMD 0x5CAD90
// GLOBAL: GAMEMD 0xABFAEC
int DAT_00ABFAEC = (int)(DAT_00ABFAF8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5CADC0
// GLOBAL: GAMEMD 0xABFA98
HeaderCellInit DAT_00ABFA98(0, 0);
// SYNTHETIC: GAMEMD 0x5CADD0
// GLOBAL: GAMEMD 0xABFAB8
HeaderCoordInit DAT_00ABFAB8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5CADF0
// GLOBAL: GAMEMD 0xABFAE0
TuningCoordInit DAT_00ABFAE0(128, 128, 0);
