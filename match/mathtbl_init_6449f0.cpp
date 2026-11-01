// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6449f0-0x644bda (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7F0150
extern const double DAT_007F0150;

// SYNTHETIC: GAMEMD 0x6449F0
// GLOBAL: GAMEMD 0xAC5098
double DAT_00AC5098 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x644A60
// GLOBAL: GAMEMD 0xAC50C8
double DAT_00AC50C8 = DAT_007E1720 * DAT_007F0150;
// SYNTHETIC: GAMEMD 0x644A80
// GLOBAL: GAMEMD 0xAC50A0
double DAT_00AC50A0 = DAT_007E1728 * DAT_007F0150;
// SYNTHETIC: GAMEMD 0x644AA0
// GLOBAL: GAMEMD 0xAC5088
double DAT_00AC5088 = DAT_007E1730 * DAT_007F0150;
// SYNTHETIC: GAMEMD 0x644AC0
// GLOBAL: GAMEMD 0xAC50F0
int DAT_00AC50F0 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC5088 - DAT_00AC50A0) * DAT_00AC5098));
// SYNTHETIC: GAMEMD 0x644B00
// GLOBAL: GAMEMD 0xAC50A8
double DAT_00AC50A8 = FUN_004CADE0((double)DAT_00AC50F0 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x644B30
// GLOBAL: GAMEMD 0xAC50C0
double DAT_00AC50C0 = FUN_004CADE0((double)(DAT_00AC50F0 * 2) / DAT_00AC5098);
// SYNTHETIC: GAMEMD 0x644B60
// GLOBAL: GAMEMD 0xAC50E4
int DAT_00AC50E4 = (int)((double)(DAT_00AC50F0 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x644B90
// GLOBAL: GAMEMD 0xAC5090
MathTblShortPair DAT_00AC5090;
// SYNTHETIC: GAMEMD 0x644BA0
// GLOBAL: GAMEMD 0xAC50B0
MathTblZero3 DAT_00AC50B0;
// SYNTHETIC: GAMEMD 0x644BC0
// GLOBAL: GAMEMD 0xAC50D8
MathTblCoord DAT_00AC50D8;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F0150
extern const double DAT_007F0150 = 0.017453292519943295;
// END defined globals
