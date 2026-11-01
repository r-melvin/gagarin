// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The constants and helpers the math-table header group of many retail translation units reads.
#ifndef GG_MATCH_MATHTBL_CONSTS_H
#define GG_MATCH_MATHTBL_CONSTS_H

// The double constants every math-table header group reads (pow() arguments and the table scale factors).
// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
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
// The two conversion constants the 0x770060 initialiser group reads (60.0 and pi / 180); the bytes sit at
// 0x7F7340/0x7F7348 between the Territory table and the next object's table, read only by that group, which
// match/mathtbl_init_770060.cpp defines.
// GLOBAL: GAMEMD 0x7F7340
extern const double DAT_007F7340;
// GLOBAL: GAMEMD 0x7F7348
extern const double DAT_007F7348;

#include "trig_table_functions_004cac40.h"

#endif  // GG_MATCH_MATHTBL_CONSTS_H
