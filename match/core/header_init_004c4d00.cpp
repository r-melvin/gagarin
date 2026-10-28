// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4C4D00
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
// GLOBAL: GAMEMD 0x7E8718
const double DAT_007E8718 = 60.0;
// GLOBAL: GAMEMD 0x7E8720 -- degrees to radians
const double DAT_007E8720 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4C4D00
// GLOBAL: GAMEMD 0x8A3798
double DAT_008A3798 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4C4D70
// GLOBAL: GAMEMD 0x8A37E8
double DAT_008A37E8 = DAT_007E8720 * 45.0;
// SYNTHETIC: GAMEMD 0x4C4D90
// GLOBAL: GAMEMD 0x8A37C0
double DAT_008A37C0 = DAT_007E8720 * 60.0;
// SYNTHETIC: GAMEMD 0x4C4DB0
// GLOBAL: GAMEMD 0x8A3788
double DAT_008A3788 = DAT_007E8720 * 90.0;
// SYNTHETIC: GAMEMD 0x4C4DD0
// GLOBAL: GAMEMD 0x8A3810
int DAT_008A3810 = (int)(FUN_004CAD50(DAT_008A3788 - DAT_008A37C0) * DAT_008A3798 * 0.5);
// SYNTHETIC: GAMEMD 0x4C4E10
// GLOBAL: GAMEMD 0x8A37C8
double DAT_008A37C8 = FUN_004CADE0(DAT_008A3810 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4C4E40
// GLOBAL: GAMEMD 0x8A37E0
double DAT_008A37E0 = FUN_004CADE0((DAT_008A3810 * 2) / DAT_008A3798);
// SYNTHETIC: GAMEMD 0x4C4E70
// GLOBAL: GAMEMD 0x8A3804
int DAT_008A3804 = (int)(DAT_008A3810 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4C4EA0
// GLOBAL: GAMEMD 0x8A3790
HeaderCellInit DAT_008A3790(0, 0);
// SYNTHETIC: GAMEMD 0x4C4EB0
// GLOBAL: GAMEMD 0x8A37D0
HeaderCoordInit DAT_008A37D0(0, 0, 0);
