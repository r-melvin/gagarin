// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small leaf functions (3-20 bytes) with addresses < 0x500000,
//   offsets confirmed via instruction
//   read widths and operand encoding against local Ghidra disassembly of
//   the user's retail gamemd.exe v1.001.
#ifndef GG_MATCH_CORE_LEAF_BATCH2_METHODS_H
#define GG_MATCH_CORE_LEAF_BATCH2_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x004CA170
// FactoryClass getter for OriginalBalance at offset 0x68
struct FactoryClass_004CA170 {
    unsigned char unknown_00[0x68];
    int OriginalBalance;  // +0x68

    // FUNCTION: GAMEMD 0x004CA170
    int GetOriginalBalance() const;
};
GG_STATIC_ASSERT(offsetof(FactoryClass_004CA170, OriginalBalance) == 0x68);

// FUNCTION: GAMEMD 0x004E2450
// Timer snapshot constructor
struct Timer_004E2450 {
    int Snapshot;  // +0x00

    // FUNCTION: GAMEMD 0x004E2450
    Timer_004E2450();
};
GG_STATIC_ASSERT(offsetof(Timer_004E2450, Snapshot) == 0x0);


#endif  // GG_MATCH_CORE_LEAF_BATCH2_METHODS_H
