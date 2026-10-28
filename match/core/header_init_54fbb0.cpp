// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x54FBB0-0x54FDA0 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7ECEC8
const double DAT_007ECEC8 = 60.0;
// GLOBAL: GAMEMD 0x7ECED0
const double DAT_007ECED0 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x54FBB0
// GLOBAL: GAMEMD 0xABC7C0
double DAT_00ABC7C0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x54FBE0
// GLOBAL: GAMEMD 0xABC8B0
double DAT_00ABC8B0 = DAT_00ABC7C0 / DAT_007ECEC8;
// SYNTHETIC: GAMEMD 0x54FC00
// GLOBAL: GAMEMD 0xABC898
double DAT_00ABC898 = 1.0 / DAT_00ABC8B0;
// SYNTHETIC: GAMEMD 0x54FC20
// GLOBAL: GAMEMD 0xABC890
double DAT_00ABC890 = DAT_007ECED0 * 45.0;
// SYNTHETIC: GAMEMD 0x54FC40
// GLOBAL: GAMEMD 0xABC7D0
double DAT_00ABC7D0 = DAT_007ECED0 * 60.0;
// SYNTHETIC: GAMEMD 0x54FC60
// GLOBAL: GAMEMD 0xABC720
double DAT_00ABC720 = DAT_007ECED0 * 90.0;
// SYNTHETIC: GAMEMD 0x54FC80
// GLOBAL: GAMEMD 0xABC8BC
int DAT_00ABC8BC = (int)(FUN_004CAD50(DAT_00ABC720 - DAT_00ABC7D0) * DAT_00ABC7C0 * 0.5);
// SYNTHETIC: GAMEMD 0x54FCC0
// GLOBAL: GAMEMD 0xABC7D8
double DAT_00ABC7D8 = FUN_004CADE0(DAT_00ABC8BC * 0.00390625);
// SYNTHETIC: GAMEMD 0x54FCF0
// GLOBAL: GAMEMD 0xABC7F0
double DAT_00ABC7F0 = FUN_004CADE0((DAT_00ABC8BC * 2) / DAT_00ABC7C0);
// SYNTHETIC: GAMEMD 0x54FD20
// GLOBAL: GAMEMD 0xABC8AC
int DAT_00ABC8AC = (int)(DAT_00ABC8BC * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x54FD50
// GLOBAL: GAMEMD 0xABC7B8
HeaderCellInit DAT_00ABC7B8(0, 0);
// SYNTHETIC: GAMEMD 0x54FD60
// GLOBAL: GAMEMD 0xABC7E0
HeaderCoordInit DAT_00ABC7E0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x54FD80
// GLOBAL: GAMEMD 0xABC8A0
HeaderCoordInit DAT_00ABC8A0(128, 128, 0);
// SYNTHETIC: GAMEMD 0x54FDA0
// GLOBAL: GAMEMD 0xABC728
MathTblZero4 DAT_00ABC728;
