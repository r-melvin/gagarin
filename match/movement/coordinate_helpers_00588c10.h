// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail gamemd.exe v1.001 entries 0x588C10..0x588D30.
#ifndef GG_COORDINATE_HELPERS_00588C10_H
#define GG_COORDINATE_HELPERS_00588C10_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct Coordinate_00588C40 {
    short X;
    short Y;
    Coordinate_00588C40(short x, short y) : X(x), Y(y) {}
    Coordinate_00588C40& Add(const Coordinate_00588C40& delta);
    Coordinate_00588C40 Subtract(const Coordinate_00588C40& delta) const;
};
GG_STATIC_ASSERT(offsetof(Coordinate_00588C40, X) == 0);
GG_STATIC_ASSERT(offsetof(Coordinate_00588C40, Y) == 2);
GG_STATIC_ASSERT(sizeof(Coordinate_00588C40) == 4);
// A 0x24-byte prefix view; no total allocation size is inferred here.
struct StateRecord_00588C10 {
    char unknown_00[0x10];
    int unknown_10;
    unsigned char unknown_14;
    char unknown_15[3];
    int unknown_18;
    int unknown_1C;
    unsigned char unknown_20;
    char unknown_21[3];
    StateRecord_00588C10& CopyState(const StateRecord_00588C10& other);
};
GG_STATIC_ASSERT(offsetof(StateRecord_00588C10, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(StateRecord_00588C10, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(StateRecord_00588C10, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(StateRecord_00588C10, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(StateRecord_00588C10, unknown_20) == 0x20);
GG_STATIC_ASSERT(sizeof(StateRecord_00588C10) == 0x24);
// Prefix views: only +4 and +0xC are accessed by the two index routines.
struct BufferIndex_00588CC0 {
    char unknown_00[4];
    void* Data;
    char unknown_08[4];
    unsigned char Valid;
    char unknown_0D[3];
    unsigned int Index8(const void* item) const;
    unsigned int Index16(const void* item) const;
};
GG_STATIC_ASSERT(offsetof(BufferIndex_00588CC0, Data) == 4);
GG_STATIC_ASSERT(offsetof(BufferIndex_00588CC0, Valid) == 0xC);
GG_STATIC_ASSERT(sizeof(BufferIndex_00588CC0) == 0x10);
struct ValueRecord_00588D30 {
    int unknown_00;
    int unknown_04;
    unsigned char unknown_08;
    char unknown_09[3];
    int unknown_0C;
    ValueRecord_00588D30(const ValueRecord_00588D30& other)
        : unknown_00(other.unknown_00), unknown_04(other.unknown_04),
          unknown_08(other.unknown_08), unknown_0C(other.unknown_0C) {}
};
GG_STATIC_ASSERT(offsetof(ValueRecord_00588D30, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(ValueRecord_00588D30, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(ValueRecord_00588D30, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(ValueRecord_00588D30, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(ValueRecord_00588D30) == 0x10);
// Prefix view: the full owning buffer layout is not established by Get.
struct RecordBuffer_00588D30 {
    char unknown_00[4];
    ValueRecord_00588D30* Data;
    ValueRecord_00588D30 Get(int index) const;
};
GG_STATIC_ASSERT(offsetof(RecordBuffer_00588D30, Data) == 4);
GG_STATIC_ASSERT(sizeof(RecordBuffer_00588D30) == 8);
#endif
