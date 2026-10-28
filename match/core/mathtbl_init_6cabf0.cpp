// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6cabf0-0x6cadd2 (disassembled from the user's gamemd.exe v1.001).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
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
// GLOBAL: GAMEMD 0x7F3FB0
extern const double DAT_007F3FB0;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x6CABF0
// GLOBAL: GAMEMD 0xB0BFF0
MathTblZero4 DAT_00B0BFF0;
// SYNTHETIC: GAMEMD 0x6CAC10
// GLOBAL: GAMEMD 0xB0C008
double DAT_00B0C008 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6CAC80
// GLOBAL: GAMEMD 0xB0C060
double DAT_00B0C060 = DAT_007E1720 * DAT_007F3FB0;
// SYNTHETIC: GAMEMD 0x6CACA0
// GLOBAL: GAMEMD 0xB0C010
double DAT_00B0C010 = DAT_007E1728 * DAT_007F3FB0;
// SYNTHETIC: GAMEMD 0x6CACC0
// GLOBAL: GAMEMD 0xB0BFE8
double DAT_00B0BFE8 = DAT_007E1730 * DAT_007F3FB0;
// SYNTHETIC: GAMEMD 0x6CACE0
// GLOBAL: GAMEMD 0xB0C088
int DAT_00B0C088 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B0BFE8 - DAT_00B0C010) * DAT_00B0C008));
// SYNTHETIC: GAMEMD 0x6CAD20
// GLOBAL: GAMEMD 0xB0C018
double DAT_00B0C018 = FUN_004CADE0((double)DAT_00B0C088 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x6CAD50
// GLOBAL: GAMEMD 0xB0C030
double DAT_00B0C030 = FUN_004CADE0((double)(DAT_00B0C088 * 2) / DAT_00B0C008);
// SYNTHETIC: GAMEMD 0x6CAD80
// GLOBAL: GAMEMD 0xB0C07C
int DAT_00B0C07C = (int)((double)(DAT_00B0C088 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x6CADB0
// GLOBAL: GAMEMD 0xB0C000
MathTblShortPair DAT_00B0C000;
// SYNTHETIC: GAMEMD 0x6CADC0
// GLOBAL: GAMEMD 0xB0C020
MathTblZero3 DAT_00B0C020;
