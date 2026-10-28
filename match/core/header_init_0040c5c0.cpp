// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40C5C0
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
// GLOBAL: GAMEMD 0x7E18A8
const double DAT_007E18A8 = 60.0;
// GLOBAL: GAMEMD 0x7E18B0 -- degrees to radians
const double DAT_007E18B0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x40C590
// GLOBAL: GAMEMD 0x87F6F8
double DAT_0087F6F8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x40C5C0
// GLOBAL: GAMEMD 0x87F748
double DAT_0087F748 = DAT_0087F6F8 / DAT_007E18A8;
// SYNTHETIC: GAMEMD 0x40C5E0
// GLOBAL: GAMEMD 0x87F730
double DAT_0087F730 = 1.0 / DAT_0087F748;
// SYNTHETIC: GAMEMD 0x40C600
// GLOBAL: GAMEMD 0x87F728
double DAT_0087F728 = DAT_007E18B0 * 45.0;
// SYNTHETIC: GAMEMD 0x40C620
// GLOBAL: GAMEMD 0x87F700
double DAT_0087F700 = DAT_007E18B0 * 60.0;
// SYNTHETIC: GAMEMD 0x40C640
// GLOBAL: GAMEMD 0x87F6D8
double DAT_0087F6D8 = DAT_007E18B0 * 90.0;
// SYNTHETIC: GAMEMD 0x40C660
// GLOBAL: GAMEMD 0x87F768
int DAT_0087F768 = (int)(FUN_004CAD50(DAT_0087F6D8 - DAT_0087F700) * DAT_0087F6F8 * 0.5);
// SYNTHETIC: GAMEMD 0x40C6A0
// GLOBAL: GAMEMD 0x87F708
double DAT_0087F708 = FUN_004CADE0(DAT_0087F768 * 0.00390625);
// SYNTHETIC: GAMEMD 0x40C6D0
// GLOBAL: GAMEMD 0x87F720
double DAT_0087F720 = FUN_004CADE0((DAT_0087F768 * 2) / DAT_0087F6F8);
// SYNTHETIC: GAMEMD 0x40C700
// GLOBAL: GAMEMD 0x87F744
int DAT_0087F744 = (int)(DAT_0087F768 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x40C730
// GLOBAL: GAMEMD 0x87F6F0
HeaderCellInit DAT_0087F6F0(0, 0);
// SYNTHETIC: GAMEMD 0x40C740
// GLOBAL: GAMEMD 0x87F710
HeaderCoordInit DAT_0087F710(0, 0, 0);
// SYNTHETIC: GAMEMD 0x40C760
// GLOBAL: GAMEMD 0x87F738
HeaderCoordInit DAT_0087F738(128, 128, 0);
