// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0083E650 `.?AVScoreFullFontClass@@`; class hierarchy descriptor 0x00808E28.
//   Bases in RTTI (declaration) order: ScoreFontClass +0x0.
// VTABLE: GAMEMD 0x7F0F08 (5 slots)
//   Allocation: operator new (0x7C8E17) of 0x18 bytes at 0x68D3C9.
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_SCORE_FULL_FONT_CLASS_H
#define GG_MATCH_LAYOUT_SCORE_FULL_FONT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "score_font_class.h"

class ScoreFullFontClass : public ScoreFontClass
{
public:
    // 0  0x6910A0: deleting destructor; no destructor of its own is attested (no store of its own vtable)
};
GG_STATIC_ASSERT(sizeof(ScoreFullFontClass) == 0x18);

#endif  // GG_MATCH_LAYOUT_SCORE_FULL_FONT_CLASS_H
