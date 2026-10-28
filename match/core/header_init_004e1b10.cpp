// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4E1B10
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
// GLOBAL: GAMEMD 0x7E9370
const double DAT_007E9370 = 60.0;
// GLOBAL: GAMEMD 0x7E9378 -- degrees to radians
const double DAT_007E9378 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4E1B10
// GLOBAL: GAMEMD 0x8B3EB8
double DAT_008B3EB8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4E1B80
// GLOBAL: GAMEMD 0x8B3EE8
double DAT_008B3EE8 = DAT_007E9378 * 45.0;
// SYNTHETIC: GAMEMD 0x4E1BA0
// GLOBAL: GAMEMD 0x8B3EC0
double DAT_008B3EC0 = DAT_007E9378 * 60.0;
// SYNTHETIC: GAMEMD 0x4E1BC0
// GLOBAL: GAMEMD 0x8B3E98
double DAT_008B3E98 = DAT_007E9378 * 90.0;
// SYNTHETIC: GAMEMD 0x4E1BE0
// GLOBAL: GAMEMD 0x8B3F10
int DAT_008B3F10 = (int)(FUN_004CAD50(DAT_008B3E98 - DAT_008B3EC0) * DAT_008B3EB8 * 0.5);
// SYNTHETIC: GAMEMD 0x4E1C20
// GLOBAL: GAMEMD 0x8B3EC8
double DAT_008B3EC8 = FUN_004CADE0(DAT_008B3F10 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4E1C50
// GLOBAL: GAMEMD 0x8B3EE0
double DAT_008B3EE0 = FUN_004CADE0((DAT_008B3F10 * 2) / DAT_008B3EB8);
// SYNTHETIC: GAMEMD 0x4E1C80
// GLOBAL: GAMEMD 0x8B3F04
int DAT_008B3F04 = (int)(DAT_008B3F10 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4E1CB0
// GLOBAL: GAMEMD 0x8B3EB0
HeaderCellInit DAT_008B3EB0(0, 0);
// SYNTHETIC: GAMEMD 0x4E1CC0
// GLOBAL: GAMEMD 0x8B3ED0
HeaderCoordInit DAT_008B3ED0(0, 0, 0);
