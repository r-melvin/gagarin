// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x471D40 requests 0x14 bytes at 0x471DCC and initializes the unit
// pointer at +0, saved house at +4, current frame at +8 and zero at +0x10.
// 0x472140/0x4722F0 read +0/+4; 0x472640 uses +8/+0x10 for frame arithmetic.
// The gap at +0x0C has no established type or meaning in these consumers.
#ifndef GG_MATCH_LAYOUT_CONTROL_NODE_H
#define GG_MATCH_LAYOUT_CONTROL_NODE_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
class TechnoClass;
class HouseClass;

struct ControlNode
{
    TechnoClass* Unit;
    HouseClass* OriginalOwner;
    int StartFrame;
    unsigned char unknown_0C[4];
    int Duration;
};
GG_STATIC_ASSERT(offsetof(ControlNode, Unit) == 0x00);
GG_STATIC_ASSERT(offsetof(ControlNode, OriginalOwner) == 0x04);
GG_STATIC_ASSERT(offsetof(ControlNode, StartFrame) == 0x08);
GG_STATIC_ASSERT(offsetof(ControlNode, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(ControlNode, Duration) == 0x10);
GG_STATIC_ASSERT(sizeof(ControlNode) == 0x14);
#endif
