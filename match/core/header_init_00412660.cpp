// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x412660
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E2228
const double DAT_007E2228 = 60.0;
// GLOBAL: GAMEMD 0x7E2230 -- degrees to radians
const double DAT_007E2230 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x412660
// GLOBAL: GAMEMD 0x887858
double DAT_00887858 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x412690
// GLOBAL: GAMEMD 0x889E40
double DAT_00889E40 = DAT_00887858 / DAT_007E2228;
// SYNTHETIC: GAMEMD 0x4126B0
// GLOBAL: GAMEMD 0x889E28
double DAT_00889E28 = 1.0 / DAT_00889E40;
// SYNTHETIC: GAMEMD 0x4126D0
// GLOBAL: GAMEMD 0x889E20
double DAT_00889E20 = DAT_007E2230 * 45.0;
// SYNTHETIC: GAMEMD 0x4126F0
// GLOBAL: GAMEMD 0x887860
double DAT_00887860 = DAT_007E2230 * 60.0;
// SYNTHETIC: GAMEMD 0x412710
// GLOBAL: GAMEMD 0x887838
double DAT_00887838 = DAT_007E2230 * 90.0;
// SYNTHETIC: GAMEMD 0x412730
// GLOBAL: GAMEMD 0x889E48
int DAT_00889E48 = (int)(FUN_004CAD50(DAT_00887838 - DAT_00887860) * DAT_00887858 * 0.5);
// SYNTHETIC: GAMEMD 0x412770
// GLOBAL: GAMEMD 0x887868
double DAT_00887868 = FUN_004CADE0(DAT_00889E48 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4127A0
// GLOBAL: GAMEMD 0x887880
double DAT_00887880 = FUN_004CADE0((DAT_00889E48 * 2) / DAT_00887858);
// SYNTHETIC: GAMEMD 0x4127D0
// GLOBAL: GAMEMD 0x889E3C
int DAT_00889E3C = (int)(DAT_00889E48 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x412800
// GLOBAL: GAMEMD 0x887850
HeaderCellInit DAT_00887850(0, 0);
// SYNTHETIC: GAMEMD 0x412810
// GLOBAL: GAMEMD 0x887870
HeaderCoordInit DAT_00887870(0, 0, 0);
// SYNTHETIC: GAMEMD 0x412830
// GLOBAL: GAMEMD 0x889E30
HeaderCoordInit DAT_00889E30(128, 128, 0);
