// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native value types named by the AngerStruct/ScoutStruct vector RTTI.
// Existing element definitions moved unchanged from the pair-vector header.
#ifndef GG_MATCH_LAYOUT_ANGER_SCOUT_STRUCT_H
#define GG_MATCH_LAYOUT_ANGER_SCOUT_STRUCT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class HouseClass;
struct AngerStruct {
    AngerStruct() : House(0), AngerLevel(0) {}
    AngerStruct(const AngerStruct& o) : House(o.House), AngerLevel(o.AngerLevel) {}
    bool operator==(const AngerStruct& o) const { return House == o.House && AngerLevel == o.AngerLevel; }
    bool operator!=(const AngerStruct& o) const { return !(*this == o); }
    HouseClass* House;  // +0x0 the house this node tracks
    int AngerLevel;     // +0x4
};
struct ScoutStruct {
    ScoutStruct() : A(0), B(0) {}
    ScoutStruct(const ScoutStruct& o) : A(o.A), B(o.B) {}
    bool operator==(const ScoutStruct& o) const { return A == o.A && B == o.B; }
    bool operator!=(const ScoutStruct& o) const { return !(*this == o); }
    int A;   // +0x0
    char B;  // +0x4
};
GG_STATIC_ASSERT(sizeof(AngerStruct) == 8 && sizeof(ScoutStruct) == 8);
GG_STATIC_ASSERT(offsetof(ScoutStruct, B) == 4 && offsetof(AngerStruct, AngerLevel) == 4);
#endif  // GG_MATCH_LAYOUT_ANGER_SCOUT_STRUCT_H
