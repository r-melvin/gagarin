// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x65f7a0-0x65fa5f (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7F0988
extern const double DAT_007F0988;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x65F7A0
// GLOBAL: GAMEMD 0xB04D70
double DAT_00B04D70 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x65F810
// GLOBAL: GAMEMD 0xB04DC8
double DAT_00B04DC8 = DAT_007E1720 * DAT_007F0988;
// SYNTHETIC: GAMEMD 0x65F830
// GLOBAL: GAMEMD 0xB04D80
double DAT_00B04D80 = DAT_007E1728 * DAT_007F0988;
// SYNTHETIC: GAMEMD 0x65F850
// GLOBAL: GAMEMD 0xB04D30
double DAT_00B04D30 = DAT_007E1730 * DAT_007F0988;
// SYNTHETIC: GAMEMD 0x65F870
// GLOBAL: GAMEMD 0xB04DF8
int DAT_00B04DF8 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B04D30 - DAT_00B04D80) * DAT_00B04D70));
// SYNTHETIC: GAMEMD 0x65F8B0
// GLOBAL: GAMEMD 0xB04D90
double DAT_00B04D90 = FUN_004CADE0((double)DAT_00B04DF8 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x65F8E0
// GLOBAL: GAMEMD 0xB04DC0
double DAT_00B04DC0 = FUN_004CADE0((double)(DAT_00B04DF8 * 2) / DAT_00B04D70);
// SYNTHETIC: GAMEMD 0x65F910
// GLOBAL: GAMEMD 0xB04DEC
int DAT_00B04DEC = (int)((double)(DAT_00B04DF8 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x65F940
// GLOBAL: GAMEMD 0xB04D68
MathTblShortPair DAT_00B04D68;
// SYNTHETIC: GAMEMD 0x65F950
// GLOBAL: GAMEMD 0xB04D98
MathTblZero3 DAT_00B04D98;
// SYNTHETIC: GAMEMD 0x65F970
// GLOBAL: GAMEMD 0xB04DE0
MathTblCoord DAT_00B04DE0;
// SYNTHETIC: GAMEMD 0x65F990
// GLOBAL: GAMEMD 0xB04D38
MathTblZero4 DAT_00B04D38;
// SYNTHETIC: GAMEMD 0x65FA50
// GLOBAL: GAMEMD 0xB04D78
MathTblShortPair DAT_00B04D78;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F0988
extern const double DAT_007F0988 = 0.017453292519943295;
// END defined globals
