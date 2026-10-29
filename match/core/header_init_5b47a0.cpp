// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5B47A0-0x5B4990 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7EDF58
const double DAT_007EDF58 = 60.0;
// GLOBAL: GAMEMD 0x7EDF60
const double DAT_007EDF60 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5B47A0
// GLOBAL: GAMEMD 0xABF018
MathTblZero4 DAT_00ABF018;
// SYNTHETIC: GAMEMD 0x5B47C0
// GLOBAL: GAMEMD 0xABF030
double DAT_00ABF030 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5B47F0
// GLOBAL: GAMEMD 0xABF080
double DAT_00ABF080 = DAT_00ABF030 / DAT_007EDF58;
// SYNTHETIC: GAMEMD 0x5B4810
// GLOBAL: GAMEMD 0xABF068
double DAT_00ABF068 = 1.0 / DAT_00ABF080;
// SYNTHETIC: GAMEMD 0x5B4830
// GLOBAL: GAMEMD 0xABF060
double DAT_00ABF060 = DAT_007EDF60 * 45.0;
// SYNTHETIC: GAMEMD 0x5B4850
// GLOBAL: GAMEMD 0xABF038
double DAT_00ABF038 = DAT_007EDF60 * 60.0;
// SYNTHETIC: GAMEMD 0x5B4870
// GLOBAL: GAMEMD 0xABF010
double DAT_00ABF010 = DAT_007EDF60 * 90.0;
// SYNTHETIC: GAMEMD 0x5B4890
// GLOBAL: GAMEMD 0xABF088
int DAT_00ABF088 = (int)(FUN_004CAD50(DAT_00ABF010 - DAT_00ABF038) * DAT_00ABF030 * 0.5);
// SYNTHETIC: GAMEMD 0x5B48D0
// GLOBAL: GAMEMD 0xABF040
double DAT_00ABF040 = FUN_004CADE0(DAT_00ABF088 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5B4900
// GLOBAL: GAMEMD 0xABF058
double DAT_00ABF058 = FUN_004CADE0((DAT_00ABF088 * 2) / DAT_00ABF030);
// SYNTHETIC: GAMEMD 0x5B4930
// GLOBAL: GAMEMD 0xABF07C
int DAT_00ABF07C = (int)(DAT_00ABF088 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5B4960
// GLOBAL: GAMEMD 0xABF028
HeaderCellInit DAT_00ABF028(0, 0);
// SYNTHETIC: GAMEMD 0x5B4970
// GLOBAL: GAMEMD 0xABF048
HeaderCoordInit DAT_00ABF048(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5B4990
// GLOBAL: GAMEMD 0xABF070
HeaderCoordInit DAT_00ABF070(128, 128, 0);
