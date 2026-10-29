// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Static initialisers of the math-table header group in the retail code range 0x600320-0x600502 (disassembled from the user's gamemd.exe v1.001).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
#include "mathtbl_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7E1720
extern const double DAT_007E1720;
// GLOBAL: GAMEMD 0x7E1728
extern const double DAT_007E1728;
// GLOBAL: GAMEMD 0x7E1730
extern const double DAT_007E1730;
// GLOBAL: GAMEMD 0x7E1738
extern const double DAT_007E1738;
// GLOBAL: GAMEMD 0x7E1740
extern const double DAT_007E1740;
// GLOBAL: GAMEMD 0x7EF708
extern const double DAT_007EF708;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x600320
// GLOBAL: GAMEMD 0xAC18B0
MathTblZero4 DAT_00AC18B0;
// SYNTHETIC: GAMEMD 0x600340
// GLOBAL: GAMEMD 0xAC1B40
double DAT_00AC1B40 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x6003B0
// GLOBAL: GAMEMD 0xAC4830
double DAT_00AC4830 = DAT_007E1720 * DAT_007EF708;
// SYNTHETIC: GAMEMD 0x6003D0
// GLOBAL: GAMEMD 0xAC1B88
double DAT_00AC1B88 = DAT_007E1728 * DAT_007EF708;
// SYNTHETIC: GAMEMD 0x6003F0
// GLOBAL: GAMEMD 0xAC1898
double DAT_00AC1898 = DAT_007E1730 * DAT_007EF708;
// SYNTHETIC: GAMEMD 0x600410
// GLOBAL: GAMEMD 0xAC48AC
int DAT_00AC48AC = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC1898 - DAT_00AC1B88) * DAT_00AC1B40));
// SYNTHETIC: GAMEMD 0x600450
// GLOBAL: GAMEMD 0xAC1CA0
double DAT_00AC1CA0 = FUN_004CADE0((double)DAT_00AC48AC * DAT_007E1740);
// SYNTHETIC: GAMEMD 0x600480
// GLOBAL: GAMEMD 0xAC4610
double DAT_00AC4610 = FUN_004CADE0((double)(DAT_00AC48AC * 2) / DAT_00AC1B40);
// SYNTHETIC: GAMEMD 0x6004B0
// GLOBAL: GAMEMD 0xAC489C
int DAT_00AC489C = (int)((double)(DAT_00AC48AC * 4) + DAT_007E1738);
// SYNTHETIC: GAMEMD 0x6004E0
// GLOBAL: GAMEMD 0xAC1B38
MathTblShortPair DAT_00AC1B38;
// SYNTHETIC: GAMEMD 0x6004F0
// GLOBAL: GAMEMD 0xAC1DF8
MathTblZero3 DAT_00AC1DF8;
