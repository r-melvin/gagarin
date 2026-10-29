// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI at the retail vtable 0x7E3A78 identifies BitFont; slot zero points
//   to 0x434A40. That entry stores the vptr at +0, reads cache +8 and payload
//   +4, then releases payload pointers at +0x18/+0x1C. The resolver at
//   0x433990 allocates the payload as 0x24 bytes and writes its count at +0x20.
//   Complete entry evidence: the disassembly of 0x434A40 from its entry point.
#ifndef GG_MATCH_UI_BIT_FONT_SCALAR_DTOR_00434A40_H
#define GG_MATCH_UI_BIT_FONT_SCALAR_DTOR_00434A40_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#endif  // GG_MATCH_UI_BIT_FONT_SCALAR_DTOR_00434A40_H
