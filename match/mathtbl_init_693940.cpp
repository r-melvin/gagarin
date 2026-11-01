// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x693940-0x693b22 (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7F1178
extern const double DAT_007F1178;

// SYNTHETIC: GAMEMD 0x693940
// GLOBAL: GAMEMD 0xB056D0
MathTblZero4 DAT_00B056D0;
// SYNTHETIC: GAMEMD 0x693960
// GLOBAL: GAMEMD 0xB056E8
double DAT_00B056E8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6939D0
// GLOBAL: GAMEMD 0xB05718
double DAT_00B05718 = DAT_007E1720 * DAT_007F1178;
// SYNTHETIC: GAMEMD 0x6939F0
// GLOBAL: GAMEMD 0xB056F0
double DAT_00B056F0 = DAT_007E1728 * DAT_007F1178;
// SYNTHETIC: GAMEMD 0x693A10
// GLOBAL: GAMEMD 0xB056C8
double DAT_00B056C8 = DAT_007E1730 * DAT_007F1178;
// SYNTHETIC: GAMEMD 0x693A30
// GLOBAL: GAMEMD 0xB05740
int DAT_00B05740 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B056C8 - DAT_00B056F0) * DAT_00B056E8));
// SYNTHETIC: GAMEMD 0x693A70
// GLOBAL: GAMEMD 0xB056F8
double DAT_00B056F8 = FUN_004CADE0((double)DAT_00B05740 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x693AA0
// GLOBAL: GAMEMD 0xB05710
double DAT_00B05710 = FUN_004CADE0((double)(DAT_00B05740 * 2) / DAT_00B056E8);
// SYNTHETIC: GAMEMD 0x693AD0
// GLOBAL: GAMEMD 0xB05734
int DAT_00B05734 = (int)((double)(DAT_00B05740 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x693B00
// GLOBAL: GAMEMD 0xB056E0
MathTblShortPair DAT_00B056E0;
// SYNTHETIC: GAMEMD 0x693B10
// GLOBAL: GAMEMD 0xB05700
MathTblZero3 DAT_00B05700;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F1178
extern const double DAT_007F1178 = 0.017453292519943295;
// END defined globals
