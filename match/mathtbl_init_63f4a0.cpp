// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x63f4a0-0x63f682 (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "mathtbl_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7E1720
extern const double DAT_007E1720;
// GLOBAL: GAMEMD 0x7E1728
extern const double DAT_007E1728;
// GLOBAL: GAMEMD 0x7E1730
extern const double DAT_007E1730;
// GLOBAL: GAMEMD 0x7E1738
extern const double DAT_007E1738;
// GLOBAL: GAMEMD 0x7E1740
extern const double DAT_007E1740;
// GLOBAL: GAMEMD 0x7EFF48
extern const double DAT_007EFF48;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x63F4A0
// GLOBAL: GAMEMD 0xAC4D00
MathTblZero4 DAT_00AC4D00;
// SYNTHETIC: GAMEMD 0x63F4C0
// GLOBAL: GAMEMD 0xAC4D18
double DAT_00AC4D18 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x63F530
// GLOBAL: GAMEMD 0xAC4E48
double DAT_00AC4E48 = DAT_007E1720 * DAT_007EFF48;
// SYNTHETIC: GAMEMD 0x63F550
// GLOBAL: GAMEMD 0xAC4D20
double DAT_00AC4D20 = DAT_007E1728 * DAT_007EFF48;
// SYNTHETIC: GAMEMD 0x63F570
// GLOBAL: GAMEMD 0xAC4CF8
double DAT_00AC4CF8 = DAT_007E1730 * DAT_007EFF48;
// SYNTHETIC: GAMEMD 0x63F590
// GLOBAL: GAMEMD 0xAC4E70
int DAT_00AC4E70 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC4CF8 - DAT_00AC4D20) * DAT_00AC4D18));
// SYNTHETIC: GAMEMD 0x63F5D0
// GLOBAL: GAMEMD 0xAC4D28
double DAT_00AC4D28 = FUN_004CADE0((double)DAT_00AC4E70 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x63F600
// GLOBAL: GAMEMD 0xAC4E40
double DAT_00AC4E40 = FUN_004CADE0((double)(DAT_00AC4E70 * 2) / DAT_00AC4D18);
// SYNTHETIC: GAMEMD 0x63F630
// GLOBAL: GAMEMD 0xAC4E64
int DAT_00AC4E64 = (int)((double)(DAT_00AC4E70 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x63F660
// GLOBAL: GAMEMD 0xAC4D10
MathTblShortPair DAT_00AC4D10;
// SYNTHETIC: GAMEMD 0x63F670
// GLOBAL: GAMEMD 0xAC4E30
MathTblZero3 DAT_00AC4E30;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EFF48
extern const double DAT_007EFF48 = 0.017453292519943295;
// END defined globals
