// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6b4840-0x6b4a47 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7F32C0
extern const double DAT_007F32C0;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x6B4840
// GLOBAL: GAMEMD 0xB0B710
double DAT_00B0B710 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6B48B0
// GLOBAL: GAMEMD 0xB0B740
double DAT_00B0B740 = DAT_007E1720 * DAT_007F32C0;
// SYNTHETIC: GAMEMD 0x6B48D0
// GLOBAL: GAMEMD 0xB0B718
double DAT_00B0B718 = DAT_007E1728 * DAT_007F32C0;
// SYNTHETIC: GAMEMD 0x6B48F0
// GLOBAL: GAMEMD 0xB0B6F0
double DAT_00B0B6F0 = DAT_007E1730 * DAT_007F32C0;
// SYNTHETIC: GAMEMD 0x6B4910
// GLOBAL: GAMEMD 0xB0B768
int DAT_00B0B768 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B0B6F0 - DAT_00B0B718) * DAT_00B0B710));
// SYNTHETIC: GAMEMD 0x6B4950
// GLOBAL: GAMEMD 0xB0B720
double DAT_00B0B720 = FUN_004CADE0((double)DAT_00B0B768 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x6B4980
// GLOBAL: GAMEMD 0xB0B738
double DAT_00B0B738 = FUN_004CADE0((double)(DAT_00B0B768 * 2) / DAT_00B0B710);
// SYNTHETIC: GAMEMD 0x6B49B0
// GLOBAL: GAMEMD 0xB0B75C
int DAT_00B0B75C = (int)((double)(DAT_00B0B768 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x6B49E0
// GLOBAL: GAMEMD 0xB0B708
MathTblShortPair DAT_00B0B708;
// SYNTHETIC: GAMEMD 0x6B49F0
// GLOBAL: GAMEMD 0xB0B728
MathTblZero3 DAT_00B0B728;
// SYNTHETIC: GAMEMD 0x6B4A10
// GLOBAL: GAMEMD 0xB0B750
MathTblCoord DAT_00B0B750;
// SYNTHETIC: GAMEMD 0x6B4A30
// GLOBAL: GAMEMD 0xB0B6F8
MathTblZero4 DAT_00B0B6F8;
