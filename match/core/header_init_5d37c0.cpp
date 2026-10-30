// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5D37C0-0x5D39B0 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7EEC78
const double DAT_007EEC78 = 60.0;
// GLOBAL: GAMEMD 0x7EEC80
const double DAT_007EEC80 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5D37C0
// GLOBAL: GAMEMD 0xABFC18
MathTblZero4 DAT_00ABFC18;
// SYNTHETIC: GAMEMD 0x5D37E0
// GLOBAL: GAMEMD 0xABFC30
double DAT_00ABFC30 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5D3810
// GLOBAL: GAMEMD 0xABFC80
double DAT_00ABFC80 = DAT_00ABFC30 / DAT_007EEC78;
// SYNTHETIC: GAMEMD 0x5D3830
// GLOBAL: GAMEMD 0xABFC68
double DAT_00ABFC68 = 1.0 / DAT_00ABFC80;
// SYNTHETIC: GAMEMD 0x5D3850
// GLOBAL: GAMEMD 0xABFC60
double DAT_00ABFC60 = DAT_007EEC80 * 45.0;
// SYNTHETIC: GAMEMD 0x5D3870
// GLOBAL: GAMEMD 0xABFC38
double DAT_00ABFC38 = DAT_007EEC80 * 60.0;
// SYNTHETIC: GAMEMD 0x5D3890
// GLOBAL: GAMEMD 0xABFC10
double DAT_00ABFC10 = DAT_007EEC80 * 90.0;
// SYNTHETIC: GAMEMD 0x5D38B0
// GLOBAL: GAMEMD 0xABFC88
int DAT_00ABFC88 = (int)(FUN_004CAD50(DAT_00ABFC10 - DAT_00ABFC38) * DAT_00ABFC30 * 0.5);
// SYNTHETIC: GAMEMD 0x5D38F0
// GLOBAL: GAMEMD 0xABFC40
double DAT_00ABFC40 = FUN_004CADE0(DAT_00ABFC88 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5D3920
// GLOBAL: GAMEMD 0xABFC58
double DAT_00ABFC58 = FUN_004CADE0((DAT_00ABFC88 * 2) / DAT_00ABFC30);
// SYNTHETIC: GAMEMD 0x5D3950
// GLOBAL: GAMEMD 0xABFC7C
int DAT_00ABFC7C = (int)(DAT_00ABFC88 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5D3980
// GLOBAL: GAMEMD 0xABFC28
HeaderCellInit DAT_00ABFC28(0, 0);
// SYNTHETIC: GAMEMD 0x5D3990
// GLOBAL: GAMEMD 0xABFC48
HeaderCoordInit DAT_00ABFC48(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5D39B0
// GLOBAL: GAMEMD 0xABFC70
HeaderCoordInit DAT_00ABFC70(128, 128, 0);
