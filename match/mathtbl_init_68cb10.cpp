// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x68cb10-0x68ccf2 (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7F0EA8
extern const double DAT_007F0EA8;

// SYNTHETIC: GAMEMD 0x68CB10
// GLOBAL: GAMEMD 0xB054F8
MathTblZero4 DAT_00B054F8;
// SYNTHETIC: GAMEMD 0x68CB30
// GLOBAL: GAMEMD 0xB05510
double DAT_00B05510 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x68CBA0
// GLOBAL: GAMEMD 0xB05550
double DAT_00B05550 = DAT_007E1720 * DAT_007F0EA8;
// SYNTHETIC: GAMEMD 0x68CBC0
// GLOBAL: GAMEMD 0xB05518
double DAT_00B05518 = DAT_007E1728 * DAT_007F0EA8;
// SYNTHETIC: GAMEMD 0x68CBE0
// GLOBAL: GAMEMD 0xB054E8
double DAT_00B054E8 = DAT_007E1730 * DAT_007F0EA8;
// SYNTHETIC: GAMEMD 0x68CC00
// GLOBAL: GAMEMD 0xB05580
int DAT_00B05580 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B054E8 - DAT_00B05518) * DAT_00B05510));
// SYNTHETIC: GAMEMD 0x68CC40
// GLOBAL: GAMEMD 0xB05520
double DAT_00B05520 = FUN_004CADE0((double)DAT_00B05580 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x68CC70
// GLOBAL: GAMEMD 0xB05548
double DAT_00B05548 = FUN_004CADE0((double)(DAT_00B05580 * 2) / DAT_00B05510);
// SYNTHETIC: GAMEMD 0x68CCA0
// GLOBAL: GAMEMD 0xB05574
int DAT_00B05574 = (int)((double)(DAT_00B05580 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x68CCD0
// GLOBAL: GAMEMD 0xB05508
MathTblShortPair DAT_00B05508;
// SYNTHETIC: GAMEMD 0x68CCE0
// GLOBAL: GAMEMD 0xB05538
MathTblZero3 DAT_00B05538;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F0EA8
extern const double DAT_007F0EA8 = 0.017453292519943295;
// END defined globals
