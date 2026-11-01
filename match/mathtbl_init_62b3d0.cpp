// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x62b3d0-0x62b5d7 (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7EF908
extern const double DAT_007EF908;

// SYNTHETIC: GAMEMD 0x62B3D0
// GLOBAL: GAMEMD 0xAC49B8
double DAT_00AC49B8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x62B440
// GLOBAL: GAMEMD 0xAC49F0
double DAT_00AC49F0 = DAT_007E1720 * DAT_007EF908;
// SYNTHETIC: GAMEMD 0x62B460
// GLOBAL: GAMEMD 0xAC49C0
double DAT_00AC49C0 = DAT_007E1728 * DAT_007EF908;
// SYNTHETIC: GAMEMD 0x62B480
// GLOBAL: GAMEMD 0xAC4990
double DAT_00AC4990 = DAT_007E1730 * DAT_007EF908;
// SYNTHETIC: GAMEMD 0x62B4A0
// GLOBAL: GAMEMD 0xAC4A18
int DAT_00AC4A18 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC4990 - DAT_00AC49C0) * DAT_00AC49B8));
// SYNTHETIC: GAMEMD 0x62B4E0
// GLOBAL: GAMEMD 0xAC49C8
double DAT_00AC49C8 = FUN_004CADE0((double)DAT_00AC4A18 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x62B510
// GLOBAL: GAMEMD 0xAC49E8
double DAT_00AC49E8 = FUN_004CADE0((double)(DAT_00AC4A18 * 2) / DAT_00AC49B8);
// SYNTHETIC: GAMEMD 0x62B540
// GLOBAL: GAMEMD 0xAC4A0C
int DAT_00AC4A0C = (int)((double)(DAT_00AC4A18 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x62B570
// GLOBAL: GAMEMD 0xAC49B0
MathTblShortPair DAT_00AC49B0;
// SYNTHETIC: GAMEMD 0x62B580
// GLOBAL: GAMEMD 0xAC49D8
MathTblZero3 DAT_00AC49D8;
// SYNTHETIC: GAMEMD 0x62B5A0
// GLOBAL: GAMEMD 0xAC4A00
MathTblCoord DAT_00AC4A00;
// SYNTHETIC: GAMEMD 0x62B5C0
// GLOBAL: GAMEMD 0xAC49A0
MathTblZero4 DAT_00AC49A0;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EF908
extern const double DAT_007EF908 = 0.017453292519943295;
// END defined globals
