// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC24_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC24_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8E9AC / 0xA8E9B8 — an array of records and its count. Both
// are re-read on every iteration rather than hoisted.
struct Rec_00422B80 { char _pad000[0xCC]; void* atCC; char _padD0[0x195 - 0xD0]; unsigned char at195; };
extern Rec_00422B80** DAT_00A8E9AC;
extern int            DAT_00A8E9B8;

// FUNCTION: GAMEMD 0x422B80 — clear a flag on every record pointing at `key`.
void __fastcall FUN_00422B80(void* key);

#endif  // GG_MATCH_CORE_SMALL_MISC24_METHODS_H
