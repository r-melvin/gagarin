// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA | own-binary-via-Ghidra
// Existing CRC prefix from476D80. Caller5B40B0 likewise zeroes3dwords.
// Field names retained; original class identity remains unconfirmed.
#ifndef GG_MATCH_LAYOUT_CRC_00476D80_H
#define GG_MATCH_LAYOUT_CRC_00476D80_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct CRC_00476D80
{
    int CRC;
    int Staging;
    int Index;
    // Declaration: GAMEMD 0x4A1DE0
    int FUN_004A1DE0(const void* data, int length);
};
GG_STATIC_ASSERT(offsetof(CRC_00476D80, CRC) == 0);
GG_STATIC_ASSERT(offsetof(CRC_00476D80, Staging) == 4);
GG_STATIC_ASSERT(offsetof(CRC_00476D80, Index) == 8);
GG_STATIC_ASSERT(sizeof(CRC_00476D80) == 12);
#endif
