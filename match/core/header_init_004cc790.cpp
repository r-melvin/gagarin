// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4CC790
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E89C8
const double DAT_007E89C8 = 60.0;
// GLOBAL: GAMEMD 0x7E89D0 -- degrees to radians
const double DAT_007E89D0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4CC790
// GLOBAL: GAMEMD 0x8B3C60
double DAT_008B3C60 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4CC800
// GLOBAL: GAMEMD 0x8B3C90
double DAT_008B3C90 = DAT_007E89D0 * 45.0;
// SYNTHETIC: GAMEMD 0x4CC820
// GLOBAL: GAMEMD 0x8B3C68
double DAT_008B3C68 = DAT_007E89D0 * 60.0;
// SYNTHETIC: GAMEMD 0x4CC840
// GLOBAL: GAMEMD 0x8B3C40
double DAT_008B3C40 = DAT_007E89D0 * 90.0;
// SYNTHETIC: GAMEMD 0x4CC860
// GLOBAL: GAMEMD 0x8B3CB8
int DAT_008B3CB8 = (int)(FUN_004CAD50(DAT_008B3C40 - DAT_008B3C68) * DAT_008B3C60 * 0.5);
// SYNTHETIC: GAMEMD 0x4CC8A0
// GLOBAL: GAMEMD 0x8B3C70
double DAT_008B3C70 = FUN_004CADE0(DAT_008B3CB8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4CC8D0
// GLOBAL: GAMEMD 0x8B3C88
double DAT_008B3C88 = FUN_004CADE0((DAT_008B3CB8 * 2) / DAT_008B3C60);
// SYNTHETIC: GAMEMD 0x4CC900
// GLOBAL: GAMEMD 0x8B3CAC
int DAT_008B3CAC = (int)(DAT_008B3CB8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4CC930
// GLOBAL: GAMEMD 0x8B3C58
HeaderCellInit DAT_008B3C58(0, 0);
// SYNTHETIC: GAMEMD 0x4CC940
// GLOBAL: GAMEMD 0x8B3C78
HeaderCoordInit DAT_008B3C78(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4CC960
// GLOBAL: GAMEMD 0x8B3CA0
HeaderCoordInit DAT_008B3CA0(128, 128, 0);
