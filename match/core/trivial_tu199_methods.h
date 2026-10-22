// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU199_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU199_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x887128
extern char DAT_00887128[];
// GLOBAL: GAMEMD 0x887180
extern char DAT_00887180[];

// FUNCTION: GAMEMD 0x476D80 (declaration)
void FUN_00476D80(void*, int);


// FUNCTION: GAMEMD 0x679EC0
void FUN_00679EC0(int a1, int a2);
// FUNCTION: GAMEMD 0x679ED0
void FUN_00679ED0(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU199_METHODS_H
