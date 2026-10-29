// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x6dcd70-0x6dcf77 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7F43C0
extern const double DAT_007F43C0;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x6DCD70
// GLOBAL: GAMEMD 0xB0E688
double DAT_00B0E688 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6DCDE0
// GLOBAL: GAMEMD 0xB0E6B8
double DAT_00B0E6B8 = DAT_007E1720 * DAT_007F43C0;
// SYNTHETIC: GAMEMD 0x6DCE00
// GLOBAL: GAMEMD 0xB0E690
double DAT_00B0E690 = DAT_007E1728 * DAT_007F43C0;
// SYNTHETIC: GAMEMD 0x6DCE20
// GLOBAL: GAMEMD 0xB0E650
double DAT_00B0E650 = DAT_007E1730 * DAT_007F43C0;
// SYNTHETIC: GAMEMD 0x6DCE40
// GLOBAL: GAMEMD 0xB0E6E0
int DAT_00B0E6E0 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00B0E650 - DAT_00B0E690) * DAT_00B0E688));
// SYNTHETIC: GAMEMD 0x6DCE80
// GLOBAL: GAMEMD 0xB0E698
double DAT_00B0E698 = FUN_004CADE0((double)DAT_00B0E6E0 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x6DCEB0
// GLOBAL: GAMEMD 0xB0E6B0
double DAT_00B0E6B0 = FUN_004CADE0((double)(DAT_00B0E6E0 * 2) / DAT_00B0E688);
// SYNTHETIC: GAMEMD 0x6DCEE0
// GLOBAL: GAMEMD 0xB0E6D4
int DAT_00B0E6D4 = (int)((double)(DAT_00B0E6E0 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x6DCF10
// GLOBAL: GAMEMD 0xB0E680
MathTblShortPair DAT_00B0E680;
// SYNTHETIC: GAMEMD 0x6DCF20
// GLOBAL: GAMEMD 0xB0E6A0
MathTblZero3 DAT_00B0E6A0;
// SYNTHETIC: GAMEMD 0x6DCF60
// GLOBAL: GAMEMD 0xB0E670
MathTblZero4 DAT_00B0E670;
