// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x45AFA0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E4530
const double DAT_007E4530 = 60.0;
// GLOBAL: GAMEMD 0x7E4538 -- degrees to radians
const double DAT_007E4538 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x45AFA0
// GLOBAL: GAMEMD 0x89C8B8
double DAT_0089C8B8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x45B010
// GLOBAL: GAMEMD 0x89C8F0
double DAT_0089C8F0 = DAT_007E4538 * 45.0;
// SYNTHETIC: GAMEMD 0x45B030
// GLOBAL: GAMEMD 0x89C8C0
double DAT_0089C8C0 = DAT_007E4538 * 60.0;
// SYNTHETIC: GAMEMD 0x45B050
// GLOBAL: GAMEMD 0x89C898
double DAT_0089C898 = DAT_007E4538 * 90.0;
// SYNTHETIC: GAMEMD 0x45B070
// GLOBAL: GAMEMD 0x89DDB8
int DAT_0089DDB8 = (int)(FUN_004CAD50(DAT_0089C898 - DAT_0089C8C0) * DAT_0089C8B8 * 0.5);
// SYNTHETIC: GAMEMD 0x45B0B0
// GLOBAL: GAMEMD 0x89C8C8
double DAT_0089C8C8 = FUN_004CADE0(DAT_0089DDB8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x45B0E0
// GLOBAL: GAMEMD 0x89C8E0
double DAT_0089C8E0 = FUN_004CADE0((DAT_0089DDB8 * 2) / DAT_0089C8B8);
// SYNTHETIC: GAMEMD 0x45B110
// GLOBAL: GAMEMD 0x89D35C
int DAT_0089D35C = (int)(DAT_0089DDB8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x45B140
// GLOBAL: GAMEMD 0x89C8B0
HeaderCellInit DAT_0089C8B0(0, 0);
// SYNTHETIC: GAMEMD 0x45B150
// GLOBAL: GAMEMD 0x89C8D0
HeaderCoordInit DAT_0089C8D0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x45B170
// GLOBAL: GAMEMD 0x89D350
HeaderCoordInit DAT_0089D350(128, 128, 0);
