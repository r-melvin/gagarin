// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x517840-0x517A30 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7EAEE8
const double DAT_007EAEE8 = 60.0;
// GLOBAL: GAMEMD 0x7EAEF0
const double DAT_007EAEF0 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x517840
// GLOBAL: GAMEMD 0xA8F1E8
double DAT_00A8F1E8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x517870
// GLOBAL: GAMEMD 0xA8F238
double DAT_00A8F238 = DAT_00A8F1E8 / DAT_007EAEE8;
// SYNTHETIC: GAMEMD 0x517890
// GLOBAL: GAMEMD 0xA8F220
double DAT_00A8F220 = 1.0 / DAT_00A8F238;
// SYNTHETIC: GAMEMD 0x5178B0
// GLOBAL: GAMEMD 0xA8F218
double DAT_00A8F218 = DAT_007EAEF0 * 45.0;
// SYNTHETIC: GAMEMD 0x5178D0
// GLOBAL: GAMEMD 0xA8F1F0
double DAT_00A8F1F0 = DAT_007EAEF0 * 60.0;
// SYNTHETIC: GAMEMD 0x5178F0
// GLOBAL: GAMEMD 0xA8F1C8
double DAT_00A8F1C8 = DAT_007EAEF0 * 90.0;
// SYNTHETIC: GAMEMD 0x517910
// GLOBAL: GAMEMD 0xA8F240
int DAT_00A8F240 = (int)(FUN_004CAD50(DAT_00A8F1C8 - DAT_00A8F1F0) * DAT_00A8F1E8 * 0.5);
// SYNTHETIC: GAMEMD 0x517950
// GLOBAL: GAMEMD 0xA8F1F8
double DAT_00A8F1F8 = FUN_004CADE0(DAT_00A8F240 * 0.00390625);
// SYNTHETIC: GAMEMD 0x517980
// GLOBAL: GAMEMD 0xA8F210
double DAT_00A8F210 = FUN_004CADE0((DAT_00A8F240 * 2) / DAT_00A8F1E8);
// SYNTHETIC: GAMEMD 0x5179B0
// GLOBAL: GAMEMD 0xA8F234
int DAT_00A8F234 = (int)(DAT_00A8F240 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5179E0
// GLOBAL: GAMEMD 0xA8F1E0
HeaderCellInit DAT_00A8F1E0(0, 0);
// SYNTHETIC: GAMEMD 0x5179F0
// GLOBAL: GAMEMD 0xA8F200
HeaderCoordInit DAT_00A8F200(0, 0, 0);
// SYNTHETIC: GAMEMD 0x517A10
// GLOBAL: GAMEMD 0xA8F228
HeaderCoordInit DAT_00A8F228(128, 128, 0);
// SYNTHETIC: GAMEMD 0x517A30
// GLOBAL: GAMEMD 0xA8F1D0
MathTblZero4 DAT_00A8F1D0;
