// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40FF90
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
// GLOBAL: GAMEMD 0x7E1F10
const double DAT_007E1F10 = 60.0;
// GLOBAL: GAMEMD 0x7E1F18 -- degrees to radians
const double DAT_007E1F18 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x40FF60
// GLOBAL: GAMEMD 0x887668
double DAT_00887668 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x40FF90
// GLOBAL: GAMEMD 0x8876B8
double DAT_008876B8 = DAT_00887668 / DAT_007E1F10;
// SYNTHETIC: GAMEMD 0x40FFB0
// GLOBAL: GAMEMD 0x8876A0
double DAT_008876A0 = 1.0 / DAT_008876B8;
// SYNTHETIC: GAMEMD 0x40FFD0
// GLOBAL: GAMEMD 0x887698
double DAT_00887698 = DAT_007E1F18 * 45.0;
// SYNTHETIC: GAMEMD 0x40FFF0
// GLOBAL: GAMEMD 0x887670
double DAT_00887670 = DAT_007E1F18 * 60.0;
// SYNTHETIC: GAMEMD 0x410010
// GLOBAL: GAMEMD 0x887648
double DAT_00887648 = DAT_007E1F18 * 90.0;
// SYNTHETIC: GAMEMD 0x410030
// GLOBAL: GAMEMD 0x8876C0
int DAT_008876C0 = (int)(FUN_004CAD50(DAT_00887648 - DAT_00887670) * DAT_00887668 * 0.5);
// SYNTHETIC: GAMEMD 0x410070
// GLOBAL: GAMEMD 0x887678
double DAT_00887678 = FUN_004CADE0(DAT_008876C0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4100A0
// GLOBAL: GAMEMD 0x887690
double DAT_00887690 = FUN_004CADE0((DAT_008876C0 * 2) / DAT_00887668);
// SYNTHETIC: GAMEMD 0x4100D0
// GLOBAL: GAMEMD 0x8876B4
int DAT_008876B4 = (int)(DAT_008876C0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x410100
// GLOBAL: GAMEMD 0x887660
HeaderCellInit DAT_00887660(0, 0);
// SYNTHETIC: GAMEMD 0x410110
// GLOBAL: GAMEMD 0x887680
HeaderCoordInit DAT_00887680(0, 0, 0);
// SYNTHETIC: GAMEMD 0x410130
// GLOBAL: GAMEMD 0x8876A8
HeaderCoordInit DAT_008876A8(128, 128, 0);
