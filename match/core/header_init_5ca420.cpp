// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5CA420-0x5CA610 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
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
// GLOBAL: GAMEMD 0x7EE6E8
extern const double DAT_007EE6E8;
// GLOBAL: GAMEMD 0x7EE6F0
const double DAT_007EE6F0 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5CA420
// GLOBAL: GAMEMD 0xABFA20
double DAT_00ABFA20 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5CA450
// GLOBAL: GAMEMD 0xABFA70
double DAT_00ABFA70 = DAT_00ABFA20 / DAT_007EE6E8;
// SYNTHETIC: GAMEMD 0x5CA470
// GLOBAL: GAMEMD 0xABFA58
double DAT_00ABFA58 = 1.0 / DAT_00ABFA70;
// SYNTHETIC: GAMEMD 0x5CA490
// GLOBAL: GAMEMD 0xABFA50
double DAT_00ABFA50 = DAT_007EE6F0 * 45.0;
// SYNTHETIC: GAMEMD 0x5CA4B0
// GLOBAL: GAMEMD 0xABFA28
double DAT_00ABFA28 = DAT_007EE6F0 * 60.0;
// SYNTHETIC: GAMEMD 0x5CA4D0
// GLOBAL: GAMEMD 0xABFA00
double DAT_00ABFA00 = DAT_007EE6F0 * 90.0;
// SYNTHETIC: GAMEMD 0x5CA4F0
// GLOBAL: GAMEMD 0xABFA78
int DAT_00ABFA78 = (int)(FUN_004CAD50(DAT_00ABFA00 - DAT_00ABFA28) * DAT_00ABFA20 * 0.5);
// SYNTHETIC: GAMEMD 0x5CA530
// GLOBAL: GAMEMD 0xABFA30
double DAT_00ABFA30 = FUN_004CADE0(DAT_00ABFA78 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5CA560
// GLOBAL: GAMEMD 0xABFA48
double DAT_00ABFA48 = FUN_004CADE0((DAT_00ABFA78 * 2) / DAT_00ABFA20);
// SYNTHETIC: GAMEMD 0x5CA590
// GLOBAL: GAMEMD 0xABFA6C
int DAT_00ABFA6C = (int)(DAT_00ABFA78 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5CA5C0
// GLOBAL: GAMEMD 0xABFA18
HeaderCellInit DAT_00ABFA18(0, 0);
// SYNTHETIC: GAMEMD 0x5CA5D0
// GLOBAL: GAMEMD 0xABFA38
HeaderCoordInit DAT_00ABFA38(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5CA5F0
// GLOBAL: GAMEMD 0xABFA60
TuningCoordInit DAT_00ABFA60(128, 128, 0);
// SYNTHETIC: GAMEMD 0x5CA610
// GLOBAL: GAMEMD 0xABFA08
MathTblZero4 DAT_00ABFA08;
