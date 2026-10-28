// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4A8440
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
// GLOBAL: GAMEMD 0x7E6018
const double DAT_007E6018 = 60.0;
// GLOBAL: GAMEMD 0x7E6020 -- degrees to radians
const double DAT_007E6020 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4A8440
// GLOBAL: GAMEMD 0x8A0400
double DAT_008A0400 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4A84B0
// GLOBAL: GAMEMD 0x8A0620
double DAT_008A0620 = DAT_007E6020 * 45.0;
// SYNTHETIC: GAMEMD 0x4A84D0
// GLOBAL: GAMEMD 0x8A0408
double DAT_008A0408 = DAT_007E6020 * 60.0;
// SYNTHETIC: GAMEMD 0x4A84F0
// GLOBAL: GAMEMD 0x8A03D8
double DAT_008A03D8 = DAT_007E6020 * 90.0;
// SYNTHETIC: GAMEMD 0x4A8510
// GLOBAL: GAMEMD 0x8A0740
int DAT_008A0740 = (int)(FUN_004CAD50(DAT_008A03D8 - DAT_008A0408) * DAT_008A0400 * 0.5);
// SYNTHETIC: GAMEMD 0x4A8550
// GLOBAL: GAMEMD 0x8A0410
double DAT_008A0410 = FUN_004CADE0(DAT_008A0740 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4A8580
// GLOBAL: GAMEMD 0x8A0610
double DAT_008A0610 = FUN_004CADE0((DAT_008A0740 * 2) / DAT_008A0400);
// SYNTHETIC: GAMEMD 0x4A85B0
// GLOBAL: GAMEMD 0x8A0730
int DAT_008A0730 = (int)(DAT_008A0740 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4A85E0
// GLOBAL: GAMEMD 0x8A03F8
HeaderCellInit DAT_008A03F8(0, 0);
// SYNTHETIC: GAMEMD 0x4A85F0
// GLOBAL: GAMEMD 0x8A0600
HeaderCoordInit DAT_008A0600(0, 0, 0);
