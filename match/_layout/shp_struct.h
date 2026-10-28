// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x5F9296/0x5F929A compare the signed dimensions at +2/+4.
#ifndef GG_LAYOUT_SHP_STRUCT_H
#define GG_LAYOUT_SHP_STRUCT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// Shape file header; only the 16-bit fields these bodies read are named.
struct SHPStruct
{
    short unknown_00;
    short unknown_02;
    short unknown_04;   // read by 0x43D030 as the strip height
    short unknown_06;   // read by 0x43D290 as the strip height
};
GG_STATIC_ASSERT(offsetof(SHPStruct, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(SHPStruct, unknown_06) == 0x06);

GG_STATIC_ASSERT(offsetof(SHPStruct, unknown_02) == 2);
GG_STATIC_ASSERT(sizeof(SHPStruct) == 8);
#endif
