// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x4B67D0
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
// GLOBAL: GAMEMD 0x7E8370
const double DAT_007E8370 = 60.0;
// GLOBAL: GAMEMD 0x7E8378 -- degrees to radians
const double DAT_007E8378 = 0.017453292519943295;

// GLOBAL: GAMEMD 0x8A08A8
extern double DAT_008A08A8;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4B6810
// GLOBAL: GAMEMD 0x8A08F8
double DAT_008A08F8 = DAT_007E8378 * 45.0;
// SYNTHETIC: GAMEMD 0x4B6830
// GLOBAL: GAMEMD 0x8A08B0
double DAT_008A08B0 = DAT_007E8378 * 60.0;
// SYNTHETIC: GAMEMD 0x4B6850
// GLOBAL: GAMEMD 0x8A0868
double DAT_008A0868 = DAT_007E8378 * 90.0;
// SYNTHETIC: GAMEMD 0x4B6870
// GLOBAL: GAMEMD 0x8A0920
int DAT_008A0920 = (int)(FUN_004CAD50(DAT_008A0868 - DAT_008A08B0) * DAT_008A08A8 * 0.5);
// SYNTHETIC: GAMEMD 0x4B68B0
// GLOBAL: GAMEMD 0x8A08B8
double DAT_008A08B8 = FUN_004CADE0(DAT_008A0920 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4B68E0
// GLOBAL: GAMEMD 0x8A08F0
double DAT_008A08F0 = FUN_004CADE0((DAT_008A0920 * 2) / DAT_008A08A8);
// SYNTHETIC: GAMEMD 0x4B6910
// GLOBAL: GAMEMD 0x8A0914
int DAT_008A0914 = (int)(DAT_008A0920 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4B6940
// GLOBAL: GAMEMD 0x8A08A0
HeaderCellInit DAT_008A08A0(0, 0);
// SYNTHETIC: GAMEMD 0x4B6950
// GLOBAL: GAMEMD 0x8A08E0
HeaderCoordInit DAT_008A08E0(0, 0, 0);
