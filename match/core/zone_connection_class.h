// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI identifies ZoneConnectionClass as the element of DynamicVectorClass
//   0x7ED4C0 / VectorClass 0x7ED4E0. Native SetCapacity 0x589370 initializes
//   the 0x10-byte element, and FindItemIndex 0x5894D0 compares its four
//   coordinate words.
#ifndef GG_MATCH_CORE_ZONE_CONNECTION_CLASS_H
#define GG_MATCH_CORE_ZONE_CONNECTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ZoneConnectionClass
{
    struct unknown_pair
    {
        short unknown_00;
        short unknown_02;
        unknown_pair() : unknown_00(0), unknown_02(0) {}
        bool operator==(const unknown_pair& o) const
        {
            return unknown_00 == o.unknown_00 && unknown_02 == o.unknown_02;
        }
        bool operator!=(const unknown_pair& o) const { return !(*this == o); }
    };

    unknown_pair unknown_00; // +0x00
    unknown_pair unknown_04; // +0x04
    unsigned char unknown_08; // +0x08
    int unknown_0C;           // +0x0C

    ZoneConnectionClass() : unknown_08(0), unknown_0C(-1) {}
    ZoneConnectionClass(const ZoneConnectionClass& o)
        : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {}
    bool operator==(const ZoneConnectionClass& o) const
    {
        return unknown_00 == o.unknown_00 && unknown_04 == o.unknown_04;
    }
    bool operator!=(const ZoneConnectionClass& o) const { return !(*this == o); }
};

GG_STATIC_ASSERT(offsetof(ZoneConnectionClass, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ZoneConnectionClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(ZoneConnectionClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(ZoneConnectionClass, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(ZoneConnectionClass::unknown_pair, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ZoneConnectionClass::unknown_pair, unknown_02) == 0x02);
GG_STATIC_ASSERT(sizeof(ZoneConnectionClass::unknown_pair) == 0x04);
GG_STATIC_ASSERT(sizeof(ZoneConnectionClass) == 0x10);

#endif // GG_MATCH_CORE_ZONE_CONNECTION_CLASS_H
