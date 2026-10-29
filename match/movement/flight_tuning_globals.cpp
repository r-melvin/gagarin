// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x5B2B90-0x5B2D80 (header_init_shapes.h): the same
// math-table group of doubles/ints and zero blocks as header_init_5b1ee0.cpp, the
// copy this TU got, in __xc order. Retail's evidence: each initialiser stores one
// global of the 0x00ABEF58..0x00ABEFD0 run, and the table entries point straight at
// them.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
#include "../core/header_init_shapes.h"
#include "../core/mathtbl_init_shapes.h"

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
// GLOBAL: GAMEMD 0x7EDC80
const double DAT_007EDC80 = 60.0;
// GLOBAL: GAMEMD 0x7EDC88
const double DAT_007EDC88 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x5B2B90
// GLOBAL: GAMEMD 0xABEF78
double DAT_00ABEF78 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x5B2BC0
// GLOBAL: GAMEMD 0xABEFC8
double DAT_00ABEFC8 = DAT_00ABEF78 / DAT_007EDC80;
// SYNTHETIC: GAMEMD 0x5B2BE0
// GLOBAL: GAMEMD 0xABEFB0
double DAT_00ABEFB0 = 1.0 / DAT_00ABEFC8;
// SYNTHETIC: GAMEMD 0x5B2C00
// GLOBAL: GAMEMD 0xABEFA8
double DAT_00ABEFA8 = DAT_007EDC88 * 45.0;
// SYNTHETIC: GAMEMD 0x5B2C20
// GLOBAL: GAMEMD 0xABEF80
double DAT_00ABEF80 = DAT_007EDC88 * 60.0;
// SYNTHETIC: GAMEMD 0x5B2C40
// GLOBAL: GAMEMD 0xABEF58
double DAT_00ABEF58 = DAT_007EDC88 * 90.0;
// SYNTHETIC: GAMEMD 0x5B2C60
// GLOBAL: GAMEMD 0xABEFD0
int DAT_00ABEFD0 = (int)(FUN_004CAD50(DAT_00ABEF58 - DAT_00ABEF80) * DAT_00ABEF78 * 0.5);
// SYNTHETIC: GAMEMD 0x5B2CA0
// GLOBAL: GAMEMD 0xABEF88
double DAT_00ABEF88 = FUN_004CADE0(DAT_00ABEFD0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x5B2CD0
// GLOBAL: GAMEMD 0xABEFA0
double DAT_00ABEFA0 = FUN_004CADE0((DAT_00ABEFD0 * 2) / DAT_00ABEF78);
// SYNTHETIC: GAMEMD 0x5B2D00
// GLOBAL: GAMEMD 0xABEFC4
int DAT_00ABEFC4 = (int)(DAT_00ABEFD0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x5B2D30
// GLOBAL: GAMEMD 0xABEF70
HeaderCellInit DAT_00ABEF70(0, 0);
// SYNTHETIC: GAMEMD 0x5B2D40
// GLOBAL: GAMEMD 0xABEF90
HeaderCoordInit DAT_00ABEF90(0, 0, 0);
// SYNTHETIC: GAMEMD 0x5B2D60
// GLOBAL: GAMEMD 0xABEFB8
HeaderCoordInit DAT_00ABEFB8(128, 128, 0);
// SYNTHETIC: GAMEMD 0x5B2D80
// GLOBAL: GAMEMD 0xABEF60
MathTblZero4 DAT_00ABEF60;
