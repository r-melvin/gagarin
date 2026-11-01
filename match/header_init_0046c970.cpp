// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x46C970
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
// GLOBAL: GAMEMD 0x7E49E8
const double DAT_007E49E8 = 60.0;
// GLOBAL: GAMEMD 0x7E49F0 -- degrees to radians
const double DAT_007E49F0 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x46C970
// GLOBAL: GAMEMD 0x89DF08
double DAT_0089DF08 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x46C9A0
// GLOBAL: GAMEMD 0x89DF58
double DAT_0089DF58 = DAT_0089DF08 / DAT_007E49E8;
// SYNTHETIC: GAMEMD 0x46C9C0
// GLOBAL: GAMEMD 0x89DF40
double DAT_0089DF40 = 1.0 / DAT_0089DF58;
// SYNTHETIC: GAMEMD 0x46C9E0
// GLOBAL: GAMEMD 0x89DF38
double DAT_0089DF38 = DAT_007E49F0 * 45.0;
// SYNTHETIC: GAMEMD 0x46CA00
// GLOBAL: GAMEMD 0x89DF10
double DAT_0089DF10 = DAT_007E49F0 * 60.0;
// SYNTHETIC: GAMEMD 0x46CA20
// GLOBAL: GAMEMD 0x89DEF8
double DAT_0089DEF8 = DAT_007E49F0 * 90.0;
// SYNTHETIC: GAMEMD 0x46CA40
// GLOBAL: GAMEMD 0x89DF60
int DAT_0089DF60 = (int)(FUN_004CAD50(DAT_0089DEF8 - DAT_0089DF10) * DAT_0089DF08 * 0.5);
// SYNTHETIC: GAMEMD 0x46CA80
// GLOBAL: GAMEMD 0x89DF18
double DAT_0089DF18 = FUN_004CADE0(DAT_0089DF60 * 0.00390625);
// SYNTHETIC: GAMEMD 0x46CAB0
// GLOBAL: GAMEMD 0x89DF30
double DAT_0089DF30 = FUN_004CADE0((DAT_0089DF60 * 2) / DAT_0089DF08);
// SYNTHETIC: GAMEMD 0x46CAE0
// GLOBAL: GAMEMD 0x89DF54
int DAT_0089DF54 = (int)(DAT_0089DF60 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x46CB10
// GLOBAL: GAMEMD 0x89DF00
HeaderCellInit DAT_0089DF00(0, 0);
// SYNTHETIC: GAMEMD 0x46CB20
// GLOBAL: GAMEMD 0x89DF20
HeaderCoordInit DAT_0089DF20(0, 0, 0);
// SYNTHETIC: GAMEMD 0x46CB40
// GLOBAL: GAMEMD 0x89DF48
HeaderCoordInit DAT_0089DF48(128, 128, 0);
