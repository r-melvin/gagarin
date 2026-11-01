// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x628f80-0x629187 (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7EF818
extern const double DAT_007EF818;

// SYNTHETIC: GAMEMD 0x628F80
// GLOBAL: GAMEMD 0xAC4930
double DAT_00AC4930 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x628FF0
// GLOBAL: GAMEMD 0xAC4960
double DAT_00AC4960 = DAT_007E1720 * DAT_007EF818;
// SYNTHETIC: GAMEMD 0x629010
// GLOBAL: GAMEMD 0xAC4938
double DAT_00AC4938 = DAT_007E1728 * DAT_007EF818;
// SYNTHETIC: GAMEMD 0x629030
// GLOBAL: GAMEMD 0xAC48F8
double DAT_00AC48F8 = DAT_007E1730 * DAT_007EF818;
// SYNTHETIC: GAMEMD 0x629050
// GLOBAL: GAMEMD 0xAC4988
int DAT_00AC4988 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC48F8 - DAT_00AC4938) * DAT_00AC4930));
// SYNTHETIC: GAMEMD 0x629090
// GLOBAL: GAMEMD 0xAC4940
double DAT_00AC4940 = FUN_004CADE0((double)DAT_00AC4988 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x6290C0
// GLOBAL: GAMEMD 0xAC4958
double DAT_00AC4958 = FUN_004CADE0((double)(DAT_00AC4988 * 2) / DAT_00AC4930);
// SYNTHETIC: GAMEMD 0x6290F0
// GLOBAL: GAMEMD 0xAC497C
int DAT_00AC497C = (int)((double)(DAT_00AC4988 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x629120
// GLOBAL: GAMEMD 0xAC4928
MathTblShortPair DAT_00AC4928;
// SYNTHETIC: GAMEMD 0x629130
// GLOBAL: GAMEMD 0xAC4948
MathTblZero3 DAT_00AC4948;
// SYNTHETIC: GAMEMD 0x629150
// GLOBAL: GAMEMD 0xAC4970
MathTblCoord DAT_00AC4970;
// SYNTHETIC: GAMEMD 0x629170
// GLOBAL: GAMEMD 0xAC4900
MathTblZero4 DAT_00AC4900;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EF818
extern const double DAT_007EF818 = 0.017453292519943295;
// END defined globals
