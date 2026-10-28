// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5111E0-0x5113D0 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7EAB18
const double DAT_007EAB18 = 60.0;
// GLOBAL: GAMEMD 0x7EAB20
const double DAT_007EAB20 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5111E0
// GLOBAL: GAMEMD 0xA8F0D0
MathTblZero4 DAT_00A8F0D0;
// SYNTHETIC: GAMEMD 0x511200
// GLOBAL: GAMEMD 0xA8F0E8
double DAT_00A8F0E8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x511230
// GLOBAL: GAMEMD 0xA8F138
double DAT_00A8F138 = DAT_00A8F0E8 / DAT_007EAB18;
// SYNTHETIC: GAMEMD 0x511250
// GLOBAL: GAMEMD 0xA8F120
double DAT_00A8F120 = 1.0 / DAT_00A8F138;
// SYNTHETIC: GAMEMD 0x511270
// GLOBAL: GAMEMD 0xA8F118
double DAT_00A8F118 = DAT_007EAB20 * 45.0;
// SYNTHETIC: GAMEMD 0x511290
// GLOBAL: GAMEMD 0xA8F0F0
double DAT_00A8F0F0 = DAT_007EAB20 * 60.0;
// SYNTHETIC: GAMEMD 0x5112B0
// GLOBAL: GAMEMD 0xA8F0C8
double DAT_00A8F0C8 = DAT_007EAB20 * 90.0;
// SYNTHETIC: GAMEMD 0x5112D0
// GLOBAL: GAMEMD 0xA8F140
int DAT_00A8F140 = (int)(FUN_004CAD50(DAT_00A8F0C8 - DAT_00A8F0F0) * DAT_00A8F0E8 * 0.5);
// SYNTHETIC: GAMEMD 0x511310
// GLOBAL: GAMEMD 0xA8F0F8
double DAT_00A8F0F8 = FUN_004CADE0(DAT_00A8F140 * 0.00390625);
// SYNTHETIC: GAMEMD 0x511340
// GLOBAL: GAMEMD 0xA8F110
double DAT_00A8F110 = FUN_004CADE0((DAT_00A8F140 * 2) / DAT_00A8F0E8);
// SYNTHETIC: GAMEMD 0x511370
// GLOBAL: GAMEMD 0xA8F134
int DAT_00A8F134 = (int)(DAT_00A8F140 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5113A0
// GLOBAL: GAMEMD 0xA8F0E0
HeaderCellInit DAT_00A8F0E0(0, 0);
// SYNTHETIC: GAMEMD 0x5113B0
// GLOBAL: GAMEMD 0xA8F100
HeaderCoordInit DAT_00A8F100(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5113D0
// GLOBAL: GAMEMD 0xA8F128
HeaderCoordInit DAT_00A8F128(128, 128, 0);
