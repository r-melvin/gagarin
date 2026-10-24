// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// RTTI: vtable7EFDA4 -> COL807CE8 -> TD836818 .?AVPixelFXClass@@.
// Allocation: 6D7AAD PUSH3C, 6D7AAF operator new, 6D7ABE ctor631E30.
// Fields: 631D40 initialization, 631E50 interpolation, 631EE0 countdown.
// Layout and virtual slot reconfirmed from the retail image.
#ifndef GG_MATCH_LAYOUT_PIXEL_FX_CLASS_H
#define GG_MATCH_LAYOUT_PIXEL_FX_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7EFDA4
class PixelFXClass
{
public:
    // Declaration: GAMEMD 0x631E30; ECX receiver, one stack int, RET4.
    PixelFXClass(); // 0x631E10, no explicit stack arguments
    explicit PixelFXClass(int value);
    // The sole observed virtual slot is deleting destructor631F40.
    // The virtual destructor generates the sole scalar deleting wrapper.
    virtual ~PixelFXClass();
    // Declaration: GAMEMD 0x631D40; ECX receiver, one stack int, RET4.
    void FUN_00631D40(int value);
    // Declaration: GAMEMD 0x631E50; ECX receiver, one stack int, RET4.
    void FUN_00631E50(int value);
    // Declaration: GAMEMD 0x631EE0; returns AL=0/1, one int, RET4.
    bool FUN_00631EE0(int value);

    void FUN_00631F10(int x, int y); // 0x631F10, RET8

    int unknown_04, unknown_08, unknown_0C;
    int unknown_10, unknown_14;
    int unknown_18, unknown_1C, unknown_20;
    int unknown_24, unknown_28, unknown_2C;
    int unknown_30, unknown_34, unknown_38;
};
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(PixelFXClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_08) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_0C) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_10) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_14) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_18) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_1C) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_20) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_24) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_28) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_2C) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_30) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_34) == 4);
GG_STATIC_ASSERT(sizeof(((PixelFXClass*)0)->unknown_38) == 4);
GG_STATIC_ASSERT(sizeof(PixelFXClass) == 0x3C);

// Raw table7EFDA4 has one slot before next COL at7EFDA8.
struct PixelFXPrimaryVtableLayout
{
    void* deleting_destructor; // +0x00 ->0x631F40
};
GG_STATIC_ASSERT(offsetof(PixelFXPrimaryVtableLayout, deleting_destructor) == 0);
GG_STATIC_ASSERT(sizeof(PixelFXPrimaryVtableLayout) == 4);
#endif
