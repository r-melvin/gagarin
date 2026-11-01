// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x5ef2d0-0x5ef4b2 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7EEFC0
extern const double DAT_007EEFC0;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x5EF2D0
// GLOBAL: GAMEMD 0xAC11D8
MathTblZero4 DAT_00AC11D8;
// SYNTHETIC: GAMEMD 0x5EF2F0
// GLOBAL: GAMEMD 0xAC1210
double DAT_00AC1210 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5EF360
// GLOBAL: GAMEMD 0xAC1240
double DAT_00AC1240 = DAT_007E1720 * DAT_007EEFC0;
// SYNTHETIC: GAMEMD 0x5EF380
// GLOBAL: GAMEMD 0xAC1218
double DAT_00AC1218 = DAT_007E1728 * DAT_007EEFC0;
// SYNTHETIC: GAMEMD 0x5EF3A0
// GLOBAL: GAMEMD 0xAC11D0
double DAT_00AC11D0 = DAT_007E1730 * DAT_007EEFC0;
// SYNTHETIC: GAMEMD 0x5EF3C0
// GLOBAL: GAMEMD 0xAC1268
int DAT_00AC1268 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC11D0 - DAT_00AC1218) * DAT_00AC1210));
// SYNTHETIC: GAMEMD 0x5EF400
// GLOBAL: GAMEMD 0xAC1220
double DAT_00AC1220 = FUN_004CADE0((double)DAT_00AC1268 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x5EF430
// GLOBAL: GAMEMD 0xAC1238
double DAT_00AC1238 = FUN_004CADE0((double)(DAT_00AC1268 * 2) / DAT_00AC1210);
// SYNTHETIC: GAMEMD 0x5EF460
// GLOBAL: GAMEMD 0xAC125C
int DAT_00AC125C = (int)((double)(DAT_00AC1268 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x5EF490
// GLOBAL: GAMEMD 0xAC120C
MathTblShortPair DAT_00AC120C;
// SYNTHETIC: GAMEMD 0x5EF4A0
// GLOBAL: GAMEMD 0xAC1228
MathTblZero3 DAT_00AC1228;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EEFC0
extern const double DAT_007EEFC0 = 0.017453292519943295;
// END defined globals
