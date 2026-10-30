// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x543120-0x543310 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7EC218
const double DAT_007EC218 = 60.0;
// GLOBAL: GAMEMD 0x7EC220
const double DAT_007EC220 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x543120
// GLOBAL: GAMEMD 0xAA06D8
double DAT_00AA06D8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x543150
// GLOBAL: GAMEMD 0xAA0728
double DAT_00AA0728 = DAT_00AA06D8 / DAT_007EC218;
// SYNTHETIC: GAMEMD 0x543170
// GLOBAL: GAMEMD 0xAA0710
double DAT_00AA0710 = 1.0 / DAT_00AA0728;
// SYNTHETIC: GAMEMD 0x543190
// GLOBAL: GAMEMD 0xAA0708
double DAT_00AA0708 = DAT_007EC220 * 45.0;
// SYNTHETIC: GAMEMD 0x5431B0
// GLOBAL: GAMEMD 0xAA06E0
double DAT_00AA06E0 = DAT_007EC220 * 60.0;
// SYNTHETIC: GAMEMD 0x5431D0
// GLOBAL: GAMEMD 0xAA06B8
double DAT_00AA06B8 = DAT_007EC220 * 90.0;
// SYNTHETIC: GAMEMD 0x5431F0
// GLOBAL: GAMEMD 0xAA0730
int DAT_00AA0730 = (int)(FUN_004CAD50(DAT_00AA06B8 - DAT_00AA06E0) * DAT_00AA06D8 * 0.5);
// SYNTHETIC: GAMEMD 0x543230
// GLOBAL: GAMEMD 0xAA06E8
double DAT_00AA06E8 = FUN_004CADE0(DAT_00AA0730 * 0.00390625);
// SYNTHETIC: GAMEMD 0x543260
// GLOBAL: GAMEMD 0xAA0700
double DAT_00AA0700 = FUN_004CADE0((DAT_00AA0730 * 2) / DAT_00AA06D8);
// SYNTHETIC: GAMEMD 0x543290
// GLOBAL: GAMEMD 0xAA0724
int DAT_00AA0724 = (int)(DAT_00AA0730 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5432C0
// GLOBAL: GAMEMD 0xAA06D0
HeaderCellInit DAT_00AA06D0(0, 0);
// SYNTHETIC: GAMEMD 0x5432D0
// GLOBAL: GAMEMD 0xAA06F0
HeaderCoordInit DAT_00AA06F0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5432F0
// GLOBAL: GAMEMD 0xAA0718
HeaderCoordInit DAT_00AA0718(128, 128, 0);
// SYNTHETIC: GAMEMD 0x543310
// GLOBAL: GAMEMD 0xAA06C0
MathTblZero4 DAT_00AA06C0;
