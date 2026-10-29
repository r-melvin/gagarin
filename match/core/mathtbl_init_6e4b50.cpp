// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6e4b50-0x6e4d57 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7F44A8
extern const double DAT_007F44A8;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x6E4B50
// GLOBAL: GAMEMD 0xB0E708
double DAT_00B0E708 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6E4BC0
// GLOBAL: GAMEMD 0xB0E750
double DAT_00B0E750 = DAT_007E1720 * DAT_007F44A8;
// SYNTHETIC: GAMEMD 0x6E4BE0
// GLOBAL: GAMEMD 0xB0E710
double DAT_00B0E710 = DAT_007E1728 * DAT_007F44A8;
// SYNTHETIC: GAMEMD 0x6E4C00
// GLOBAL: GAMEMD 0xB0E6E8
double DAT_00B0E6E8 = DAT_007E1730 * DAT_007F44A8;
// SYNTHETIC: GAMEMD 0x6E4C20
// GLOBAL: GAMEMD 0xB0E778
int DAT_00B0E778 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B0E6E8 - DAT_00B0E710) * DAT_00B0E708));
// SYNTHETIC: GAMEMD 0x6E4C60
// GLOBAL: GAMEMD 0xB0E718
double DAT_00B0E718 = FUN_004CADE0((double)DAT_00B0E778 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x6E4C90
// GLOBAL: GAMEMD 0xB0E748
double DAT_00B0E748 = FUN_004CADE0((double)(DAT_00B0E778 * 2) / DAT_00B0E708);
// SYNTHETIC: GAMEMD 0x6E4CC0
// GLOBAL: GAMEMD 0xB0E76C
int DAT_00B0E76C = (int)((double)(DAT_00B0E778 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x6E4CF0
// GLOBAL: GAMEMD 0xB0E700
MathTblShortPair DAT_00B0E700;
// SYNTHETIC: GAMEMD 0x6E4D00
// GLOBAL: GAMEMD 0xB0E738
MathTblZero3 DAT_00B0E738;
// SYNTHETIC: GAMEMD 0x6E4D40
// GLOBAL: GAMEMD 0xB0E6F0
MathTblZero4 DAT_00B0E6F0;
