// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Header static initialisers at 0x4F4EE0-0x4F50D0 (header_init_shapes.h): the group of
// math-table doubles/ints and zero blocks each retail TU opens with, in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"
#include "mathtbl_init_shapes.h"
#include "_layout/cell.h"
#include "mathtbl_consts.h"
#include "trig_table_functions_004cac40.h"


// GLOBAL: GAMEMD 0x7EA758
const double DAT_007EA758 = 60.0;
// GLOBAL: GAMEMD 0x7EA760
const double DAT_007EA760 = 0.017453292519943295;

// SYNTHETIC: GAMEMD 0x4F4EE0
// GLOBAL: GAMEMD 0xA8EF68
MathTblZero4 DAT_00A8EF68;
