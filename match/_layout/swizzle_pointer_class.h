// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// RTTI identifies the eight-byte element of the vectors at 0x7F4134/0x7F4154.
// Slot6 at 0x6CF540 copies DWORDs at +0 and +4; the constructor at 0x6CF8F0
// zeroes both. Equality at 0x6CF560 compares only the first DWORD.
#ifndef GG_MATCH_LAYOUT_SWIZZLE_POINTER_CLASS_H
#define GG_MATCH_LAYOUT_SWIZZLE_POINTER_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class SwizzlePointerClass {
public:
    SwizzlePointerClass() : A(0), B(0) {}
    SwizzlePointerClass(int first, void* second) : A(first), B(second) {}
    bool operator==(const SwizzlePointerClass& o) const { return A == o.A; }
    bool operator!=(const SwizzlePointerClass& o) const { return !(*this == o); }
    int A;  // +0x0
    void* B;  // +0x4: slot address (6CF2A4) or subject pointer (6CF30D)
};
GG_STATIC_ASSERT(sizeof(SwizzlePointerClass) == 8);
GG_STATIC_ASSERT(offsetof(SwizzlePointerClass, A) == 0);
GG_STATIC_ASSERT(offsetof(SwizzlePointerClass, B) == 4);
#endif
