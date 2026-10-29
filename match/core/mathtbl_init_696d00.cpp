// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x696d00-0x696ee2 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7F1198
extern const double DAT_007F1198;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x696D00
// GLOBAL: GAMEMD 0xB057D0
MathTblZero4 DAT_00B057D0;
// SYNTHETIC: GAMEMD 0x696D20
// GLOBAL: GAMEMD 0xB057E8
double DAT_00B057E8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x696D90
// GLOBAL: GAMEMD 0xB07758
double DAT_00B07758 = DAT_007E1720 * DAT_007F1198;
// SYNTHETIC: GAMEMD 0x696DB0
// GLOBAL: GAMEMD 0xB057F0
double DAT_00B057F0 = DAT_007E1728 * DAT_007F1198;
// SYNTHETIC: GAMEMD 0x696DD0
// GLOBAL: GAMEMD 0xB057C8
double DAT_00B057C8 = DAT_007E1730 * DAT_007F1198;
// SYNTHETIC: GAMEMD 0x696DF0
// GLOBAL: GAMEMD 0xB07780
int DAT_00B07780 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B057C8 - DAT_00B057F0) * DAT_00B057E8));
// SYNTHETIC: GAMEMD 0x696E30
// GLOBAL: GAMEMD 0xB057F8
double DAT_00B057F8 = FUN_004CADE0((double)DAT_00B07780 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x696E60
// GLOBAL: GAMEMD 0xB07750
double DAT_00B07750 = FUN_004CADE0((double)(DAT_00B07780 * 2) / DAT_00B057E8);
// SYNTHETIC: GAMEMD 0x696E90
// GLOBAL: GAMEMD 0xB07774
int DAT_00B07774 = (int)((double)(DAT_00B07780 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x696EC0
// GLOBAL: GAMEMD 0xB057E0
MathTblShortPair DAT_00B057E0;
// SYNTHETIC: GAMEMD 0x696ED0
// GLOBAL: GAMEMD 0xB07740
MathTblZero3 DAT_00B07740;
