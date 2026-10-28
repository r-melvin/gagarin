// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x46D120
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
// GLOBAL: GAMEMD 0x7E4A98
const double DAT_007E4A98 = 60.0;
// GLOBAL: GAMEMD 0x7E4AA0 -- degrees to radians
const double DAT_007E4AA0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x46D120
// GLOBAL: GAMEMD 0x89DFA8
double DAT_0089DFA8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x46D190
// GLOBAL: GAMEMD 0x89E010
double DAT_0089E010 = DAT_007E4AA0 * 45.0;
// SYNTHETIC: GAMEMD 0x46D1B0
// GLOBAL: GAMEMD 0x89DFB0
double DAT_0089DFB0 = DAT_007E4AA0 * 60.0;
// SYNTHETIC: GAMEMD 0x46D1D0
// GLOBAL: GAMEMD 0x89DF68
double DAT_0089DF68 = DAT_007E4AA0 * 90.0;
// SYNTHETIC: GAMEMD 0x46D1F0
// GLOBAL: GAMEMD 0x89E048
int DAT_0089E048 = (int)(FUN_004CAD50(DAT_0089DF68 - DAT_0089DFB0) * DAT_0089DFA8 * 0.5);
// SYNTHETIC: GAMEMD 0x46D230
// GLOBAL: GAMEMD 0x89DFB8
double DAT_0089DFB8 = FUN_004CADE0(DAT_0089E048 * 0.00390625);
// SYNTHETIC: GAMEMD 0x46D260
// GLOBAL: GAMEMD 0x89DFD8
double DAT_0089DFD8 = FUN_004CADE0((DAT_0089E048 * 2) / DAT_0089DFA8);
// SYNTHETIC: GAMEMD 0x46D290
// GLOBAL: GAMEMD 0x89E034
int DAT_0089E034 = (int)(DAT_0089E048 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x46D2C0
// GLOBAL: GAMEMD 0x89DFA0
HeaderCellInit DAT_0089DFA0(0, 0);
// SYNTHETIC: GAMEMD 0x46D2D0
// GLOBAL: GAMEMD 0x89DFC8
HeaderCoordInit DAT_0089DFC8(0, 0, 0);
