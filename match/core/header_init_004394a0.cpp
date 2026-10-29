// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4394A0
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
// GLOBAL: GAMEMD 0x7E3D70
const double DAT_007E3D70 = 60.0;
// GLOBAL: GAMEMD 0x7E3D78 -- degrees to radians
const double DAT_007E3D78 = 0.017453292519943295;

// GLOBAL: GAMEMD 0x89C778
extern int DAT_0089C778;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4394A0
// GLOBAL: GAMEMD 0x89C720
double DAT_0089C720 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x439610
// GLOBAL: GAMEMD 0x89C76C
int DAT_0089C76C = (int)(DAT_0089C778 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x439640
// GLOBAL: GAMEMD 0x89C718
HeaderCellInit DAT_0089C718(0, 0);
// SYNTHETIC: GAMEMD 0x439650
// GLOBAL: GAMEMD 0x89C738
HeaderCoordInit DAT_0089C738(0, 0, 0);
// SYNTHETIC: GAMEMD 0x439670
// GLOBAL: GAMEMD 0x89C760
HeaderCoordInit DAT_0089C760(128, 128, 0);
