// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6e8880-0x6e8a87 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7F46F8
extern const double DAT_007F46F8;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x6E8880
// GLOBAL: GAMEMD 0xB0E950
double DAT_00B0E950 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6E88F0
// GLOBAL: GAMEMD 0xB0E980
double DAT_00B0E980 = DAT_007E1720 * DAT_007F46F8;
// SYNTHETIC: GAMEMD 0x6E8910
// GLOBAL: GAMEMD 0xB0E958
double DAT_00B0E958 = DAT_007E1728 * DAT_007F46F8;
// SYNTHETIC: GAMEMD 0x6E8930
// GLOBAL: GAMEMD 0xB0E930
double DAT_00B0E930 = DAT_007E1730 * DAT_007F46F8;
// SYNTHETIC: GAMEMD 0x6E8950
// GLOBAL: GAMEMD 0xB0E9A8
int DAT_00B0E9A8 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B0E930 - DAT_00B0E958) * DAT_00B0E950));
// SYNTHETIC: GAMEMD 0x6E8990
// GLOBAL: GAMEMD 0xB0E960
double DAT_00B0E960 = FUN_004CADE0((double)DAT_00B0E9A8 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x6E89C0
// GLOBAL: GAMEMD 0xB0E978
double DAT_00B0E978 = FUN_004CADE0((double)(DAT_00B0E9A8 * 2) / DAT_00B0E950);
// SYNTHETIC: GAMEMD 0x6E89F0
// GLOBAL: GAMEMD 0xB0E99C
int DAT_00B0E99C = (int)((double)(DAT_00B0E9A8 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x6E8A20
// GLOBAL: GAMEMD 0xB0E948
MathTblShortPair DAT_00B0E948;
// SYNTHETIC: GAMEMD 0x6E8A30
// GLOBAL: GAMEMD 0xB0E968
MathTblZero3 DAT_00B0E968;
// SYNTHETIC: GAMEMD 0x6E8A50
// GLOBAL: GAMEMD 0xB0E990
MathTblCoord DAT_00B0E990;
// SYNTHETIC: GAMEMD 0x6E8A70
// GLOBAL: GAMEMD 0xB0E938
MathTblZero4 DAT_00B0E938;
