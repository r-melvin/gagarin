// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5B1EE0-0x5B20D0 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7EDC70
const double DAT_007EDC70 = 60.0;
// GLOBAL: GAMEMD 0x7EDC78
const double DAT_007EDC78 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5B1EE0
// GLOBAL: GAMEMD 0xABEEE0
MathTblZero4 DAT_00ABEEE0;
// SYNTHETIC: GAMEMD 0x5B1F00
// GLOBAL: GAMEMD 0xABEEF8
double DAT_00ABEEF8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5B1F30
// GLOBAL: GAMEMD 0xABEF48
double DAT_00ABEF48 = DAT_00ABEEF8 / DAT_007EDC70;
// SYNTHETIC: GAMEMD 0x5B1F50
// GLOBAL: GAMEMD 0xABEF30
double DAT_00ABEF30 = 1.0 / DAT_00ABEF48;
// SYNTHETIC: GAMEMD 0x5B1F70
// GLOBAL: GAMEMD 0xABEF28
double DAT_00ABEF28 = DAT_007EDC78 * 45.0;
// SYNTHETIC: GAMEMD 0x5B1F90
// GLOBAL: GAMEMD 0xABEF00
double DAT_00ABEF00 = DAT_007EDC78 * 60.0;
// SYNTHETIC: GAMEMD 0x5B1FB0
// GLOBAL: GAMEMD 0xABEED8
double DAT_00ABEED8 = DAT_007EDC78 * 90.0;
// SYNTHETIC: GAMEMD 0x5B1FD0
// GLOBAL: GAMEMD 0xABEF50
int DAT_00ABEF50 = (int)(FUN_004CAD50(DAT_00ABEED8 - DAT_00ABEF00) * DAT_00ABEEF8 * 0.5);
// SYNTHETIC: GAMEMD 0x5B2010
// GLOBAL: GAMEMD 0xABEF08
double DAT_00ABEF08 = FUN_004CADE0(DAT_00ABEF50 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5B2040
// GLOBAL: GAMEMD 0xABEF20
double DAT_00ABEF20 = FUN_004CADE0((DAT_00ABEF50 * 2) / DAT_00ABEEF8);
// SYNTHETIC: GAMEMD 0x5B2070
// GLOBAL: GAMEMD 0xABEF44
int DAT_00ABEF44 = (int)(DAT_00ABEF50 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5B20A0
// GLOBAL: GAMEMD 0xABEEF0
HeaderCellInit DAT_00ABEEF0(0, 0);
// SYNTHETIC: GAMEMD 0x5B20B0
// GLOBAL: GAMEMD 0xABEF10
HeaderCoordInit DAT_00ABEF10(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5B20D0
// GLOBAL: GAMEMD 0xABEF38
HeaderCoordInit DAT_00ABEF38(128, 128, 0);
