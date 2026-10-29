// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x53F220-0x53F410 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
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
// GLOBAL: GAMEMD 0x7EC0B8
const double DAT_007EC0B8 = 60.0;
// GLOBAL: GAMEMD 0x7EC0C0
const double DAT_007EC0C0 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x53F220
// GLOBAL: GAMEMD 0xAA0510
MathTblZero4 DAT_00AA0510;
// SYNTHETIC: GAMEMD 0x53F240
// GLOBAL: GAMEMD 0xAA0528
double DAT_00AA0528 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x53F270
// GLOBAL: GAMEMD 0xAA0598
double DAT_00AA0598 = DAT_00AA0528 / DAT_007EC0B8;
// SYNTHETIC: GAMEMD 0x53F290
// GLOBAL: GAMEMD 0xAA0580
double DAT_00AA0580 = 1.0 / DAT_00AA0598;
// SYNTHETIC: GAMEMD 0x53F2B0
// GLOBAL: GAMEMD 0xAA0570
double DAT_00AA0570 = DAT_007EC0C0 * 45.0;
// SYNTHETIC: GAMEMD 0x53F2D0
// GLOBAL: GAMEMD 0xAA0538
double DAT_00AA0538 = DAT_007EC0C0 * 60.0;
// SYNTHETIC: GAMEMD 0x53F2F0
// GLOBAL: GAMEMD 0xAA0500
double DAT_00AA0500 = DAT_007EC0C0 * 90.0;
// SYNTHETIC: GAMEMD 0x53F310
// GLOBAL: GAMEMD 0xAA05A0
int DAT_00AA05A0 = (int)(FUN_004CAD50(DAT_00AA0500 - DAT_00AA0538) * DAT_00AA0528 * 0.5);
// SYNTHETIC: GAMEMD 0x53F350
// GLOBAL: GAMEMD 0xAA0540
double DAT_00AA0540 = FUN_004CADE0(DAT_00AA05A0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x53F380
// GLOBAL: GAMEMD 0xAA0560
double DAT_00AA0560 = FUN_004CADE0((DAT_00AA05A0 * 2) / DAT_00AA0528);
// SYNTHETIC: GAMEMD 0x53F3B0
// GLOBAL: GAMEMD 0xAA0594
int DAT_00AA0594 = (int)(DAT_00AA05A0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x53F3E0
// GLOBAL: GAMEMD 0xAA0520
HeaderCellInit DAT_00AA0520(0, 0);
// SYNTHETIC: GAMEMD 0x53F3F0
// GLOBAL: GAMEMD 0xAA0550
HeaderCoordInit DAT_00AA0550(0, 0, 0);
// SYNTHETIC: GAMEMD 0x53F410
// GLOBAL: GAMEMD 0xAA0588
HeaderCoordInit DAT_00AA0588(128, 128, 0);
