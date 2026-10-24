// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native template RTTI names BaseNodeClass (0x8188D0/0x818900). Vector operations
// at 0x42F3F0/0x42F490/0x42F4F0/0x42F9C0 pin this 16-byte element layout.
#ifndef GG_MATCH_LAYOUT_BASE_NODE_CLASS_H
#define GG_MATCH_LAYOUT_BASE_NODE_CLASS_H

#include "cell.h"
#include <stddef.h>

class BaseNodeClass
{
public:
    int unknown_00;             // +0x00
    Cell unknown_04;            // +0x04
    unsigned char unknown_08;   // +0x08; copy construction leaves padding 0x09..0x0B alone
    int Attempts;               // +0x0C; incremented by 0x42F380

    BaseNodeClass() {}
    BaseNodeClass(const BaseNodeClass& other)
        : unknown_00(other.unknown_00), unknown_04(other.unknown_04),
          unknown_08(other.unknown_08), Attempts(other.Attempts) {}
    bool operator==(const BaseNodeClass& other) const
    {
        return unknown_00 == other.unknown_00 && unknown_04 == other.unknown_04;
    }
    bool operator!=(const BaseNodeClass& other) const { return !(*this == other); }
};
GG_STATIC_ASSERT(offsetof(BaseNodeClass, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BaseNodeClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(BaseNodeClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(BaseNodeClass, Attempts) == 0x0C);
GG_STATIC_ASSERT(sizeof(BaseNodeClass) == 0x10);

#endif // GG_MATCH_LAYOUT_BASE_NODE_CLASS_H
