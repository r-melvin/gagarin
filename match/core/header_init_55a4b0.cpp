// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x55A4B0-0x55A6A0 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7ED348
const double DAT_007ED348 = 60.0;
// GLOBAL: GAMEMD 0x7ED350
const double DAT_007ED350 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x55A4B0
// GLOBAL: GAMEMD 0xABCC48
MathTblZero4 DAT_00ABCC48;
// SYNTHETIC: GAMEMD 0x55A4D0
// GLOBAL: GAMEMD 0xABCC60
double DAT_00ABCC60 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x55A500
// GLOBAL: GAMEMD 0xABCCB0
double DAT_00ABCCB0 = DAT_00ABCC60 / DAT_007ED348;
// SYNTHETIC: GAMEMD 0x55A520
// GLOBAL: GAMEMD 0xABCC98
double DAT_00ABCC98 = 1.0 / DAT_00ABCCB0;
// SYNTHETIC: GAMEMD 0x55A540
// GLOBAL: GAMEMD 0xABCC90
double DAT_00ABCC90 = DAT_007ED350 * 45.0;
// SYNTHETIC: GAMEMD 0x55A560
// GLOBAL: GAMEMD 0xABCC68
double DAT_00ABCC68 = DAT_007ED350 * 60.0;
// SYNTHETIC: GAMEMD 0x55A580
// GLOBAL: GAMEMD 0xABCC40
double DAT_00ABCC40 = DAT_007ED350 * 90.0;
// SYNTHETIC: GAMEMD 0x55A5A0
// GLOBAL: GAMEMD 0xABCCB8
int DAT_00ABCCB8 = (int)(FUN_004CAD50(DAT_00ABCC40 - DAT_00ABCC68) * DAT_00ABCC60 * 0.5);
// SYNTHETIC: GAMEMD 0x55A5E0
// GLOBAL: GAMEMD 0xABCC70
double DAT_00ABCC70 = FUN_004CADE0(DAT_00ABCCB8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x55A610
// GLOBAL: GAMEMD 0xABCC88
double DAT_00ABCC88 = FUN_004CADE0((DAT_00ABCCB8 * 2) / DAT_00ABCC60);
// SYNTHETIC: GAMEMD 0x55A640
// GLOBAL: GAMEMD 0xABCCAC
int DAT_00ABCCAC = (int)(DAT_00ABCCB8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x55A670
// GLOBAL: GAMEMD 0xABCC58
HeaderCellInit DAT_00ABCC58(0, 0);
// SYNTHETIC: GAMEMD 0x55A680
// GLOBAL: GAMEMD 0xABCC78
HeaderCoordInit DAT_00ABCC78(0, 0, 0);
// SYNTHETIC: GAMEMD 0x55A6A0
// GLOBAL: GAMEMD 0xABCCA0
HeaderCoordInit DAT_00ABCCA0(128, 128, 0);
