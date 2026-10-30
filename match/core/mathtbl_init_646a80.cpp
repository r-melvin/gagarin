// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x646a80-0x646c87 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7F0298
extern const double DAT_007F0298;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x646A80
// GLOBAL: GAMEMD 0xAC6650
double DAT_00AC6650 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x646AF0
// GLOBAL: GAMEMD 0xAFA408
double DAT_00AFA408 = DAT_007E1720 * DAT_007F0298;
// SYNTHETIC: GAMEMD 0x646B10
// GLOBAL: GAMEMD 0xAFA260
double DAT_00AFA260 = DAT_007E1728 * DAT_007F0298;
// SYNTHETIC: GAMEMD 0x646B30
// GLOBAL: GAMEMD 0xAC5208
double DAT_00AC5208 = DAT_007E1730 * DAT_007F0298;
// SYNTHETIC: GAMEMD 0x646B50
// GLOBAL: GAMEMD 0xB0446C
int DAT_00B0446C = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC5208 - DAT_00AFA260) * DAT_00AC6650));
// SYNTHETIC: GAMEMD 0x646B90
// GLOBAL: GAMEMD 0xAFA270
double DAT_00AFA270 = FUN_004CADE0((double)DAT_00B0446C * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x646BC0
// GLOBAL: GAMEMD 0xAFA330
double DAT_00AFA330 = FUN_004CADE0((double)(DAT_00B0446C * 2) / DAT_00AC6650);
// SYNTHETIC: GAMEMD 0x646BF0
// GLOBAL: GAMEMD 0xAFA45C
int DAT_00AFA45C = (int)((double)(DAT_00B0446C * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x646C20
// GLOBAL: GAMEMD 0xAC6640
MathTblShortPair DAT_00AC6640;
// SYNTHETIC: GAMEMD 0x646C30
// GLOBAL: GAMEMD 0xAFA320
MathTblZero3 DAT_00AFA320;
// SYNTHETIC: GAMEMD 0x646C70
// GLOBAL: GAMEMD 0xAC6630
MathTblZero4 DAT_00AC6630;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F0298
extern const double DAT_007F0298 = 0.017453292519943295;
// END defined globals
