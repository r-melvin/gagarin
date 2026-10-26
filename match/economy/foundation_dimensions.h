// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x6563B0 reads both tables at offsets 0..0x54: EBX starts at zero,
// advances by four at 0x656560 and is bounded by 0x58 at 0x656566.
// Parser 0x474DA0 independently returns the 22 foundation enum values 0..21.
// Both ranges are initialized writable .data in retail gamemd.exe v1.001.
#ifndef GG_MATCH_ECONOMY_FOUNDATION_DIMENSIONS_H
#define GG_MATCH_ECONOMY_FOUNDATION_DIMENSIONS_H
#include "../_rt/gg_static_assert.h"
GG_STATIC_ASSERT(sizeof(int) == 4);
// GLOBAL: GAMEMD 0x8192B8
extern int FoundationWidth[22];
// GLOBAL: GAMEMD 0x819310
extern int FoundationHeight[22];
GG_STATIC_ASSERT(sizeof(FoundationWidth) == 0x58);
GG_STATIC_ASSERT(sizeof(FoundationHeight) == 0x58);
#endif
