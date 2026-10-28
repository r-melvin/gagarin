// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6954c0-0x6956a2 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7F1188
extern const double DAT_007F1188;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x6954C0
// GLOBAL: GAMEMD 0xB05750
MathTblZero4 DAT_00B05750;
// SYNTHETIC: GAMEMD 0x6954E0
// GLOBAL: GAMEMD 0xB05768
double DAT_00B05768 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x695550
// GLOBAL: GAMEMD 0xB05798
double DAT_00B05798 = DAT_007E1720 * DAT_007F1188;
// SYNTHETIC: GAMEMD 0x695570
// GLOBAL: GAMEMD 0xB05770
double DAT_00B05770 = DAT_007E1728 * DAT_007F1188;
// SYNTHETIC: GAMEMD 0x695590
// GLOBAL: GAMEMD 0xB05748
double DAT_00B05748 = DAT_007E1730 * DAT_007F1188;
// SYNTHETIC: GAMEMD 0x6955B0
// GLOBAL: GAMEMD 0xB057C0
int DAT_00B057C0 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B05748 - DAT_00B05770) * DAT_00B05768));
// SYNTHETIC: GAMEMD 0x6955F0
// GLOBAL: GAMEMD 0xB05778
double DAT_00B05778 = FUN_004CADE0((double)DAT_00B057C0 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x695620
// GLOBAL: GAMEMD 0xB05790
double DAT_00B05790 = FUN_004CADE0((double)(DAT_00B057C0 * 2) / DAT_00B05768);
// SYNTHETIC: GAMEMD 0x695650
// GLOBAL: GAMEMD 0xB057B4
int DAT_00B057B4 = (int)((double)(DAT_00B057C0 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x695680
// GLOBAL: GAMEMD 0xB05760
MathTblShortPair DAT_00B05760;
// SYNTHETIC: GAMEMD 0x695690
// GLOBAL: GAMEMD 0xB05780
MathTblZero3 DAT_00B05780;
