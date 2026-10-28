// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4C5EE0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E8808
const double DAT_007E8808 = 60.0;
// GLOBAL: GAMEMD 0x7E8810 -- degrees to radians
const double DAT_007E8810 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4C5EE0
// GLOBAL: GAMEMD 0x8A38D8
double DAT_008A38D8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4C5F50
// GLOBAL: GAMEMD 0x8A3950
double DAT_008A3950 = DAT_007E8810 * 45.0;
// SYNTHETIC: GAMEMD 0x4C5F70
// GLOBAL: GAMEMD 0x8A3928
double DAT_008A3928 = DAT_007E8810 * 60.0;
// SYNTHETIC: GAMEMD 0x4C5F90
// GLOBAL: GAMEMD 0x8A38B8
double DAT_008A38B8 = DAT_007E8810 * 90.0;
// SYNTHETIC: GAMEMD 0x4C5FB0
// GLOBAL: GAMEMD 0x8A3978
int DAT_008A3978 = (int)(FUN_004CAD50(DAT_008A38B8 - DAT_008A3928) * DAT_008A38D8 * 0.5);
// SYNTHETIC: GAMEMD 0x4C5FF0
// GLOBAL: GAMEMD 0x8A3930
double DAT_008A3930 = FUN_004CADE0(DAT_008A3978 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4C6020
// GLOBAL: GAMEMD 0x8A3948
double DAT_008A3948 = FUN_004CADE0((DAT_008A3978 * 2) / DAT_008A38D8);
// SYNTHETIC: GAMEMD 0x4C6050
// GLOBAL: GAMEMD 0x8A396C
int DAT_008A396C = (int)(DAT_008A3978 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4C6080
// GLOBAL: GAMEMD 0x8A38D0
HeaderCellInit DAT_008A38D0(0, 0);
// SYNTHETIC: GAMEMD 0x4C6090
// GLOBAL: GAMEMD 0x8A3938
HeaderCoordInit DAT_008A3938(0, 0, 0);
