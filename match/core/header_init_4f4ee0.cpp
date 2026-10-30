// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x4F4EE0-0x4F50D0 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#pragma intrinsic(pow)
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"
#include "../_layout/cell.h"

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
// GLOBAL: GAMEMD 0x7EA758
const double DAT_007EA758 = 60.0;
// GLOBAL: GAMEMD 0x7EA760
const double DAT_007EA760 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x4F4EE0
// GLOBAL: GAMEMD 0xA8EF68
MathTblZero4 DAT_00A8EF68;
