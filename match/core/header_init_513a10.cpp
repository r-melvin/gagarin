// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x513A10-0x513C00 (header_init_shapes.h): the group of
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
// GLOBAL: GAMEMD 0x7EACE8
const double DAT_007EACE8 = 60.0;
// GLOBAL: GAMEMD 0x7EACF0
const double DAT_007EACF0 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x513A10
// GLOBAL: GAMEMD 0xA8F168
double DAT_00A8F168 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
// SYNTHETIC: GAMEMD 0x513A40
// GLOBAL: GAMEMD 0xA8F1B8
double DAT_00A8F1B8 = DAT_00A8F168 / DAT_007EACE8;
// SYNTHETIC: GAMEMD 0x513A60
// GLOBAL: GAMEMD 0xA8F1A0
double DAT_00A8F1A0 = 1.0 / DAT_00A8F1B8;
// SYNTHETIC: GAMEMD 0x513A80
// GLOBAL: GAMEMD 0xA8F198
double DAT_00A8F198 = DAT_007EACF0 * 45.0;
// SYNTHETIC: GAMEMD 0x513AA0
// GLOBAL: GAMEMD 0xA8F170
double DAT_00A8F170 = DAT_007EACF0 * 60.0;
// SYNTHETIC: GAMEMD 0x513AC0
// GLOBAL: GAMEMD 0xA8F148
double DAT_00A8F148 = DAT_007EACF0 * 90.0;
// SYNTHETIC: GAMEMD 0x513AE0
// GLOBAL: GAMEMD 0xA8F1C0
int DAT_00A8F1C0 = (int)(FUN_004CAD50(DAT_00A8F148 - DAT_00A8F170) * DAT_00A8F168 * 0.5);
// SYNTHETIC: GAMEMD 0x513B20
// GLOBAL: GAMEMD 0xA8F178
double DAT_00A8F178 = FUN_004CADE0(DAT_00A8F1C0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x513B50
// GLOBAL: GAMEMD 0xA8F190
double DAT_00A8F190 = FUN_004CADE0((DAT_00A8F1C0 * 2) / DAT_00A8F168);
// SYNTHETIC: GAMEMD 0x513B80
// GLOBAL: GAMEMD 0xA8F1B4
int DAT_00A8F1B4 = (int)(DAT_00A8F1C0 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x513BB0
// GLOBAL: GAMEMD 0xA8F160
HeaderCellInit DAT_00A8F160(0, 0);
// SYNTHETIC: GAMEMD 0x513BC0
// GLOBAL: GAMEMD 0xA8F180
HeaderCoordInit DAT_00A8F180(0, 0, 0);
// SYNTHETIC: GAMEMD 0x513BE0
// GLOBAL: GAMEMD 0xA8F1A8
HeaderCoordInit DAT_00A8F1A8(128, 128, 0);
// SYNTHETIC: GAMEMD 0x513C00
// GLOBAL: GAMEMD 0xA8F150
MathTblZero4 DAT_00A8F150;

// The unit's own static after the header group: a three-byte colour record whose
// constructor zeroes its components (retail 0x517340, in the hover unit proper).
struct HeaderByteTriple
{
    unsigned char A;
    unsigned char B;
    unsigned char C;
    HeaderByteTriple() : A(0), B(0), C(0) {}
};
GG_STATIC_ASSERT(sizeof(HeaderByteTriple) == 3);

// SYNTHETIC: GAMEMD 0x517340
// GLOBAL: GAMEMD 0xA8F1C4
HeaderByteTriple DAT_00A8F1C4;
