// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5C94F0-0x5C96E0 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
#include <math.h>
#pragma intrinsic(pow)
#include "header_init_shapes.h"
#include "header_tuning_globals.h"
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
// GLOBAL: GAMEMD 0x7EE6D8
extern const double DAT_007EE6D8;
// GLOBAL: GAMEMD 0x7EE6E0
const double DAT_007EE6E0 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5C94F0
// GLOBAL: GAMEMD 0xABF980
MathTblZero4 DAT_00ABF980;
// SYNTHETIC: GAMEMD 0x5C9510
// GLOBAL: GAMEMD 0xABF998
double DAT_00ABF998 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5C9540
// GLOBAL: GAMEMD 0xABF9E8
double DAT_00ABF9E8 = DAT_00ABF998 / DAT_007EE6D8;
// SYNTHETIC: GAMEMD 0x5C9560
// GLOBAL: GAMEMD 0xABF9D0
double DAT_00ABF9D0 = 1.0 / DAT_00ABF9E8;
// SYNTHETIC: GAMEMD 0x5C9580
// GLOBAL: GAMEMD 0xABF9C8
double DAT_00ABF9C8 = DAT_007EE6E0 * 45.0;
// SYNTHETIC: GAMEMD 0x5C95A0
// GLOBAL: GAMEMD 0xABF9A0
double DAT_00ABF9A0 = DAT_007EE6E0 * 60.0;
// SYNTHETIC: GAMEMD 0x5C95C0
// GLOBAL: GAMEMD 0xABF978
double DAT_00ABF978 = DAT_007EE6E0 * 90.0;
// SYNTHETIC: GAMEMD 0x5C95E0
// GLOBAL: GAMEMD 0xABF9F0
int DAT_00ABF9F0 = (int)(FUN_004CAD50(DAT_00ABF978 - DAT_00ABF9A0) * DAT_00ABF998 * 0.5);
// SYNTHETIC: GAMEMD 0x5C9620
// GLOBAL: GAMEMD 0xABF9A8
double DAT_00ABF9A8 = FUN_004CADE0(DAT_00ABF9F0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5C9650
// GLOBAL: GAMEMD 0xABF9C0
double DAT_00ABF9C0 = FUN_004CADE0((DAT_00ABF9F0 * 2) / DAT_00ABF998);
// SYNTHETIC: GAMEMD 0x5C9680
// GLOBAL: GAMEMD 0xABF9E4
int DAT_00ABF9E4 = (int)(DAT_00ABF9F0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5C96B0
// GLOBAL: GAMEMD 0xABF990
HeaderCellInit DAT_00ABF990(0, 0);
// SYNTHETIC: GAMEMD 0x5C96C0
// GLOBAL: GAMEMD 0xABF9B0
HeaderCoordInit DAT_00ABF9B0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5C96E0
// GLOBAL: GAMEMD 0xABF9D8
TuningCoordInit DAT_00ABF9D8(128, 128, 0);
