// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4206F0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E2B10
const double DAT_007E2B10 = 60.0;
// GLOBAL: GAMEMD 0x7E2B18 -- degrees to radians
const double DAT_007E2B18 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4206F0
// GLOBAL: GAMEMD 0x88A0C0
double DAT_0088A0C0 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x420760
// GLOBAL: GAMEMD 0x88A108
double DAT_0088A108 = DAT_007E2B18 * 45.0;
// SYNTHETIC: GAMEMD 0x420780
// GLOBAL: GAMEMD 0x88A0C8
double DAT_0088A0C8 = DAT_007E2B18 * 60.0;
// SYNTHETIC: GAMEMD 0x4207A0
// GLOBAL: GAMEMD 0x88A0A0
double DAT_0088A0A0 = DAT_007E2B18 * 90.0;
// SYNTHETIC: GAMEMD 0x4207C0
// GLOBAL: GAMEMD 0x89A130
int DAT_0089A130 = (int)(FUN_004CAD50(DAT_0088A0A0 - DAT_0088A0C8) * DAT_0088A0C0 * 0.5);
// SYNTHETIC: GAMEMD 0x420800
// GLOBAL: GAMEMD 0x88A0D0
double DAT_0088A0D0 = FUN_004CADE0(DAT_0089A130 * 0.00390625);
// SYNTHETIC: GAMEMD 0x420830
// GLOBAL: GAMEMD 0x88A0E8
double DAT_0088A0E8 = FUN_004CADE0((DAT_0089A130 * 2) / DAT_0088A0C0);
// SYNTHETIC: GAMEMD 0x420860
// GLOBAL: GAMEMD 0x89A124
int DAT_0089A124 = (int)(DAT_0089A130 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x420890
// GLOBAL: GAMEMD 0x88A0B8
HeaderCellInit DAT_0088A0B8(0, 0);
// SYNTHETIC: GAMEMD 0x4208A0
// GLOBAL: GAMEMD 0x88A0D8
HeaderCoordInit DAT_0088A0D8(0, 0, 0);
