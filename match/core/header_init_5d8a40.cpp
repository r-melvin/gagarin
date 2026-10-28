// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5D8A40-0x5D8C30 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7EEEC8
const double DAT_007EEEC8 = 60.0;
// GLOBAL: GAMEMD 0x7EEED0
const double DAT_007EEED0 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5D8A40
// GLOBAL: GAMEMD 0xABFDE0
MathTblZero4 DAT_00ABFDE0;
// SYNTHETIC: GAMEMD 0x5D8A60
// GLOBAL: GAMEMD 0xABFDF8
double DAT_00ABFDF8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5D8A90
// GLOBAL: GAMEMD 0xABFE48
double DAT_00ABFE48 = DAT_00ABFDF8 / DAT_007EEEC8;
// SYNTHETIC: GAMEMD 0x5D8AB0
// GLOBAL: GAMEMD 0xABFE30
double DAT_00ABFE30 = 1.0 / DAT_00ABFE48;
// SYNTHETIC: GAMEMD 0x5D8AD0
// GLOBAL: GAMEMD 0xABFE28
double DAT_00ABFE28 = DAT_007EEED0 * 45.0;
// SYNTHETIC: GAMEMD 0x5D8AF0
// GLOBAL: GAMEMD 0xABFE00
double DAT_00ABFE00 = DAT_007EEED0 * 60.0;
// SYNTHETIC: GAMEMD 0x5D8B10
// GLOBAL: GAMEMD 0xABFDD8
double DAT_00ABFDD8 = DAT_007EEED0 * 90.0;
// SYNTHETIC: GAMEMD 0x5D8B30
// GLOBAL: GAMEMD 0xABFE50
int DAT_00ABFE50 = (int)(FUN_004CAD50(DAT_00ABFDD8 - DAT_00ABFE00) * DAT_00ABFDF8 * 0.5);
// SYNTHETIC: GAMEMD 0x5D8B70
// GLOBAL: GAMEMD 0xABFE08
double DAT_00ABFE08 = FUN_004CADE0(DAT_00ABFE50 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5D8BA0
// GLOBAL: GAMEMD 0xABFE20
double DAT_00ABFE20 = FUN_004CADE0((DAT_00ABFE50 * 2) / DAT_00ABFDF8);
// SYNTHETIC: GAMEMD 0x5D8BD0
// GLOBAL: GAMEMD 0xABFE44
int DAT_00ABFE44 = (int)(DAT_00ABFE50 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5D8C00
// GLOBAL: GAMEMD 0xABFDF0
HeaderCellInit DAT_00ABFDF0(0, 0);
// SYNTHETIC: GAMEMD 0x5D8C10
// GLOBAL: GAMEMD 0xABFE10
HeaderCoordInit DAT_00ABFE10(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5D8C30
// GLOBAL: GAMEMD 0xABFE38
HeaderCoordInit DAT_00ABFE38(128, 128, 0);
