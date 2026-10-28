// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x47B150
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E4EA8
const double DAT_007E4EA8 = 60.0;
// GLOBAL: GAMEMD 0x7E4EB0 -- degrees to radians
const double DAT_007E4EB0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x47B150
// GLOBAL: GAMEMD 0x89E750
double DAT_0089E750 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x47B180
// GLOBAL: GAMEMD 0x89E7B8
double DAT_0089E7B8 = DAT_0089E750 / DAT_007E4EA8;
// SYNTHETIC: GAMEMD 0x47B1A0
// GLOBAL: GAMEMD 0x89E7A0
double DAT_0089E7A0 = 1.0 / DAT_0089E7B8;
// SYNTHETIC: GAMEMD 0x47B1C0
// GLOBAL: GAMEMD 0x89E798
double DAT_0089E798 = DAT_007E4EB0 * 45.0;
// SYNTHETIC: GAMEMD 0x47B1E0
// GLOBAL: GAMEMD 0x89E758
double DAT_0089E758 = DAT_007E4EB0 * 60.0;
// SYNTHETIC: GAMEMD 0x47B200
// GLOBAL: GAMEMD 0x89E728
double DAT_0089E728 = DAT_007E4EB0 * 90.0;
// SYNTHETIC: GAMEMD 0x47B220
// GLOBAL: GAMEMD 0x89E7C0
int DAT_0089E7C0 = (int)(FUN_004CAD50(DAT_0089E728 - DAT_0089E758) * DAT_0089E750 * 0.5);
// SYNTHETIC: GAMEMD 0x47B260
// GLOBAL: GAMEMD 0x89E768
double DAT_0089E768 = FUN_004CADE0(DAT_0089E7C0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x47B290
// GLOBAL: GAMEMD 0x89E788
double DAT_0089E788 = FUN_004CADE0((DAT_0089E7C0 * 2) / DAT_0089E750);
// SYNTHETIC: GAMEMD 0x47B2C0
// GLOBAL: GAMEMD 0x89E7B4
int DAT_0089E7B4 = (int)(DAT_0089E7C0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x47B2F0
// GLOBAL: GAMEMD 0x89E748
HeaderCellInit DAT_0089E748(0, 0);
// SYNTHETIC: GAMEMD 0x47B300
// GLOBAL: GAMEMD 0x89E778
HeaderCoordInit DAT_0089E778(0, 0, 0);
// SYNTHETIC: GAMEMD 0x47B320
// GLOBAL: GAMEMD 0x89E7A8
HeaderCoordInit DAT_0089E7A8(128, 128, 0);
