// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x41D070
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
// GLOBAL: GAMEMD 0x7E2928
const double DAT_007E2928 = 60.0;
// GLOBAL: GAMEMD 0x7E2930 -- degrees to radians
const double DAT_007E2930 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x41D070
// GLOBAL: GAMEMD 0x889F88
double DAT_00889F88 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x41D0E0
// GLOBAL: GAMEMD 0x889FD0
double DAT_00889FD0 = DAT_007E2930 * 45.0;
// SYNTHETIC: GAMEMD 0x41D100
// GLOBAL: GAMEMD 0x889F90
double DAT_00889F90 = DAT_007E2930 * 60.0;
// SYNTHETIC: GAMEMD 0x41D120
// GLOBAL: GAMEMD 0x889F68
double DAT_00889F68 = DAT_007E2930 * 90.0;
// SYNTHETIC: GAMEMD 0x41D140
// GLOBAL: GAMEMD 0x889FF8
int DAT_00889FF8 = (int)(FUN_004CAD50(DAT_00889F68 - DAT_00889F90) * DAT_00889F88 * 0.5);
// SYNTHETIC: GAMEMD 0x41D180
// GLOBAL: GAMEMD 0x889F98
double DAT_00889F98 = FUN_004CADE0(DAT_00889FF8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x41D1B0
// GLOBAL: GAMEMD 0x889FB0
double DAT_00889FB0 = FUN_004CADE0((DAT_00889FF8 * 2) / DAT_00889F88);
// SYNTHETIC: GAMEMD 0x41D1E0
// GLOBAL: GAMEMD 0x889FEC
int DAT_00889FEC = (int)(DAT_00889FF8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x41D210
// GLOBAL: GAMEMD 0x889F80
HeaderCellInit DAT_00889F80(0, 0);
// SYNTHETIC: GAMEMD 0x41D220
// GLOBAL: GAMEMD 0x889FA0
HeaderCoordInit DAT_00889FA0(0, 0, 0);
