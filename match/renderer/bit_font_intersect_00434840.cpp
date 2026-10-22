// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Function body, call ABI, branches and all four LTRB field offsets follow
//   the pinned retail instructions at 0x434840..0x4348E1; the entry-bounded
//   REA evidence is /tmp/gagarin_bitfont_intersect_00434840.json.
#include "bit_font_lock_methods.h"
#include <stddef.h>

GG_STATIC_ASSERT(offsetof(LTRBStruct, Left) == 0x00);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Right) == 0x08);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Bottom) == 0x0C);
GG_STATIC_ASSERT(sizeof(LTRBStruct) == 0x10);

// FUNCTION: GAMEMD 0x434840
bool BitFont::Intersect(LTRBStruct* out, LTRBStruct* a, LTRBStruct* b)
{
    if (a->Top > b->Bottom || b->Top > a->Bottom ||
        a->Left > b->Right || b->Left > a->Right) {
        out->Left = 0;
        out->Top = 0;
        out->Right = -1;
        out->Bottom = -1;
        return false;
    }

    *out = *a;
    if (out->Top < b->Top) {
        out->Top = b->Top;
    }
    if (out->Left < b->Left) {
        out->Left = b->Left;
    }
    if (out->Bottom > b->Bottom) {
        out->Bottom = b->Bottom;
    }
    if (out->Right > b->Right) {
        out->Right = b->Right;
    }
    return true;
}
