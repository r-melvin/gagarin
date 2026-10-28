// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4CBF10
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E89B8
const double DAT_007E89B8 = 60.0;
// GLOBAL: GAMEMD 0x7E89C0 -- degrees to radians
const double DAT_007E89C0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4CBF10
// GLOBAL: GAMEMD 0x8B3BD0
double DAT_008B3BD0 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4CBF40
// GLOBAL: GAMEMD 0x8B3C20
double DAT_008B3C20 = DAT_008B3BD0 / DAT_007E89B8;
// SYNTHETIC: GAMEMD 0x4CBF60
// GLOBAL: GAMEMD 0x8B3C08
double DAT_008B3C08 = 1.0 / DAT_008B3C20;
// SYNTHETIC: GAMEMD 0x4CBF80
// GLOBAL: GAMEMD 0x8B3C00
double DAT_008B3C00 = DAT_007E89C0 * 45.0;
// SYNTHETIC: GAMEMD 0x4CBFA0
// GLOBAL: GAMEMD 0x8B3BD8
double DAT_008B3BD8 = DAT_007E89C0 * 60.0;
// SYNTHETIC: GAMEMD 0x4CBFC0
// GLOBAL: GAMEMD 0x8B3BB0
double DAT_008B3BB0 = DAT_007E89C0 * 90.0;
// SYNTHETIC: GAMEMD 0x4CBFE0
// GLOBAL: GAMEMD 0x8B3C28
int DAT_008B3C28 = (int)(FUN_004CAD50(DAT_008B3BB0 - DAT_008B3BD8) * DAT_008B3BD0 * 0.5);
// SYNTHETIC: GAMEMD 0x4CC020
// GLOBAL: GAMEMD 0x8B3BE0
double DAT_008B3BE0 = FUN_004CADE0(DAT_008B3C28 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4CC050
// GLOBAL: GAMEMD 0x8B3BF8
double DAT_008B3BF8 = FUN_004CADE0((DAT_008B3C28 * 2) / DAT_008B3BD0);
// SYNTHETIC: GAMEMD 0x4CC080
// GLOBAL: GAMEMD 0x8B3C1C
int DAT_008B3C1C = (int)(DAT_008B3C28 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4CC0B0
// GLOBAL: GAMEMD 0x8B3BC8
HeaderCellInit DAT_008B3BC8(0, 0);
// SYNTHETIC: GAMEMD 0x4CC0C0
// GLOBAL: GAMEMD 0x8B3BE8
HeaderCoordInit DAT_008B3BE8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4CC0E0
// GLOBAL: GAMEMD 0x8B3C10
HeaderCoordInit DAT_008B3C10(128, 128, 0);
