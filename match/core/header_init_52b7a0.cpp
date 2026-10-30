// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x52B7A0-0x52B990 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"
#include "pk_key_pipes.h"

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
// GLOBAL: GAMEMD 0x7EB7F8
const double DAT_007EB7F8 = 60.0;
// GLOBAL: GAMEMD 0x7EB800
const double DAT_007EB800 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x52B7A0
// GLOBAL: GAMEMD 0xA8F2E8
MathTblZero4 DAT_00A8F2E8;
// SYNTHETIC: GAMEMD 0x52B7C0
// GLOBAL: GAMEMD 0xA8F418
double DAT_00A8F418 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x52B7F0
// GLOBAL: GAMEMD 0xA8F778
double DAT_00A8F778 = DAT_00A8F418 / DAT_007EB7F8;
// SYNTHETIC: GAMEMD 0x52B810
// GLOBAL: GAMEMD 0xA8F760
double DAT_00A8F760 = 1.0 / DAT_00A8F778;
// SYNTHETIC: GAMEMD 0x52B830
// GLOBAL: GAMEMD 0xA8F758
double DAT_00A8F758 = DAT_007EB800 * 45.0;
// SYNTHETIC: GAMEMD 0x52B850
// GLOBAL: GAMEMD 0xA8F5A0
double DAT_00A8F5A0 = DAT_007EB800 * 60.0;
// SYNTHETIC: GAMEMD 0x52B870
// GLOBAL: GAMEMD 0xA8F2E0
double DAT_00A8F2E0 = DAT_007EB800 * 90.0;
// SYNTHETIC: GAMEMD 0x52B890
// GLOBAL: GAMEMD 0xA8F780
int DAT_00A8F780 = (int)(FUN_004CAD50(DAT_00A8F2E0 - DAT_00A8F5A0) * DAT_00A8F418 * 0.5);
// SYNTHETIC: GAMEMD 0x52B8D0
// GLOBAL: GAMEMD 0xA8F5A8
double DAT_00A8F5A8 = FUN_004CADE0(DAT_00A8F780 * 0.00390625);
// SYNTHETIC: GAMEMD 0x52B900
// GLOBAL: GAMEMD 0xA8F648
double DAT_00A8F648 = FUN_004CADE0((DAT_00A8F780 * 2) / DAT_00A8F418);
// SYNTHETIC: GAMEMD 0x52B930
// GLOBAL: GAMEMD 0xA8F774
int DAT_00A8F774 = (int)(DAT_00A8F780 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x52B960
// GLOBAL: GAMEMD 0xA8F2F8
HeaderCellInit DAT_00A8F2F8(0, 0);
// SYNTHETIC: GAMEMD 0x52B970
// GLOBAL: GAMEMD 0xA8F638
HeaderCoordInit DAT_00A8F638(0, 0, 0);
// SYNTHETIC: GAMEMD 0x52B990
// GLOBAL: GAMEMD 0xA8F768
HeaderCoordInit DAT_00A8F768(128, 128, 0);
// SYNTHETIC: GAMEMD 0x538C10 -- a 64-word big integer, filled with 0 by its constructor (0x5C6940).
// GLOBAL: GAMEMD 0xA8F7F8
BigInt_00632740 DAT_00A8F7F8;
