// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x523490-0x523680 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
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
// GLOBAL: GAMEMD 0x7EB5D0
const double DAT_007EB5D0 = 60.0;
// GLOBAL: GAMEMD 0x7EB5D8
const double DAT_007EB5D8 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x523490
// GLOBAL: GAMEMD 0xA8F268
double DAT_00A8F268 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5234C0
// GLOBAL: GAMEMD 0xA8F2C0
double DAT_00A8F2C0 = DAT_00A8F268 / DAT_007EB5D0;
// SYNTHETIC: GAMEMD 0x5234E0
// GLOBAL: GAMEMD 0xA8F2A8
double DAT_00A8F2A8 = 1.0 / DAT_00A8F2C0;
// SYNTHETIC: GAMEMD 0x523500
// GLOBAL: GAMEMD 0xA8F2A0
double DAT_00A8F2A0 = DAT_007EB5D8 * 45.0;
// SYNTHETIC: GAMEMD 0x523520
// GLOBAL: GAMEMD 0xA8F270
double DAT_00A8F270 = DAT_007EB5D8 * 60.0;
// SYNTHETIC: GAMEMD 0x523540
// GLOBAL: GAMEMD 0xA8F248
double DAT_00A8F248 = DAT_007EB5D8 * 90.0;
// SYNTHETIC: GAMEMD 0x523560
// GLOBAL: GAMEMD 0xA8F2CC
int DAT_00A8F2CC = (int)(FUN_004CAD50(DAT_00A8F248 - DAT_00A8F270) * DAT_00A8F268 * 0.5);
// SYNTHETIC: GAMEMD 0x5235A0
// GLOBAL: GAMEMD 0xA8F278
double DAT_00A8F278 = FUN_004CADE0(DAT_00A8F2CC * 0.00390625);
// SYNTHETIC: GAMEMD 0x5235D0
// GLOBAL: GAMEMD 0xA8F298
double DAT_00A8F298 = FUN_004CADE0((DAT_00A8F2CC * 2) / DAT_00A8F268);
// SYNTHETIC: GAMEMD 0x523600
// GLOBAL: GAMEMD 0xA8F2BC
int DAT_00A8F2BC = (int)(DAT_00A8F2CC * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x523630
// GLOBAL: GAMEMD 0xA8F260
HeaderCellInit DAT_00A8F260(0, 0);
// SYNTHETIC: GAMEMD 0x523640
// GLOBAL: GAMEMD 0xA8F280
HeaderCoordInit DAT_00A8F280(0, 0, 0);
// SYNTHETIC: GAMEMD 0x523660
// GLOBAL: GAMEMD 0xA8F2B0
HeaderCoordInit DAT_00A8F2B0(128, 128, 0);
// SYNTHETIC: GAMEMD 0x523680
// GLOBAL: GAMEMD 0xA8F250
MathTblZero4 DAT_00A8F250;
