// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x41C6A0
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
// GLOBAL: GAMEMD 0x7E2828
const double DAT_007E2828 = 60.0;
// GLOBAL: GAMEMD 0x7E2830 -- degrees to radians
const double DAT_007E2830 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x41C6A0
// GLOBAL: GAMEMD 0x889EF0
double DAT_00889EF0 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x41C710
// GLOBAL: GAMEMD 0x889F28
double DAT_00889F28 = DAT_007E2830 * 45.0;
// SYNTHETIC: GAMEMD 0x41C730
// GLOBAL: GAMEMD 0x889EF8
double DAT_00889EF8 = DAT_007E2830 * 60.0;
// SYNTHETIC: GAMEMD 0x41C750
// GLOBAL: GAMEMD 0x889ED0
double DAT_00889ED0 = DAT_007E2830 * 90.0;
// SYNTHETIC: GAMEMD 0x41C770
// GLOBAL: GAMEMD 0x889F58
int DAT_00889F58 = (int)(FUN_004CAD50(DAT_00889ED0 - DAT_00889EF8) * DAT_00889EF0 * 0.5);
// SYNTHETIC: GAMEMD 0x41C7B0
// GLOBAL: GAMEMD 0x889F00
double DAT_00889F00 = FUN_004CADE0(DAT_00889F58 * 0.00390625);
// SYNTHETIC: GAMEMD 0x41C7E0
// GLOBAL: GAMEMD 0x889F18
double DAT_00889F18 = FUN_004CADE0((DAT_00889F58 * 2) / DAT_00889EF0);
// SYNTHETIC: GAMEMD 0x41C810
// GLOBAL: GAMEMD 0x889F4C
int DAT_00889F4C = (int)(DAT_00889F58 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x41C840
// GLOBAL: GAMEMD 0x889EE8
HeaderCellInit DAT_00889EE8(0, 0);
// SYNTHETIC: GAMEMD 0x41C850
// GLOBAL: GAMEMD 0x889F08
HeaderCoordInit DAT_00889F08(0, 0, 0);
