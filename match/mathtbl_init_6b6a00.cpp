// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6b6a00-0x6b6c07 (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7F35D8
extern const double DAT_007F35D8;

// SYNTHETIC: GAMEMD 0x6B6A00
// GLOBAL: GAMEMD 0xB0B828
double DAT_00B0B828 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6B6A70
// GLOBAL: GAMEMD 0xB0B858
double DAT_00B0B858 = DAT_007E1720 * DAT_007F35D8;
// SYNTHETIC: GAMEMD 0x6B6A90
// GLOBAL: GAMEMD 0xB0B830
double DAT_00B0B830 = DAT_007E1728 * DAT_007F35D8;
// SYNTHETIC: GAMEMD 0x6B6AB0
// GLOBAL: GAMEMD 0xB0B808
double DAT_00B0B808 = DAT_007E1730 * DAT_007F35D8;
// SYNTHETIC: GAMEMD 0x6B6AD0
// GLOBAL: GAMEMD 0xB0B898
int DAT_00B0B898 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B0B808 - DAT_00B0B830) * DAT_00B0B828));
// SYNTHETIC: GAMEMD 0x6B6B10
// GLOBAL: GAMEMD 0xB0B838
double DAT_00B0B838 = FUN_004CADE0((double)DAT_00B0B898 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x6B6B40
// GLOBAL: GAMEMD 0xB0B850
double DAT_00B0B850 = FUN_004CADE0((double)(DAT_00B0B898 * 2) / DAT_00B0B828);
// SYNTHETIC: GAMEMD 0x6B6B70
// GLOBAL: GAMEMD 0xB0B874
int DAT_00B0B874 = (int)((double)(DAT_00B0B898 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x6B6BA0
// GLOBAL: GAMEMD 0xB0B820
MathTblShortPair DAT_00B0B820;
// SYNTHETIC: GAMEMD 0x6B6BB0
// GLOBAL: GAMEMD 0xB0B840
MathTblZero3 DAT_00B0B840;
// SYNTHETIC: GAMEMD 0x6B6BD0
// GLOBAL: GAMEMD 0xB0B868
MathTblCoord DAT_00B0B868;
// SYNTHETIC: GAMEMD 0x6B6BF0
// GLOBAL: GAMEMD 0xB0B810
MathTblZero4 DAT_00B0B810;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F35D8
extern const double DAT_007F35D8 = 0.017453292519943295;
// END defined globals
