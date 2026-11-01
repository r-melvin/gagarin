// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x65f310-0x65f4f2 (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7F0978
extern const double DAT_007F0978;

// SYNTHETIC: GAMEMD 0x65F310
// GLOBAL: GAMEMD 0xB04CB0
MathTblZero4 DAT_00B04CB0;
// SYNTHETIC: GAMEMD 0x65F330
// GLOBAL: GAMEMD 0xB04CC8
double DAT_00B04CC8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x65F3A0
// GLOBAL: GAMEMD 0xB04CF8
double DAT_00B04CF8 = DAT_007E1720 * DAT_007F0978;
// SYNTHETIC: GAMEMD 0x65F3C0
// GLOBAL: GAMEMD 0xB04CD0
double DAT_00B04CD0 = DAT_007E1728 * DAT_007F0978;
// SYNTHETIC: GAMEMD 0x65F3E0
// GLOBAL: GAMEMD 0xB04CA8
double DAT_00B04CA8 = DAT_007E1730 * DAT_007F0978;
// SYNTHETIC: GAMEMD 0x65F400
// GLOBAL: GAMEMD 0xB04D20
int DAT_00B04D20 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B04CA8 - DAT_00B04CD0) * DAT_00B04CC8));
// SYNTHETIC: GAMEMD 0x65F440
// GLOBAL: GAMEMD 0xB04CD8
double DAT_00B04CD8 = FUN_004CADE0((double)DAT_00B04D20 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x65F470
// GLOBAL: GAMEMD 0xB04CF0
double DAT_00B04CF0 = FUN_004CADE0((double)(DAT_00B04D20 * 2) / DAT_00B04CC8);
// SYNTHETIC: GAMEMD 0x65F4A0
// GLOBAL: GAMEMD 0xB04D14
int DAT_00B04D14 = (int)((double)(DAT_00B04D20 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x65F4D0
// GLOBAL: GAMEMD 0xB04CC0
MathTblShortPair DAT_00B04CC0;
// SYNTHETIC: GAMEMD 0x65F4E0
// GLOBAL: GAMEMD 0xB04CE0
MathTblZero3 DAT_00B04CE0;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F0978
extern const double DAT_007F0978 = 0.017453292519943295;
// END defined globals
