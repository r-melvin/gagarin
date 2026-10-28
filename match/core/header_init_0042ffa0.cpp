// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x42FFA0
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
// GLOBAL: GAMEMD 0x7E3A18
const double DAT_007E3A18 = 60.0;
// GLOBAL: GAMEMD 0x7E3A20 -- degrees to radians
const double DAT_007E3A20 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x42FFA0
// GLOBAL: GAMEMD 0x89C398
double DAT_0089C398 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x430010
// GLOBAL: GAMEMD 0x89C448
double DAT_0089C448 = DAT_007E3A20 * 45.0;
// SYNTHETIC: GAMEMD 0x430030
// GLOBAL: GAMEMD 0x89C3A0
double DAT_0089C3A0 = DAT_007E3A20 * 60.0;
// SYNTHETIC: GAMEMD 0x430050
// GLOBAL: GAMEMD 0x89C378
double DAT_0089C378 = DAT_007E3A20 * 90.0;
// SYNTHETIC: GAMEMD 0x430070
// GLOBAL: GAMEMD 0x89C470
int DAT_0089C470 = (int)(FUN_004CAD50(DAT_0089C378 - DAT_0089C3A0) * DAT_0089C398 * 0.5);
// SYNTHETIC: GAMEMD 0x4300B0
// GLOBAL: GAMEMD 0x89C3A8
double DAT_0089C3A8 = FUN_004CADE0(DAT_0089C470 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4300E0
// GLOBAL: GAMEMD 0x89C440
double DAT_0089C440 = FUN_004CADE0((DAT_0089C470 * 2) / DAT_0089C398);
// SYNTHETIC: GAMEMD 0x430110
// GLOBAL: GAMEMD 0x89C464
int DAT_0089C464 = (int)(DAT_0089C470 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x430140
// GLOBAL: GAMEMD 0x89C390
HeaderCellInit DAT_0089C390(0, 0);
// SYNTHETIC: GAMEMD 0x430150
// GLOBAL: GAMEMD 0x89C430
HeaderCoordInit DAT_0089C430(0, 0, 0);
