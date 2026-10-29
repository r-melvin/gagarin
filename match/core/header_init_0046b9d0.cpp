// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x46B9D0
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
// GLOBAL: GAMEMD 0x7E4908
const double DAT_007E4908 = 60.0;
// GLOBAL: GAMEMD 0x7E4910 -- degrees to radians
const double DAT_007E4910 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x46B9D0
// GLOBAL: GAMEMD 0x89DE98
double DAT_0089DE98 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x46BA00
// GLOBAL: GAMEMD 0x89DEE8
double DAT_0089DEE8 = DAT_0089DE98 / DAT_007E4908;
// SYNTHETIC: GAMEMD 0x46BA20
// GLOBAL: GAMEMD 0x89DED0
double DAT_0089DED0 = 1.0 / DAT_0089DEE8;
// SYNTHETIC: GAMEMD 0x46BA40
// GLOBAL: GAMEMD 0x89DEC8
double DAT_0089DEC8 = DAT_007E4910 * 45.0;
// SYNTHETIC: GAMEMD 0x46BA60
// GLOBAL: GAMEMD 0x89DEA0
double DAT_0089DEA0 = DAT_007E4910 * 60.0;
// SYNTHETIC: GAMEMD 0x46BA80
// GLOBAL: GAMEMD 0x89DE78
double DAT_0089DE78 = DAT_007E4910 * 90.0;
// SYNTHETIC: GAMEMD 0x46BAA0
// GLOBAL: GAMEMD 0x89DEF0
int DAT_0089DEF0 = (int)(FUN_004CAD50(DAT_0089DE78 - DAT_0089DEA0) * DAT_0089DE98 * 0.5);
// SYNTHETIC: GAMEMD 0x46BAE0
// GLOBAL: GAMEMD 0x89DEA8
double DAT_0089DEA8 = FUN_004CADE0(DAT_0089DEF0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x46BB10
// GLOBAL: GAMEMD 0x89DEC0
double DAT_0089DEC0 = FUN_004CADE0((DAT_0089DEF0 * 2) / DAT_0089DE98);
// SYNTHETIC: GAMEMD 0x46BB40
// GLOBAL: GAMEMD 0x89DEE4
int DAT_0089DEE4 = (int)(DAT_0089DEF0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x46BB70
// GLOBAL: GAMEMD 0x89DE90
HeaderCellInit DAT_0089DE90(0, 0);
// SYNTHETIC: GAMEMD 0x46BB80
// GLOBAL: GAMEMD 0x89DEB0
HeaderCoordInit DAT_0089DEB0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x46BBA0
// GLOBAL: GAMEMD 0x89DED8
HeaderCoordInit DAT_0089DED8(128, 128, 0);
