// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Caller5B40B0 allocates0x24; constructor69E430 writes through+20 and
// returns this with RET4. Word0 is data, not a vptr. Identity is unknown.
#ifndef GG_MATCH_LAYOUT_OBJ_0069E430_H
#define GG_MATCH_LAYOUT_OBJ_0069E430_H
#include <stddef.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"
struct RectangleStruct;
struct ColorStruct;
struct Obj_0069E430;
// FUNCTION: GAMEMD 0x69E100
inline void FUN_0069E100(Obj_0069E430* resource);
// GLOBAL: GAMEMD 0x00B077B0
extern Obj_0069E430* DAT_00B077B0;
struct Obj_0069E430
{
    // Declaration: GAMEMD 0x69E430
    Obj_0069E430(const char* name);
    // FUNCTION: GAMEMD 0x69E500
    // Expanded in 69E100/69E180/69E210/69E320; array cleanup takes its address.
    ~Obj_0069E430()
    {
        if (unknown_00 == -1) {
            FUN_0069E100(this);
            if (unknown_18) unknown_18->unknown_1C = unknown_1C;
            if (unknown_1C) unknown_1C->unknown_18 = unknown_18;
            else DAT_00B077B0 = unknown_18;
            if (unknown_08) {
                free(unknown_08);
                unknown_08 = 0;
            }
        }
    }
    // FUNCTION: GAMEMD 0x69E580
    Obj_0069E430* FUN_0069E580();
    // FUNCTION: GAMEMD 0x69E740
    char* FUN_0069E740(unsigned int index);
    // FUNCTION: GAMEMD 0x69E7E0
    RectangleStruct FUN_0069E7E0(unsigned int index);
    // FUNCTION: GAMEMD 0x69E860
    ColorStruct FUN_0069E860(unsigned int index);
    // FUNCTION: GAMEMD 0x69E8D0
    bool FUN_0069E8D0(unsigned int index);
    // FUNCTION: GAMEMD 0x69E900
    bool FUN_0069E900(unsigned int index);
    short unknown_00;
    short unknown_02;
    short unknown_04;
    short unknown_06;
    char* unknown_08;
    Obj_0069E430* unknown_0C;
    unsigned char unknown_10;
    unsigned char unknown_11[3];
    unsigned int unknown_14;
    Obj_0069E430* unknown_18;
    Obj_0069E430* unknown_1C;
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
GG_STATIC_ASSERT(sizeof(((Obj_0069E430*)0)->unknown_0C) == 4);
GG_STATIC_ASSERT(sizeof(((Obj_0069E430*)0)->unknown_18) == 4);
GG_STATIC_ASSERT(sizeof(((Obj_0069E430*)0)->unknown_1C) == 4);
// FUNCTION: GAMEMD 0x69E100
inline void FUN_0069E100(Obj_0069E430* resource)
{
    if (resource->unknown_00 == -1 && resource->unknown_10) {
        delete resource->unknown_0C;
        resource->unknown_0C = 0;
        resource->unknown_10 = 0;
    }
}

#endif
