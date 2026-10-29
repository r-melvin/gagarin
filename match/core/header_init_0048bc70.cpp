// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x48BC70
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
// GLOBAL: GAMEMD 0x7E51A0
const double DAT_007E51A0 = 60.0;
// GLOBAL: GAMEMD 0x7E51A8 -- degrees to radians
const double DAT_007E51A8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x48BC70
// GLOBAL: GAMEMD 0x89E8B8
double DAT_0089E8B8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x48BCE0
// GLOBAL: GAMEMD 0x89E8E8
double DAT_0089E8E8 = DAT_007E51A8 * 45.0;
// SYNTHETIC: GAMEMD 0x48BD00
// GLOBAL: GAMEMD 0x89E8C0
double DAT_0089E8C0 = DAT_007E51A8 * 60.0;
// SYNTHETIC: GAMEMD 0x48BD20
// GLOBAL: GAMEMD 0x89E898
double DAT_0089E898 = DAT_007E51A8 * 90.0;
// SYNTHETIC: GAMEMD 0x48BD40
// GLOBAL: GAMEMD 0x89E910
int DAT_0089E910 = (int)(FUN_004CAD50(DAT_0089E898 - DAT_0089E8C0) * DAT_0089E8B8 * 0.5);
// SYNTHETIC: GAMEMD 0x48BD80
// GLOBAL: GAMEMD 0x89E8C8
double DAT_0089E8C8 = FUN_004CADE0(DAT_0089E910 * 0.00390625);
// SYNTHETIC: GAMEMD 0x48BDB0
// GLOBAL: GAMEMD 0x89E8E0
double DAT_0089E8E0 = FUN_004CADE0((DAT_0089E910 * 2) / DAT_0089E8B8);
// SYNTHETIC: GAMEMD 0x48BDE0
// GLOBAL: GAMEMD 0x89E904
int DAT_0089E904 = (int)(DAT_0089E910 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x48BE10
// GLOBAL: GAMEMD 0x89E8B0
HeaderCellInit DAT_0089E8B0(0, 0);
// SYNTHETIC: GAMEMD 0x48BE20
// GLOBAL: GAMEMD 0x89E8D0
HeaderCoordInit DAT_0089E8D0(0, 0, 0);
