// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x652660-0x652842 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7F02B0
extern const double DAT_007F02B0;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x652660
// GLOBAL: GAMEMD 0xB048B0
MathTblZero4 DAT_00B048B0;
// SYNTHETIC: GAMEMD 0x652680
// GLOBAL: GAMEMD 0xB048D8
double DAT_00B048D8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6526F0
// GLOBAL: GAMEMD 0xB049D8
double DAT_00B049D8 = DAT_007E1720 * DAT_007F02B0;
// SYNTHETIC: GAMEMD 0x652710
// GLOBAL: GAMEMD 0xB048E8
double DAT_00B048E8 = DAT_007E1728 * DAT_007F02B0;
// SYNTHETIC: GAMEMD 0x652730
// GLOBAL: GAMEMD 0xB048A0
double DAT_00B048A0 = DAT_007E1730 * DAT_007F02B0;
// SYNTHETIC: GAMEMD 0x652750
// GLOBAL: GAMEMD 0xB04A34
int DAT_00B04A34 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B048A0 - DAT_00B048E8) * DAT_00B048D8));
// SYNTHETIC: GAMEMD 0x652790
// GLOBAL: GAMEMD 0xB048F0
double DAT_00B048F0 = FUN_004CADE0((double)DAT_00B04A34 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x6527C0
// GLOBAL: GAMEMD 0xB04970
double DAT_00B04970 = FUN_004CADE0((double)(DAT_00B04A34 * 2) / DAT_00B048D8);
// SYNTHETIC: GAMEMD 0x6527F0
// GLOBAL: GAMEMD 0xB049F4
int DAT_00B049F4 = (int)((double)(DAT_00B04A34 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x652820
// GLOBAL: GAMEMD 0xB048C0
MathTblShortPair DAT_00B048C0;
// SYNTHETIC: GAMEMD 0x652830
// GLOBAL: GAMEMD 0xB04900
MathTblZero3 DAT_00B04900;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F02B0
extern const double DAT_007F02B0 = 0.017453292519943295;
// END defined globals
