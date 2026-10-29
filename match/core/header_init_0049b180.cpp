// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x49B1B0
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
// GLOBAL: GAMEMD 0x7E5BB0
const double DAT_007E5BB0 = 60.0;
// GLOBAL: GAMEMD 0x7E5BB8 -- degrees to radians
const double DAT_007E5BB8 = 0.017453292519943295;

// GLOBAL: GAMEMD 0x89F5A0
extern double DAT_0089F5A0;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x49B1F0
// GLOBAL: GAMEMD 0x89F5D0
double DAT_0089F5D0 = DAT_007E5BB8 * 45.0;
// SYNTHETIC: GAMEMD 0x49B210
// GLOBAL: GAMEMD 0x89F5A8
double DAT_0089F5A8 = DAT_007E5BB8 * 60.0;
// SYNTHETIC: GAMEMD 0x49B230
// GLOBAL: GAMEMD 0x89F580
double DAT_0089F580 = DAT_007E5BB8 * 90.0;
// SYNTHETIC: GAMEMD 0x49B250
// GLOBAL: GAMEMD 0x89F678
int DAT_0089F678 = (int)(FUN_004CAD50(DAT_0089F580 - DAT_0089F5A8) * DAT_0089F5A0 * 0.5);
// SYNTHETIC: GAMEMD 0x49B290
// GLOBAL: GAMEMD 0x89F5B0
double DAT_0089F5B0 = FUN_004CADE0(DAT_0089F678 * 0.00390625);
// SYNTHETIC: GAMEMD 0x49B2C0
// GLOBAL: GAMEMD 0x89F5C8
double DAT_0089F5C8 = FUN_004CADE0((DAT_0089F678 * 2) / DAT_0089F5A0);
// SYNTHETIC: GAMEMD 0x49B2F0
// GLOBAL: GAMEMD 0x89F66C
int DAT_0089F66C = (int)(DAT_0089F678 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x49B320
// GLOBAL: GAMEMD 0x89F598
HeaderCellInit DAT_0089F598(0, 0);
// SYNTHETIC: GAMEMD 0x49B330
// GLOBAL: GAMEMD 0x89F5B8
HeaderCoordInit DAT_0089F5B8(0, 0, 0);
