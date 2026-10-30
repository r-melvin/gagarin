// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x452D40. The four calls take 0, 2, 4 and 6 — even values only,
//   so the argument is a side/facing pair index rather than a count.
#ifndef GG_MATCH_AI_REFRESH_ALL_SIDES_METHODS_H
#define GG_MATCH_AI_REFRESH_ALL_SIDES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8E7AC — nonzero suppresses the whole pass.
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x452D40
void FUN_00452D40();

#endif  // GG_MATCH_AI_REFRESH_ALL_SIDES_METHODS_H
