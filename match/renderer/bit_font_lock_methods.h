// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and vtable slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x4348F0: `[ESI+0xC]` (the locked
//   buffer), `[ESI+0x10]` (pitch halved with SHR), `[ESI+0x30..0x3C]` (the
//   clip rectangle, OR-tested for all-zero); surface slots `CALL [EDX+0x5C]`
//   (Lock, two zeroed dwords pushed from two separately materialised
//   registers), `[EAX+0x74]` (pitch), `[EDX+0x7C]` (width), `[EAX+0x80]`
//   (height). Names cross-checked against YRpp
//   (consult-only, no LICENSE); YRpp types the Lock slot as (int, int), but
//   only a by-value two-int struct reproduces the two XORs, so it is modelled
//   that way here.
#ifndef GG_MATCH_RENDERER_BIT_FONT_LOCK_METHODS_H
#define GG_MATCH_RENDERER_BIT_FONT_LOCK_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "surface_class.h"

// BitFont (partial) — only the members Lock touches.
struct BitFont
{
    char        _pad000[0xC];    // +0x0000
    void*       pGraphBuffer;    // +0x000C  locked surface base
    int         PitchDiv2;       // +0x0010  surface stride in 16-bit words
    char        _pad014[0x1C];   // +0x0014
    LTRBStruct  Bounds;          // +0x0030  clip rectangle; all-zero = unset

    // FUNCTION: GAMEMD 0x434840 (decl; reloc) — clip `a` against `b` into
    // `out`; three stack arguments (`RET 0xC`), `this` unused.
    bool Intersect(LTRBStruct* out, LTRBStruct* a, LTRBStruct* b);

    // FUNCTION: GAMEMD 0x4348F0
    void Lock(Surface* surface);
};
GG_STATIC_ASSERT(offsetof(BitFont, pGraphBuffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(BitFont, PitchDiv2)    == 0x10);
GG_STATIC_ASSERT(offsetof(BitFont, Bounds)       == 0x30);

#endif  // GG_MATCH_RENDERER_BIT_FONT_LOCK_METHODS_H
