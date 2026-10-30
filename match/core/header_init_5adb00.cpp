// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5ADB00-0x5ADCF0 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7EDB38
const double DAT_007EDB38 = 60.0;
// GLOBAL: GAMEMD 0x7EDB40
const double DAT_007EDB40 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5ADB00
// GLOBAL: GAMEMD 0xABED60
MathTblZero4 DAT_00ABED60;
// SYNTHETIC: GAMEMD 0x5ADB20
// GLOBAL: GAMEMD 0xABED78
double DAT_00ABED78 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5ADB50
// GLOBAL: GAMEMD 0xABEDC8
double DAT_00ABEDC8 = DAT_00ABED78 / DAT_007EDB38;
// SYNTHETIC: GAMEMD 0x5ADB70
// GLOBAL: GAMEMD 0xABEDB0
double DAT_00ABEDB0 = 1.0 / DAT_00ABEDC8;
// SYNTHETIC: GAMEMD 0x5ADB90
// GLOBAL: GAMEMD 0xABEDA8
double DAT_00ABEDA8 = DAT_007EDB40 * 45.0;
// SYNTHETIC: GAMEMD 0x5ADBB0
// GLOBAL: GAMEMD 0xABED80
double DAT_00ABED80 = DAT_007EDB40 * 60.0;
// SYNTHETIC: GAMEMD 0x5ADBD0
// GLOBAL: GAMEMD 0xABED58
double DAT_00ABED58 = DAT_007EDB40 * 90.0;
// SYNTHETIC: GAMEMD 0x5ADBF0
// GLOBAL: GAMEMD 0xABEDD0
int DAT_00ABEDD0 = (int)(FUN_004CAD50(DAT_00ABED58 - DAT_00ABED80) * DAT_00ABED78 * 0.5);
// SYNTHETIC: GAMEMD 0x5ADC30
// GLOBAL: GAMEMD 0xABED88
double DAT_00ABED88 = FUN_004CADE0(DAT_00ABEDD0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5ADC60
// GLOBAL: GAMEMD 0xABEDA0
double DAT_00ABEDA0 = FUN_004CADE0((DAT_00ABEDD0 * 2) / DAT_00ABED78);
// SYNTHETIC: GAMEMD 0x5ADC90
// GLOBAL: GAMEMD 0xABEDC4
int DAT_00ABEDC4 = (int)(DAT_00ABEDD0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5ADCC0
// GLOBAL: GAMEMD 0xABED70
HeaderCellInit DAT_00ABED70(0, 0);
// SYNTHETIC: GAMEMD 0x5ADCD0
// GLOBAL: GAMEMD 0xABED90
HeaderCoordInit DAT_00ABED90(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5ADCF0
// GLOBAL: GAMEMD 0xABEDB8
HeaderCoordInit DAT_00ABEDB8(128, 128, 0);
