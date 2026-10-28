// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x54AA30-0x54AC20 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7ECD30
const double DAT_007ECD30 = 60.0;
// GLOBAL: GAMEMD 0x7ECD38
const double DAT_007ECD38 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x54AA30
// GLOBAL: GAMEMD 0xABC590
double DAT_00ABC590 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x54AA60
// GLOBAL: GAMEMD 0xABC5E0
double DAT_00ABC5E0 = DAT_00ABC590 / DAT_007ECD30;
// SYNTHETIC: GAMEMD 0x54AA80
// GLOBAL: GAMEMD 0xABC5C8
double DAT_00ABC5C8 = 1.0 / DAT_00ABC5E0;
// SYNTHETIC: GAMEMD 0x54AAA0
// GLOBAL: GAMEMD 0xABC5C0
double DAT_00ABC5C0 = DAT_007ECD38 * 45.0;
// SYNTHETIC: GAMEMD 0x54AAC0
// GLOBAL: GAMEMD 0xABC598
double DAT_00ABC598 = DAT_007ECD38 * 60.0;
// SYNTHETIC: GAMEMD 0x54AAE0
// GLOBAL: GAMEMD 0xABC570
double DAT_00ABC570 = DAT_007ECD38 * 90.0;
// SYNTHETIC: GAMEMD 0x54AB00
// GLOBAL: GAMEMD 0xABC5E8
int DAT_00ABC5E8 = (int)(FUN_004CAD50(DAT_00ABC570 - DAT_00ABC598) * DAT_00ABC590 * 0.5);
// SYNTHETIC: GAMEMD 0x54AB40
// GLOBAL: GAMEMD 0xABC5A0
double DAT_00ABC5A0 = FUN_004CADE0(DAT_00ABC5E8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x54AB70
// GLOBAL: GAMEMD 0xABC5B8
double DAT_00ABC5B8 = FUN_004CADE0((DAT_00ABC5E8 * 2) / DAT_00ABC590);
// SYNTHETIC: GAMEMD 0x54ABA0
// GLOBAL: GAMEMD 0xABC5DC
int DAT_00ABC5DC = (int)(DAT_00ABC5E8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x54ABD0
// GLOBAL: GAMEMD 0xABC588
HeaderCellInit DAT_00ABC588(0, 0);
// SYNTHETIC: GAMEMD 0x54ABE0
// GLOBAL: GAMEMD 0xABC5A8
HeaderCoordInit DAT_00ABC5A8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x54AC00
// GLOBAL: GAMEMD 0xABC5D0
HeaderCoordInit DAT_00ABC5D0(128, 128, 0);
// SYNTHETIC: GAMEMD 0x54AC20
// GLOBAL: GAMEMD 0xABC578
MathTblZero4 DAT_00ABC578;
