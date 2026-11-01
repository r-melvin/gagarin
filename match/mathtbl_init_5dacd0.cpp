// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x5dacd0-0x5daeb2 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7EEF10
extern const double DAT_007EEF10;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x5DACD0
// GLOBAL: GAMEMD 0xAC01A8
MathTblZero4 DAT_00AC01A8;
// SYNTHETIC: GAMEMD 0x5DACF0
// GLOBAL: GAMEMD 0xAC01C0
double DAT_00AC01C0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5DAD60
// GLOBAL: GAMEMD 0xAC0210
double DAT_00AC0210 = DAT_007E1720 * DAT_007EEF10;
// SYNTHETIC: GAMEMD 0x5DAD80
// GLOBAL: GAMEMD 0xAC01C8
double DAT_00AC01C8 = DAT_007E1728 * DAT_007EEF10;
// SYNTHETIC: GAMEMD 0x5DADA0
// GLOBAL: GAMEMD 0xAC0198
double DAT_00AC0198 = DAT_007E1730 * DAT_007EEF10;
// SYNTHETIC: GAMEMD 0x5DADC0
// GLOBAL: GAMEMD 0xAC0258
int DAT_00AC0258 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC0198 - DAT_00AC01C8) * DAT_00AC01C0));
// SYNTHETIC: GAMEMD 0x5DAE00
// GLOBAL: GAMEMD 0xAC01D8
double DAT_00AC01D8 = FUN_004CADE0((double)DAT_00AC0258 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x5DAE30
// GLOBAL: GAMEMD 0xAC01F8
double DAT_00AC01F8 = FUN_004CADE0((double)(DAT_00AC0258 * 2) / DAT_00AC01C0);
// SYNTHETIC: GAMEMD 0x5DAE60
// GLOBAL: GAMEMD 0xAC024C
int DAT_00AC024C = (int)((double)(DAT_00AC0258 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x5DAE90
// GLOBAL: GAMEMD 0xAC01B8
MathTblShortPair DAT_00AC01B8;
// SYNTHETIC: GAMEMD 0x5DAEA0
// GLOBAL: GAMEMD 0xAC01E8
MathTblZero3 DAT_00AC01E8;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EEF10
extern const double DAT_007EEF10 = 0.017453292519943295;
// END defined globals
