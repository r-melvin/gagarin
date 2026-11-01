// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40DDF0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E1AE0
const double DAT_007E1AE0 = 60.0;
// GLOBAL: GAMEMD 0x7E1AE8 -- degrees to radians
const double DAT_007E1AE8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x40DDC0
// GLOBAL: GAMEMD 0x887050
double DAT_00887050 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x40DDF0
// GLOBAL: GAMEMD 0x887268
double DAT_00887268 = DAT_00887050 / DAT_007E1AE0;
// SYNTHETIC: GAMEMD 0x40DE10
// GLOBAL: GAMEMD 0x8871F0
double DAT_008871F0 = 1.0 / DAT_00887268;
// SYNTHETIC: GAMEMD 0x40DE30
// GLOBAL: GAMEMD 0x8871E8
double DAT_008871E8 = DAT_007E1AE8 * 45.0;
// SYNTHETIC: GAMEMD 0x40DE50
// GLOBAL: GAMEMD 0x8870B0
double DAT_008870B0 = DAT_007E1AE8 * 60.0;
// SYNTHETIC: GAMEMD 0x40DE70
// GLOBAL: GAMEMD 0x887040
double DAT_00887040 = DAT_007E1AE8 * 90.0;
// SYNTHETIC: GAMEMD 0x40DE90
// GLOBAL: GAMEMD 0x887270
int DAT_00887270 = (int)(FUN_004CAD50(DAT_00887040 - DAT_008870B0) * DAT_00887050 * 0.5);
// SYNTHETIC: GAMEMD 0x40DED0
// GLOBAL: GAMEMD 0x8870B8
double DAT_008870B8 = FUN_004CADE0(DAT_00887270 * 0.00390625);
// SYNTHETIC: GAMEMD 0x40DF00
// GLOBAL: GAMEMD 0x8871D8
double DAT_008871D8 = FUN_004CADE0((DAT_00887270 * 2) / DAT_00887050);
// SYNTHETIC: GAMEMD 0x40DF30
// GLOBAL: GAMEMD 0x887260
int DAT_00887260 = (int)(DAT_00887270 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x40DF60
// GLOBAL: GAMEMD 0x88704C
HeaderCellInit DAT_0088704C(0, 0);
// SYNTHETIC: GAMEMD 0x40DF70
// GLOBAL: GAMEMD 0x887118
HeaderCoordInit DAT_00887118(0, 0, 0);
// SYNTHETIC: GAMEMD 0x40DF90
// GLOBAL: GAMEMD 0x8871F8
HeaderCoordInit DAT_008871F8(128, 128, 0);
