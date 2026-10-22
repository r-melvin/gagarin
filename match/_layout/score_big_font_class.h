// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0083E698 `.?AVScoreBigFontClass@@`; class hierarchy descriptor 0x00808E78.
//   Bases in RTTI (declaration) order: ScoreFontClass +0x0.
// VTABLE: GAMEMD 0x7F0F20 (5 slots)
//   Allocation: operator new (0x7C8E17) of 0x18 bytes at 0x68D3E7.
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_SCORE_BIG_FONT_CLASS_H
#define GG_MATCH_LAYOUT_SCORE_BIG_FONT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "score_font_class.h"

class ScoreBigFontClass : public ScoreFontClass
{
public:
    // 0  0x691100: deleting destructor; no destructor of its own is attested (no store of its own vtable)
};
GG_STATIC_ASSERT(sizeof(ScoreBigFontClass) == 0x18);

#endif  // GG_MATCH_LAYOUT_SCORE_BIG_FONT_CLASS_H
