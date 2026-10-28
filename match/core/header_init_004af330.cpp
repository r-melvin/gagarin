// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4AF330
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E6230
const double DAT_007E6230 = 60.0;
// GLOBAL: GAMEMD 0x7E6238 -- degrees to radians
const double DAT_007E6238 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4AF330
// GLOBAL: GAMEMD 0x8A0778
double DAT_008A0778 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4AF360
// GLOBAL: GAMEMD 0x8A07C8
double DAT_008A07C8 = DAT_008A0778 / DAT_007E6230;
// SYNTHETIC: GAMEMD 0x4AF380
// GLOBAL: GAMEMD 0x8A07B0
double DAT_008A07B0 = 1.0 / DAT_008A07C8;
// SYNTHETIC: GAMEMD 0x4AF3A0
// GLOBAL: GAMEMD 0x8A07A8
double DAT_008A07A8 = DAT_007E6238 * 45.0;
// SYNTHETIC: GAMEMD 0x4AF3C0
// GLOBAL: GAMEMD 0x8A0780
double DAT_008A0780 = DAT_007E6238 * 60.0;
// SYNTHETIC: GAMEMD 0x4AF3E0
// GLOBAL: GAMEMD 0x8A0758
double DAT_008A0758 = DAT_007E6238 * 90.0;
// SYNTHETIC: GAMEMD 0x4AF400
// GLOBAL: GAMEMD 0x8A07D0
int DAT_008A07D0 = (int)(FUN_004CAD50(DAT_008A0758 - DAT_008A0780) * DAT_008A0778 * 0.5);
// SYNTHETIC: GAMEMD 0x4AF440
// GLOBAL: GAMEMD 0x8A0788
double DAT_008A0788 = FUN_004CADE0(DAT_008A07D0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4AF470
// GLOBAL: GAMEMD 0x8A07A0
double DAT_008A07A0 = FUN_004CADE0((DAT_008A07D0 * 2) / DAT_008A0778);
// SYNTHETIC: GAMEMD 0x4AF4A0
// GLOBAL: GAMEMD 0x8A07C4
int DAT_008A07C4 = (int)(DAT_008A07D0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4AF4D0
// GLOBAL: GAMEMD 0x8A0770
HeaderCellInit DAT_008A0770(0, 0);
// SYNTHETIC: GAMEMD 0x4AF4E0
// GLOBAL: GAMEMD 0x8A0790
HeaderCoordInit DAT_008A0790(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4AF500
// GLOBAL: GAMEMD 0x8A07B8
HeaderCoordInit DAT_008A07B8(128, 128, 0);
