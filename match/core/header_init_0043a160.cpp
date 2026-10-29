// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x43A160
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
// GLOBAL: GAMEMD 0x7E3DB0
const double DAT_007E3DB0 = 60.0;
// GLOBAL: GAMEMD 0x7E3DB8 -- degrees to radians
const double DAT_007E3DB8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x43A160
// GLOBAL: GAMEMD 0x89C790
double DAT_0089C790 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x43A190
// GLOBAL: GAMEMD 0x89C7E0
double DAT_0089C7E0 = DAT_0089C790 / DAT_007E3DB0;
// SYNTHETIC: GAMEMD 0x43A1B0
// GLOBAL: GAMEMD 0x89C7C8
double DAT_0089C7C8 = 1.0 / DAT_0089C7E0;
// SYNTHETIC: GAMEMD 0x43A1D0
// GLOBAL: GAMEMD 0x89C7C0
double DAT_0089C7C0 = DAT_007E3DB8 * 45.0;
// SYNTHETIC: GAMEMD 0x43A1F0
// GLOBAL: GAMEMD 0x89C798
double DAT_0089C798 = DAT_007E3DB8 * 60.0;
// SYNTHETIC: GAMEMD 0x43A210
// GLOBAL: GAMEMD 0x89C780
double DAT_0089C780 = DAT_007E3DB8 * 90.0;
// SYNTHETIC: GAMEMD 0x43A230
// GLOBAL: GAMEMD 0x89C7E8
int DAT_0089C7E8 = (int)(FUN_004CAD50(DAT_0089C780 - DAT_0089C798) * DAT_0089C790 * 0.5);
// SYNTHETIC: GAMEMD 0x43A270
// GLOBAL: GAMEMD 0x89C7A0
double DAT_0089C7A0 = FUN_004CADE0(DAT_0089C7E8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x43A2A0
// GLOBAL: GAMEMD 0x89C7B8
double DAT_0089C7B8 = FUN_004CADE0((DAT_0089C7E8 * 2) / DAT_0089C790);
// SYNTHETIC: GAMEMD 0x43A2D0
// GLOBAL: GAMEMD 0x89C7DC
int DAT_0089C7DC = (int)(DAT_0089C7E8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x43A300
// GLOBAL: GAMEMD 0x89C788
HeaderCellInit DAT_0089C788(0, 0);
// SYNTHETIC: GAMEMD 0x43A310
// GLOBAL: GAMEMD 0x89C7A8
HeaderCoordInit DAT_0089C7A8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x43A330
// GLOBAL: GAMEMD 0x89C7D0
HeaderCoordInit DAT_0089C7D0(128, 128, 0);
