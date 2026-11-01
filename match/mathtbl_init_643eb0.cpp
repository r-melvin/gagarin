// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x643eb0-0x64409a (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7F0070
extern const double DAT_007F0070;

// SYNTHETIC: GAMEMD 0x643EB0
// GLOBAL: GAMEMD 0xAC5028
double DAT_00AC5028 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x643F20
// GLOBAL: GAMEMD 0xAC5058
double DAT_00AC5058 = DAT_007E1720 * DAT_007F0070;
// SYNTHETIC: GAMEMD 0x643F40
// GLOBAL: GAMEMD 0xAC5030
double DAT_00AC5030 = DAT_007E1728 * DAT_007F0070;
// SYNTHETIC: GAMEMD 0x643F60
// GLOBAL: GAMEMD 0xAC5018
double DAT_00AC5018 = DAT_007E1730 * DAT_007F0070;
// SYNTHETIC: GAMEMD 0x643F80
// GLOBAL: GAMEMD 0xAC5080
int DAT_00AC5080 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC5018 - DAT_00AC5030) * DAT_00AC5028));
// SYNTHETIC: GAMEMD 0x643FC0
// GLOBAL: GAMEMD 0xAC5038
double DAT_00AC5038 = FUN_004CADE0((double)DAT_00AC5080 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x643FF0
// GLOBAL: GAMEMD 0xAC5050
double DAT_00AC5050 = FUN_004CADE0((double)(DAT_00AC5080 * 2) / DAT_00AC5028);
// SYNTHETIC: GAMEMD 0x644020
// GLOBAL: GAMEMD 0xAC5074
int DAT_00AC5074 = (int)((double)(DAT_00AC5080 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x644050
// GLOBAL: GAMEMD 0xAC5020
MathTblShortPair DAT_00AC5020;
// SYNTHETIC: GAMEMD 0x644060
// GLOBAL: GAMEMD 0xAC5040
MathTblZero3 DAT_00AC5040;
// SYNTHETIC: GAMEMD 0x644080
// GLOBAL: GAMEMD 0xAC5068
MathTblCoord DAT_00AC5068;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F0070
extern const double DAT_007F0070 = 0.017453292519943295;
// END defined globals
