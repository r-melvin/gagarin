// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x00825B70 `.?AVBase64Straw@@`; class hierarchy descriptor 0x00803748.
//   Bases in RTTI (declaration) order: Straw +0x0.
//   vtable 0x7EB764 (3 slots) (VTABLE marker already carried by match/ccini_class_uublock_methods.h)
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
    // FUNCTION: GAMEMD 0x42DF90
    virtual int FUN_006C98E0(void*, int);                         // 2  0x42DF90: override of Straw

    int Control;         // +0x0C  0 = encode, otherwise decode (0x42DF90)
    int Counter;         // +0x10  bytes of the current group not yet handed out
    char CBuffer[4];     // +0x14  the four-character group
    char PBuffer[3];     // +0x18  the three-byte group
    char unknown_1B;     // +0x1B
};
GG_STATIC_ASSERT(offsetof(Base64Straw, Control) == 0x0C);
GG_STATIC_ASSERT(offsetof(Base64Straw, Counter) == 0x10);
GG_STATIC_ASSERT(offsetof(Base64Straw, CBuffer) == 0x14);
GG_STATIC_ASSERT(offsetof(Base64Straw, PBuffer) == 0x18);
GG_STATIC_ASSERT(sizeof(Base64Straw) == 0x1C);

#endif  // GG_MATCH_LAYOUT_BASE64_STRAW_H
