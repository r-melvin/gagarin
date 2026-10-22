// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU126_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU126_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Gbl_00ABCE70;

// GLOBAL: GAMEMD 0xABCE70
extern Gbl_00ABCE70 DAT_00ABCE70;

struct Gbl_00ABCE70
{
    // FUNCTION: GAMEMD 0x5FA350
    void FUN_005FA350();
};


// FUNCTION: GAMEMD 0x55F970
void __cdecl FUN_0055F970();

#endif  // GG_MATCH_CORE_TRIVIAL_TU126_METHODS_H
