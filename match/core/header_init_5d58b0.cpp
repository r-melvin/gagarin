// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5D58B0-0x5D5AA0 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
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
// GLOBAL: GAMEMD 0x7EED08
const double DAT_007EED08 = 60.0;
// GLOBAL: GAMEMD 0x7EED10
const double DAT_007EED10 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5D58B0
// GLOBAL: GAMEMD 0xABFD58
double DAT_00ABFD58 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5D58E0
// GLOBAL: GAMEMD 0xABFDC8
double DAT_00ABFDC8 = DAT_00ABFD58 / DAT_007EED08;
// SYNTHETIC: GAMEMD 0x5D5900
// GLOBAL: GAMEMD 0xABFD98
double DAT_00ABFD98 = 1.0 / DAT_00ABFDC8;
// SYNTHETIC: GAMEMD 0x5D5920
// GLOBAL: GAMEMD 0xABFD90
double DAT_00ABFD90 = DAT_007EED10 * 45.0;
// SYNTHETIC: GAMEMD 0x5D5940
// GLOBAL: GAMEMD 0xABFD60
double DAT_00ABFD60 = DAT_007EED10 * 60.0;
// SYNTHETIC: GAMEMD 0x5D5960
// GLOBAL: GAMEMD 0xABFD38
double DAT_00ABFD38 = DAT_007EED10 * 90.0;
// SYNTHETIC: GAMEMD 0x5D5980
// GLOBAL: GAMEMD 0xABFDD0
int DAT_00ABFDD0 = (int)(FUN_004CAD50(DAT_00ABFD38 - DAT_00ABFD60) * DAT_00ABFD58 * 0.5);
// SYNTHETIC: GAMEMD 0x5D59C0
// GLOBAL: GAMEMD 0xABFD68
double DAT_00ABFD68 = FUN_004CADE0(DAT_00ABFDD0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5D59F0
// GLOBAL: GAMEMD 0xABFD88
double DAT_00ABFD88 = FUN_004CADE0((DAT_00ABFDD0 * 2) / DAT_00ABFD58);
// SYNTHETIC: GAMEMD 0x5D5A20
// GLOBAL: GAMEMD 0xABFDC4
int DAT_00ABFDC4 = (int)(DAT_00ABFDD0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5D5A50
// GLOBAL: GAMEMD 0xABFD50
HeaderCellInit DAT_00ABFD50(0, 0);
// SYNTHETIC: GAMEMD 0x5D5A60
// GLOBAL: GAMEMD 0xABFD78
HeaderCoordInit DAT_00ABFD78(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5D5A80
// GLOBAL: GAMEMD 0xABFDB8
HeaderCoordInit DAT_00ABFDB8(128, 128, 0);
// SYNTHETIC: GAMEMD 0x5D5AA0
// GLOBAL: GAMEMD 0xABFD40
MathTblZero4 DAT_00ABFD40;
