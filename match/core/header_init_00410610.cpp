// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x410610
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E1FC0
const double DAT_007E1FC0 = 60.0;
// GLOBAL: GAMEMD 0x7E1FC8 -- degrees to radians
const double DAT_007E1FC8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x410610
// GLOBAL: GAMEMD 0x8876D8
double DAT_008876D8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x410680
// GLOBAL: GAMEMD 0x887708
double DAT_00887708 = DAT_007E1FC8 * 45.0;
// SYNTHETIC: GAMEMD 0x4106A0
// GLOBAL: GAMEMD 0x8876E0
double DAT_008876E0 = DAT_007E1FC8 * 60.0;
// SYNTHETIC: GAMEMD 0x4106C0
// GLOBAL: GAMEMD 0x8876C8
double DAT_008876C8 = DAT_007E1FC8 * 90.0;
// SYNTHETIC: GAMEMD 0x4106E0
// GLOBAL: GAMEMD 0x887730
int DAT_00887730 = (int)(FUN_004CAD50(DAT_008876C8 - DAT_008876E0) * DAT_008876D8 * 0.5);
// SYNTHETIC: GAMEMD 0x410720
// GLOBAL: GAMEMD 0x8876E8
double DAT_008876E8 = FUN_004CADE0(DAT_00887730 * 0.00390625);
// SYNTHETIC: GAMEMD 0x410750
// GLOBAL: GAMEMD 0x887700
double DAT_00887700 = FUN_004CADE0((DAT_00887730 * 2) / DAT_008876D8);
// SYNTHETIC: GAMEMD 0x410780
// GLOBAL: GAMEMD 0x887724
int DAT_00887724 = (int)(DAT_00887730 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4107B0
// GLOBAL: GAMEMD 0x8876D0
HeaderCellInit DAT_008876D0(0, 0);
// SYNTHETIC: GAMEMD 0x4107C0
// GLOBAL: GAMEMD 0x8876F0
HeaderCoordInit DAT_008876F0(0, 0, 0);
