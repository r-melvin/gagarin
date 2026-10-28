// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x55AD30-0x55AF20 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7ED368
const double DAT_007ED368 = 60.0;
// GLOBAL: GAMEMD 0x7ED370
const double DAT_007ED370 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x55AD30
// GLOBAL: GAMEMD 0xABCCC8
MathTblZero4 DAT_00ABCCC8;
// SYNTHETIC: GAMEMD 0x55AD50
// GLOBAL: GAMEMD 0xABCCE0
double DAT_00ABCCE0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x55AD80
// GLOBAL: GAMEMD 0xABCD30
double DAT_00ABCD30 = DAT_00ABCCE0 / DAT_007ED368;
// SYNTHETIC: GAMEMD 0x55ADA0
// GLOBAL: GAMEMD 0xABCD18
double DAT_00ABCD18 = 1.0 / DAT_00ABCD30;
// SYNTHETIC: GAMEMD 0x55ADC0
// GLOBAL: GAMEMD 0xABCD10
double DAT_00ABCD10 = DAT_007ED370 * 45.0;
// SYNTHETIC: GAMEMD 0x55ADE0
// GLOBAL: GAMEMD 0xABCCE8
double DAT_00ABCCE8 = DAT_007ED370 * 60.0;
// SYNTHETIC: GAMEMD 0x55AE00
// GLOBAL: GAMEMD 0xABCCC0
double DAT_00ABCCC0 = DAT_007ED370 * 90.0;
// SYNTHETIC: GAMEMD 0x55AE20
// GLOBAL: GAMEMD 0xABCD38
int DAT_00ABCD38 = (int)(FUN_004CAD50(DAT_00ABCCC0 - DAT_00ABCCE8) * DAT_00ABCCE0 * 0.5);
// SYNTHETIC: GAMEMD 0x55AE60
// GLOBAL: GAMEMD 0xABCCF0
double DAT_00ABCCF0 = FUN_004CADE0(DAT_00ABCD38 * 0.00390625);
// SYNTHETIC: GAMEMD 0x55AE90
// GLOBAL: GAMEMD 0xABCD08
double DAT_00ABCD08 = FUN_004CADE0((DAT_00ABCD38 * 2) / DAT_00ABCCE0);
// SYNTHETIC: GAMEMD 0x55AEC0
// GLOBAL: GAMEMD 0xABCD2C
int DAT_00ABCD2C = (int)(DAT_00ABCD38 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x55AEF0
// GLOBAL: GAMEMD 0xABCCD8
HeaderCellInit DAT_00ABCCD8(0, 0);
// SYNTHETIC: GAMEMD 0x55AF00
// GLOBAL: GAMEMD 0xABCCF8
HeaderCoordInit DAT_00ABCCF8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x55AF20
// GLOBAL: GAMEMD 0xABCD20
HeaderCoordInit DAT_00ABCD20(128, 128, 0);
