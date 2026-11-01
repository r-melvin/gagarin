// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x4D2F50
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
// GLOBAL: GAMEMD 0x7E8BE0
const double DAT_007E8BE0 = 60.0;
// GLOBAL: GAMEMD 0x7E8BE8 -- degrees to radians
const double DAT_007E8BE8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x4D2F50
// GLOBAL: GAMEMD 0x8B3D90
double DAT_008B3D90 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x4D2F80
// GLOBAL: GAMEMD 0x8B3DF8
double DAT_008B3DF8 = DAT_008B3D90 / DAT_007E8BE0;
// SYNTHETIC: GAMEMD 0x4D2FA0
// GLOBAL: GAMEMD 0x8B3DE0
double DAT_008B3DE0 = 1.0 / DAT_008B3DF8;
// SYNTHETIC: GAMEMD 0x4D2FC0
// GLOBAL: GAMEMD 0x8B3DD8
double DAT_008B3DD8 = DAT_007E8BE8 * 45.0;
// SYNTHETIC: GAMEMD 0x4D2FE0
// GLOBAL: GAMEMD 0x8B3D98
double DAT_008B3D98 = DAT_007E8BE8 * 60.0;
// SYNTHETIC: GAMEMD 0x4D3000
// GLOBAL: GAMEMD 0x8B3D70
double DAT_008B3D70 = DAT_007E8BE8 * 90.0;
// SYNTHETIC: GAMEMD 0x4D3020
// GLOBAL: GAMEMD 0x8B3E00
int DAT_008B3E00 = (int)(FUN_004CAD50(DAT_008B3D70 - DAT_008B3D98) * DAT_008B3D90 * 0.5);
// SYNTHETIC: GAMEMD 0x4D3060
// GLOBAL: GAMEMD 0x8B3DA0
double DAT_008B3DA0 = FUN_004CADE0(DAT_008B3E00 * 0.00390625);
// SYNTHETIC: GAMEMD 0x4D3090
// GLOBAL: GAMEMD 0x8B3DB8
double DAT_008B3DB8 = FUN_004CADE0((DAT_008B3E00 * 2) / DAT_008B3D90);
// SYNTHETIC: GAMEMD 0x4D30C0
// GLOBAL: GAMEMD 0x8B3DF4
int DAT_008B3DF4 = (int)(DAT_008B3E00 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x4D30F0
// GLOBAL: GAMEMD 0x8B3D88
HeaderCellInit DAT_008B3D88(0, 0);
// SYNTHETIC: GAMEMD 0x4D3100
// GLOBAL: GAMEMD 0x8B3DA8
HeaderCoordInit DAT_008B3DA8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4D3120
// GLOBAL: GAMEMD 0x8B3DE8
HeaderCoordInit DAT_008B3DE8(128, 128, 0);
