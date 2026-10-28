// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x41E160
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E2A08
const double DAT_007E2A08 = 60.0;
// GLOBAL: GAMEMD 0x7E2A10 -- degrees to radians
const double DAT_007E2A10 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x41E160
// GLOBAL: GAMEMD 0x88A020
double DAT_0088A020 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x41E1D0
// GLOBAL: GAMEMD 0x88A050
double DAT_0088A050 = DAT_007E2A10 * 45.0;
// SYNTHETIC: GAMEMD 0x41E1F0
// GLOBAL: GAMEMD 0x88A028
double DAT_0088A028 = DAT_007E2A10 * 60.0;
// SYNTHETIC: GAMEMD 0x41E210
// GLOBAL: GAMEMD 0x88A000
double DAT_0088A000 = DAT_007E2A10 * 90.0;
// SYNTHETIC: GAMEMD 0x41E230
// GLOBAL: GAMEMD 0x88A078
int DAT_0088A078 = (int)(FUN_004CAD50(DAT_0088A000 - DAT_0088A028) * DAT_0088A020 * 0.5);
// SYNTHETIC: GAMEMD 0x41E270
// GLOBAL: GAMEMD 0x88A030
double DAT_0088A030 = FUN_004CADE0(DAT_0088A078 * 0.00390625);
// SYNTHETIC: GAMEMD 0x41E2A0
// GLOBAL: GAMEMD 0x88A048
double DAT_0088A048 = FUN_004CADE0((DAT_0088A078 * 2) / DAT_0088A020);
// SYNTHETIC: GAMEMD 0x41E2D0
// GLOBAL: GAMEMD 0x88A06C
int DAT_0088A06C = (int)(DAT_0088A078 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x41E300
// GLOBAL: GAMEMD 0x88A018
HeaderCellInit DAT_0088A018(0, 0);
// SYNTHETIC: GAMEMD 0x41E310
// GLOBAL: GAMEMD 0x88A038
HeaderCoordInit DAT_0088A038(0, 0, 0);
