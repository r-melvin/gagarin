// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x48C6B0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E51E0
const double DAT_007E51E0 = 60.0;
// GLOBAL: GAMEMD 0x7E51E8 -- degrees to radians
const double DAT_007E51E8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x48C6B0
// GLOBAL: GAMEMD 0x89E948
double DAT_0089E948 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x48C720
// GLOBAL: GAMEMD 0x89E980
double DAT_0089E980 = DAT_007E51E8 * 45.0;
// SYNTHETIC: GAMEMD 0x48C740
// GLOBAL: GAMEMD 0x89E958
double DAT_0089E958 = DAT_007E51E8 * 60.0;
// SYNTHETIC: GAMEMD 0x48C760
// GLOBAL: GAMEMD 0x89E918
double DAT_0089E918 = DAT_007E51E8 * 90.0;
// SYNTHETIC: GAMEMD 0x48C780
// GLOBAL: GAMEMD 0x89E9A8
int DAT_0089E9A8 = (int)(FUN_004CAD50(DAT_0089E918 - DAT_0089E958) * DAT_0089E948 * 0.5);
// SYNTHETIC: GAMEMD 0x48C7C0
// GLOBAL: GAMEMD 0x89E960
double DAT_0089E960 = FUN_004CADE0(DAT_0089E9A8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x48C7F0
// GLOBAL: GAMEMD 0x89E978
double DAT_0089E978 = FUN_004CADE0((DAT_0089E9A8 * 2) / DAT_0089E948);
// SYNTHETIC: GAMEMD 0x48C820
// GLOBAL: GAMEMD 0x89E99C
int DAT_0089E99C = (int)(DAT_0089E9A8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x48C850
// GLOBAL: GAMEMD 0x89E940
HeaderCellInit DAT_0089E940(0, 0);
// SYNTHETIC: GAMEMD 0x48C860
// GLOBAL: GAMEMD 0x89E968
HeaderCoordInit DAT_0089E968(0, 0, 0);
