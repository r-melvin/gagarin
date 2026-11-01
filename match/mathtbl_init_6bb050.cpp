// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6bb050-0x6bb232 (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7F3708
extern const double DAT_007F3708;

// SYNTHETIC: GAMEMD 0x6BB050
// GLOBAL: GAMEMD 0xB0BC58
MathTblZero4 DAT_00B0BC58;
// SYNTHETIC: GAMEMD 0x6BB070
// GLOBAL: GAMEMD 0xB0BC70
double DAT_00B0BC70 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6BB0E0
// GLOBAL: GAMEMD 0xB0BCB8
double DAT_00B0BCB8 = DAT_007E1720 * DAT_007F3708;
// SYNTHETIC: GAMEMD 0x6BB100
// GLOBAL: GAMEMD 0xB0BC78
double DAT_00B0BC78 = DAT_007E1728 * DAT_007F3708;
// SYNTHETIC: GAMEMD 0x6BB120
// GLOBAL: GAMEMD 0xB0BC50
double DAT_00B0BC50 = DAT_007E1730 * DAT_007F3708;
// SYNTHETIC: GAMEMD 0x6BB140
// GLOBAL: GAMEMD 0xB0BCE0
int DAT_00B0BCE0 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B0BC50 - DAT_00B0BC78) * DAT_00B0BC70));
// SYNTHETIC: GAMEMD 0x6BB180
// GLOBAL: GAMEMD 0xB0BC80
double DAT_00B0BC80 = FUN_004CADE0((double)DAT_00B0BCE0 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x6BB1B0
// GLOBAL: GAMEMD 0xB0BCB0
double DAT_00B0BCB0 = FUN_004CADE0((double)(DAT_00B0BCE0 * 2) / DAT_00B0BC70);
// SYNTHETIC: GAMEMD 0x6BB1E0
// GLOBAL: GAMEMD 0xB0BCD4
int DAT_00B0BCD4 = (int)((double)(DAT_00B0BCE0 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x6BB210
// GLOBAL: GAMEMD 0xB0BC68
MathTblShortPair DAT_00B0BC68;
// SYNTHETIC: GAMEMD 0x6BB220
// GLOBAL: GAMEMD 0xB0BCA0
MathTblZero3 DAT_00B0BCA0;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F3708
extern const double DAT_007F3708 = 0.017453292519943295;
// END defined globals
