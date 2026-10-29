// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Receiver of 0x6C9940 and its callers: an object holding a packed three-byte
// time of day in the word at +0x08 (hi in bits 16-23, mid 8-15, lo 0-7).
#ifndef GG_MATCH_CORE_PACKED_006C9940_H
#define GG_MATCH_CORE_PACKED_006C9940_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Packed_006C9940
{
    unsigned char unknown_00[8];
    unsigned int Packed;   // +0x08

    void FUN_006C9940(unsigned char hi, unsigned char mid, unsigned char lo);
};
GG_STATIC_ASSERT(offsetof(Packed_006C9940, Packed) == 0x08);

#endif
