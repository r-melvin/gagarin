// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Existing Value view extracted unchanged from economy/house_class_tib_methods.h.
// Retail 0x4F9610 and 0x684F3D read +0xB8; no complete object extent claimed.
#ifndef GG_MATCH_LAYOUT_TIBERIUM_CLASS_H
#define GG_MATCH_LAYOUT_TIBERIUM_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
class TiberiumClass
{
public:
    char           _pad0[0x60];   // AbstractTypeClass-derived head = P2
    const wchar_t* UIName;        // +0x60 (read by CellClass::GetUIName 0x484FF0)
    char           _pad64[0xB8 - 0x64];
    int            Value;         // +0xB8
};
GG_STATIC_ASSERT(offsetof(TiberiumClass, UIName) == 0x60);
GG_STATIC_ASSERT(offsetof(TiberiumClass, Value) == 0xB8);
#endif
