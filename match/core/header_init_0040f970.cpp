// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40F970
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
// GLOBAL: GAMEMD 0x7E1EC0
const double DAT_007E1EC0 = 60.0;
// GLOBAL: GAMEMD 0x7E1EC8 -- degrees to radians
const double DAT_007E1EC8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x40F940
// GLOBAL: GAMEMD 0x887518
double DAT_00887518 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x40F970
// GLOBAL: GAMEMD 0x887588
double DAT_00887588 = DAT_00887518 / DAT_007E1EC0;
// SYNTHETIC: GAMEMD 0x40F990
// GLOBAL: GAMEMD 0x887550
double DAT_00887550 = 1.0 / DAT_00887588;
// SYNTHETIC: GAMEMD 0x40F9B0
// GLOBAL: GAMEMD 0x887548
double DAT_00887548 = DAT_007E1EC8 * 45.0;
// SYNTHETIC: GAMEMD 0x40F9D0
// GLOBAL: GAMEMD 0x887520
double DAT_00887520 = DAT_007E1EC8 * 60.0;
// SYNTHETIC: GAMEMD 0x40F9F0
// GLOBAL: GAMEMD 0x887508
double DAT_00887508 = DAT_007E1EC8 * 90.0;
// SYNTHETIC: GAMEMD 0x40FA10
// GLOBAL: GAMEMD 0x887590
int DAT_00887590 = (int)(FUN_004CAD50(DAT_00887508 - DAT_00887520) * DAT_00887518 * 0.5);
// SYNTHETIC: GAMEMD 0x40FA50
// GLOBAL: GAMEMD 0x887528
double DAT_00887528 = FUN_004CADE0(DAT_00887590 * 0.00390625);
// SYNTHETIC: GAMEMD 0x40FA80
// GLOBAL: GAMEMD 0x887540
double DAT_00887540 = FUN_004CADE0((DAT_00887590 * 2) / DAT_00887518);
// SYNTHETIC: GAMEMD 0x40FAB0
// GLOBAL: GAMEMD 0x887580
int DAT_00887580 = (int)(DAT_00887590 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x40FAE0
// GLOBAL: GAMEMD 0x887510
HeaderCellInit DAT_00887510(0, 0);
// SYNTHETIC: GAMEMD 0x40FAF0
// GLOBAL: GAMEMD 0x887530
HeaderCoordInit DAT_00887530(0, 0, 0);
// SYNTHETIC: GAMEMD 0x40FB10
// GLOBAL: GAMEMD 0x887558
HeaderCoordInit DAT_00887558(128, 128, 0);
