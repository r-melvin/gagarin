// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x53F880-0x53FA70 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
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
// GLOBAL: GAMEMD 0x7EC0F8
const double DAT_007EC0F8 = 60.0;
// GLOBAL: GAMEMD 0x7EC100
const double DAT_007EC100 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x53F880
// GLOBAL: GAMEMD 0xAA05B8
MathTblZero4 DAT_00AA05B8;
// SYNTHETIC: GAMEMD 0x53F8A0
// GLOBAL: GAMEMD 0xAA05D0
double DAT_00AA05D0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x53F8D0
// GLOBAL: GAMEMD 0xAA0620
double DAT_00AA0620 = DAT_00AA05D0 / DAT_007EC0F8;
// SYNTHETIC: GAMEMD 0x53F8F0
// GLOBAL: GAMEMD 0xAA0608
double DAT_00AA0608 = 1.0 / DAT_00AA0620;
// SYNTHETIC: GAMEMD 0x53F910
// GLOBAL: GAMEMD 0xAA0600
double DAT_00AA0600 = DAT_007EC100 * 45.0;
// SYNTHETIC: GAMEMD 0x53F930
// GLOBAL: GAMEMD 0xAA05D8
double DAT_00AA05D8 = DAT_007EC100 * 60.0;
// SYNTHETIC: GAMEMD 0x53F950
// GLOBAL: GAMEMD 0xAA05B0
double DAT_00AA05B0 = DAT_007EC100 * 90.0;
// SYNTHETIC: GAMEMD 0x53F970
// GLOBAL: GAMEMD 0xAA0628
int DAT_00AA0628 = (int)(FUN_004CAD50(DAT_00AA05B0 - DAT_00AA05D8) * DAT_00AA05D0 * 0.5);
// SYNTHETIC: GAMEMD 0x53F9B0
// GLOBAL: GAMEMD 0xAA05E0
double DAT_00AA05E0 = FUN_004CADE0(DAT_00AA0628 * 0.00390625);
// SYNTHETIC: GAMEMD 0x53F9E0
// GLOBAL: GAMEMD 0xAA05F8
double DAT_00AA05F8 = FUN_004CADE0((DAT_00AA0628 * 2) / DAT_00AA05D0);
// SYNTHETIC: GAMEMD 0x53FA10
// GLOBAL: GAMEMD 0xAA061C
int DAT_00AA061C = (int)(DAT_00AA0628 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x53FA40
// GLOBAL: GAMEMD 0xAA05C8
HeaderCellInit DAT_00AA05C8(0, 0);
// SYNTHETIC: GAMEMD 0x53FA50
// GLOBAL: GAMEMD 0xAA05E8
HeaderCoordInit DAT_00AA05E8(0, 0, 0);
// SYNTHETIC: GAMEMD 0x53FA70
// GLOBAL: GAMEMD 0xAA0610
HeaderCoordInit DAT_00AA0610(128, 128, 0);
