// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x4F4EE0-0x4F50D0 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"
#include "../_layout/cell.h"

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
// GLOBAL: GAMEMD 0x7EA758
const double DAT_007EA758 = 60.0;
// GLOBAL: GAMEMD 0x7EA760
const double DAT_007EA760 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x4F4EE0
// GLOBAL: GAMEMD 0xA8EF68
MathTblZero4 DAT_00A8EF68;
// SYNTHETIC: GAMEMD 0x4F4F00
// GLOBAL: GAMEMD 0xA8EFA0
double DAT_00A8EFA0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x4F4F30
// GLOBAL: GAMEMD 0xA8F030
double DAT_00A8F030 = DAT_00A8EFA0 / DAT_007EA758;
// SYNTHETIC: GAMEMD 0x4F4F50
// GLOBAL: GAMEMD 0xA8F018
double DAT_00A8F018 = 1.0 / DAT_00A8F030;
// SYNTHETIC: GAMEMD 0x4F4F70
// GLOBAL: GAMEMD 0xA8F010
double DAT_00A8F010 = DAT_007EA760 * 45.0;
// SYNTHETIC: GAMEMD 0x4F4F90
// GLOBAL: GAMEMD 0xA8EFE0
double DAT_00A8EFE0 = DAT_007EA760 * 60.0;
// SYNTHETIC: GAMEMD 0x4F4FB0
// GLOBAL: GAMEMD 0xA8EF58
double DAT_00A8EF58 = DAT_007EA760 * 90.0;
// SYNTHETIC: GAMEMD 0x4F4FD0
// GLOBAL: GAMEMD 0xA8F038
int DAT_00A8F038 = (int)(FUN_004CAD50(DAT_00A8EF58 - DAT_00A8EFE0) * DAT_00A8EFA0 * 0.5);
// SYNTHETIC: GAMEMD 0x4F5010
// GLOBAL: GAMEMD 0xA8EFF0
double DAT_00A8EFF0 = FUN_004CADE0(DAT_00A8F038 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4F5040
// GLOBAL: GAMEMD 0xA8F008
double DAT_00A8F008 = FUN_004CADE0((DAT_00A8F038 * 2) / DAT_00A8EFA0);
// SYNTHETIC: GAMEMD 0x4F5070
// GLOBAL: GAMEMD 0xA8F02C
int DAT_00A8F02C = (int)(DAT_00A8F038 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4F50A0
// GLOBAL: GAMEMD 0xA8EF98
Cell DAT_00A8EF98(0, 0);
// SYNTHETIC: GAMEMD 0x4F50B0
// GLOBAL: GAMEMD 0xA8EFF8
HeaderCoordInit DAT_00A8EFF8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4F50D0
// GLOBAL: GAMEMD 0xA8F020
HeaderCoordInit DAT_00A8F020(128, 128, 0);
