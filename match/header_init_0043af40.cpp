// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x43AF40
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"
#include "trig_table_functions_004cac40.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E3E78
const double DAT_007E3E78 = 60.0;
// GLOBAL: GAMEMD 0x7E3E80 -- degrees to radians
const double DAT_007E3E80 = 0.017453292519943295;



// SYNTHETIC: GAMEMD 0x43AF40
// GLOBAL: GAMEMD 0x89C820
double DAT_0089C820 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
