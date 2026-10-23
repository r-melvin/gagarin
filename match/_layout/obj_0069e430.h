// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Caller5B40B0 allocates0x24; constructor69E430 writes through+20 and
// returns this with RET4. Word0 is data, not a vptr. Identity is unknown.
#ifndef GG_MATCH_LAYOUT_OBJ_0069E430_H
#define GG_MATCH_LAYOUT_OBJ_0069E430_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct Obj_0069E430
{
    // Declaration: GAMEMD 0x69E430
    Obj_0069E430(const char* name);
    unsigned short unknown_00;
    unsigned short unknown_02;
    unsigned short unknown_04;
    unsigned short unknown_06;
    char* unknown_08;
    unsigned int unknown_0C;
    unsigned char unknown_10;
    unsigned char unknown_11[3];
    unsigned int unknown_14;
    void* unknown_18;
    void* unknown_1C;
    unsigned int unknown_20;
};
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_02) == 0x02);
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_06) == 0x06);
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(Obj_0069E430, unknown_20) == 0x20);
GG_STATIC_ASSERT(sizeof(Obj_0069E430) == 0x24);
GG_STATIC_ASSERT(sizeof(unsigned short) == 2);
GG_STATIC_ASSERT(sizeof(unsigned int) == 4);
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(((Obj_0069E430*)0)->unknown_00) == 2);
GG_STATIC_ASSERT(sizeof(((Obj_0069E430*)0)->unknown_08) == 4);
GG_STATIC_ASSERT(sizeof(((Obj_0069E430*)0)->unknown_10) == 1);
#endif
