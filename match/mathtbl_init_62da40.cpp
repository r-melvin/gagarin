// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x62da40-0x62dc47 (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7EFB60
extern const double DAT_007EFB60;

// SYNTHETIC: GAMEMD 0x62DA40
// GLOBAL: GAMEMD 0xAC4A40
double DAT_00AC4A40 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x62DAB0
// GLOBAL: GAMEMD 0xAC4A70
double DAT_00AC4A70 = DAT_007E1720 * DAT_007EFB60;
// SYNTHETIC: GAMEMD 0x62DAD0
// GLOBAL: GAMEMD 0xAC4A48
double DAT_00AC4A48 = DAT_007E1728 * DAT_007EFB60;
// SYNTHETIC: GAMEMD 0x62DAF0
// GLOBAL: GAMEMD 0xAC4A20
double DAT_00AC4A20 = DAT_007E1730 * DAT_007EFB60;
// SYNTHETIC: GAMEMD 0x62DB10
// GLOBAL: GAMEMD 0xAC4A98
int DAT_00AC4A98 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC4A20 - DAT_00AC4A48) * DAT_00AC4A40));
// SYNTHETIC: GAMEMD 0x62DB50
// GLOBAL: GAMEMD 0xAC4A50
double DAT_00AC4A50 = FUN_004CADE0((double)DAT_00AC4A98 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x62DB80
// GLOBAL: GAMEMD 0xAC4A68
double DAT_00AC4A68 = FUN_004CADE0((double)(DAT_00AC4A98 * 2) / DAT_00AC4A40);
// SYNTHETIC: GAMEMD 0x62DBB0
// GLOBAL: GAMEMD 0xAC4A8C
int DAT_00AC4A8C = (int)((double)(DAT_00AC4A98 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x62DBE0
// GLOBAL: GAMEMD 0xAC4A38
MathTblShortPair DAT_00AC4A38;
// SYNTHETIC: GAMEMD 0x62DBF0
// GLOBAL: GAMEMD 0xAC4A58
MathTblZero3 DAT_00AC4A58;
// SYNTHETIC: GAMEMD 0x62DC10
// GLOBAL: GAMEMD 0xAC4A80
MathTblCoord DAT_00AC4A80;
// SYNTHETIC: GAMEMD 0x62DC30
// GLOBAL: GAMEMD 0xAC4A28
MathTblZero4 DAT_00AC4A28;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EFB60
extern const double DAT_007EFB60 = 0.017453292519943295;
// END defined globals
