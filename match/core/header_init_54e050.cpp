// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x54E050-0x54E240 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7ECE68
const double DAT_007ECE68 = 60.0;
// GLOBAL: GAMEMD 0x7ECE70
const double DAT_007ECE70 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x54E050
// GLOBAL: GAMEMD 0xABC638
double DAT_00ABC638 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x54E080
// GLOBAL: GAMEMD 0xABC688
double DAT_00ABC688 = DAT_00ABC638 / DAT_007ECE68;
// SYNTHETIC: GAMEMD 0x54E0A0
// GLOBAL: GAMEMD 0xABC670
double DAT_00ABC670 = 1.0 / DAT_00ABC688;
// SYNTHETIC: GAMEMD 0x54E0C0
// GLOBAL: GAMEMD 0xABC668
double DAT_00ABC668 = DAT_007ECE70 * 45.0;
// SYNTHETIC: GAMEMD 0x54E0E0
// GLOBAL: GAMEMD 0xABC640
double DAT_00ABC640 = DAT_007ECE70 * 60.0;
// SYNTHETIC: GAMEMD 0x54E100
// GLOBAL: GAMEMD 0xABC5F0
double DAT_00ABC5F0 = DAT_007ECE70 * 90.0;
// SYNTHETIC: GAMEMD 0x54E120
// GLOBAL: GAMEMD 0xABC690
int DAT_00ABC690 = (int)(FUN_004CAD50(DAT_00ABC5F0 - DAT_00ABC640) * DAT_00ABC638 * 0.5);
// SYNTHETIC: GAMEMD 0x54E160
// GLOBAL: GAMEMD 0xABC648
double DAT_00ABC648 = FUN_004CADE0(DAT_00ABC690 * 0.00390625);
// SYNTHETIC: GAMEMD 0x54E190
// GLOBAL: GAMEMD 0xABC660
double DAT_00ABC660 = FUN_004CADE0((DAT_00ABC690 * 2) / DAT_00ABC638);
// SYNTHETIC: GAMEMD 0x54E1C0
// GLOBAL: GAMEMD 0xABC684
int DAT_00ABC684 = (int)(DAT_00ABC690 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x54E1F0
// GLOBAL: GAMEMD 0xABC630
HeaderCellInit DAT_00ABC630(0, 0);
// SYNTHETIC: GAMEMD 0x54E200
// GLOBAL: GAMEMD 0xABC650
HeaderCoordInit DAT_00ABC650(0, 0, 0);
// SYNTHETIC: GAMEMD 0x54E220
// GLOBAL: GAMEMD 0xABC678
HeaderCoordInit DAT_00ABC678(128, 128, 0);
// SYNTHETIC: GAMEMD 0x54E240
// GLOBAL: GAMEMD 0xABC620
MathTblZero4 DAT_00ABC620;
