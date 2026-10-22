// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0081B7A8 `.?AVCarryoverClass@@`; class hierarchy descriptor 0x007FCBE8.
//   Bases in RTTI (declaration) order: LinkClass +0x0.
//   vtable 0x7E4C04 (10 slots) (VTABLE marker already carried by match/combat/target_snapshot_ctor_methods.h)
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_CARRYOVER_CLASS_H
#define GG_MATCH_LAYOUT_CARRYOVER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/link_class_methods.h"

class CarryoverClass : public LinkClass
{
public:
    virtual ~CarryoverClass();                                  // 0  0x473920: deleting destructor override
    int unknown_0C;  // +0xC store at 0x473760
    int unknown_10;  // +0x10 store at 0x4737B3
    int unknown_14;  // +0x14 store at 0x473763
    int unknown_18;  // +0x18 store at 0x47376D
    int unknown_1C;  // +0x1C store at 0x473770
};
GG_STATIC_ASSERT(offsetof(CarryoverClass, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(CarryoverClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(CarryoverClass, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(CarryoverClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(CarryoverClass, unknown_1C) == 0x1C);

#endif  // GG_MATCH_LAYOUT_CARRYOVER_CLASS_H
