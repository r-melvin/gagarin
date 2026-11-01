// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40F2D0
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
// GLOBAL: GAMEMD 0x7E1E70
const double DAT_007E1E70 = 60.0;
// GLOBAL: GAMEMD 0x7E1E78 -- degrees to radians
const double DAT_007E1E78 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x40F2A0
// GLOBAL: GAMEMD 0x887490
double DAT_00887490 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x40F2D0
// GLOBAL: GAMEMD 0x8874F8
double DAT_008874F8 = DAT_00887490 / DAT_007E1E70;
// SYNTHETIC: GAMEMD 0x40F2F0
// GLOBAL: GAMEMD 0x8874E0
double DAT_008874E0 = 1.0 / DAT_008874F8;
// SYNTHETIC: GAMEMD 0x40F310
// GLOBAL: GAMEMD 0x8874D8
double DAT_008874D8 = DAT_007E1E78 * 45.0;
// SYNTHETIC: GAMEMD 0x40F330
// GLOBAL: GAMEMD 0x887498
double DAT_00887498 = DAT_007E1E78 * 60.0;
// SYNTHETIC: GAMEMD 0x40F350
// GLOBAL: GAMEMD 0x887480
double DAT_00887480 = DAT_007E1E78 * 90.0;
// SYNTHETIC: GAMEMD 0x40F370
// GLOBAL: GAMEMD 0x887500
int DAT_00887500 = (int)(FUN_004CAD50(DAT_00887480 - DAT_00887498) * DAT_00887490 * 0.5);
// SYNTHETIC: GAMEMD 0x40F3B0
// GLOBAL: GAMEMD 0x8874A0
double DAT_008874A0 = FUN_004CADE0(DAT_00887500 * 0.00390625);
// SYNTHETIC: GAMEMD 0x40F3E0
// GLOBAL: GAMEMD 0x8874B8
double DAT_008874B8 = FUN_004CADE0((DAT_00887500 * 2) / DAT_00887490);
// SYNTHETIC: GAMEMD 0x40F410
// GLOBAL: GAMEMD 0x8874F4
int DAT_008874F4 = (int)(DAT_00887500 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x40F440
// GLOBAL: GAMEMD 0x887488
HeaderCellInit DAT_00887488(0, 0);
// SYNTHETIC: GAMEMD 0x40F450
// GLOBAL: GAMEMD 0x8874A8
HeaderCoordInit DAT_008874A8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x40F470
// GLOBAL: GAMEMD 0x8874E8
HeaderCoordInit DAT_008874E8(128, 128, 0);
