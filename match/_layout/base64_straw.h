// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x00825B70 `.?AVBase64Straw@@`; class hierarchy descriptor 0x00803748.
//   Bases in RTTI (declaration) order: Straw +0x0.
//   vtable 0x7EB764 (3 slots) (VTABLE marker already carried by match/platform/ccini_class_uublock_methods.h)
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_BASE64_STRAW_H
#define GG_MATCH_LAYOUT_BASE64_STRAW_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "straw.h"

class Base64Straw : public Straw
{
public:
    // 0  0x52AEA0: deleting destructor; no destructor of its own is attested (calls the base destructor 0x6C9850 directly)
    virtual int FUN_006C98E0(void*, int);                         // 2  0x42DF90: override of Straw
};

#endif  // GG_MATCH_LAYOUT_BASE64_STRAW_H
