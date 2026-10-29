// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x5da4b0-0x5da692 (disassembled from the user's gamemd.exe v1.001).
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
// GLOBAL: GAMEMD 0x7EEF00
extern const double DAT_007EEF00;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x5DA4B0
// GLOBAL: GAMEMD 0xABFEF8
MathTblZero4 DAT_00ABFEF8;
// SYNTHETIC: GAMEMD 0x5DA4D0
// GLOBAL: GAMEMD 0xABFF10
double DAT_00ABFF10 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5DA540
// GLOBAL: GAMEMD 0xABFF40
double DAT_00ABFF40 = DAT_007E1720 * DAT_007EEF00;
// SYNTHETIC: GAMEMD 0x5DA560
// GLOBAL: GAMEMD 0xABFF18
double DAT_00ABFF18 = DAT_007E1728 * DAT_007EEF00;
// SYNTHETIC: GAMEMD 0x5DA580
// GLOBAL: GAMEMD 0xABFEF0
double DAT_00ABFEF0 = DAT_007E1730 * DAT_007EEF00;
// SYNTHETIC: GAMEMD 0x5DA5A0
// GLOBAL: GAMEMD 0xABFF68
int DAT_00ABFF68 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00ABFEF0 - DAT_00ABFF18) * DAT_00ABFF10));
// SYNTHETIC: GAMEMD 0x5DA5E0
// GLOBAL: GAMEMD 0xABFF20
double DAT_00ABFF20 = FUN_004CADE0((double)DAT_00ABFF68 * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x5DA610
// GLOBAL: GAMEMD 0xABFF38
double DAT_00ABFF38 = FUN_004CADE0((double)(DAT_00ABFF68 * 2) / DAT_00ABFF10);
// SYNTHETIC: GAMEMD 0x5DA640
// GLOBAL: GAMEMD 0xABFF5C
int DAT_00ABFF5C = (int)((double)(DAT_00ABFF68 * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x5DA670
// GLOBAL: GAMEMD 0xABFF08
MathTblShortPair DAT_00ABFF08;
// SYNTHETIC: GAMEMD 0x5DA680
// GLOBAL: GAMEMD 0xABFF28
MathTblZero3 DAT_00ABFF28;
