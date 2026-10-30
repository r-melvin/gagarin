// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI names VectorClass<HSVClass> (vtable 0x7EF7F0) and DynamicVectorClass<HSVClass>
// (vtable 0x7EF750) over a three-byte element. RGBClass::FUN_006613A0 (0x6613A0) stores hue,
// saturation and value in member order at +0/+1/+2. The array-new loop of the capacity
// constructor 0x628DF0 inlines the element constructor as three zero byte stores and
// `ADD EAX,3`. Equality is the out-of-line __fastcall body at 0x5175D0 (one self-JMP in
// retail) and inequality the out-of-line __thiscall body at 0x517590.
#ifndef GG_MATCH_LAYOUT_HSV_CLASS_H
#define GG_MATCH_LAYOUT_HSV_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class HSVClass
{
public:
    unsigned char Hue;          // +0x00
    unsigned char Saturation;   // +0x01
    unsigned char Value;        // +0x02

    HSVClass() : Hue(0), Saturation(0), Value(0) {}
    // GAMEMD 0x5175D0 (declared; retail body is outside this unit)
    bool __fastcall operator==(const HSVClass& o) const;
    // GAMEMD 0x517590 (declared; retail body is outside this unit)
    bool operator!=(const HSVClass& o) const;
};
GG_STATIC_ASSERT(offsetof(HSVClass, Hue) == 0);
GG_STATIC_ASSERT(offsetof(HSVClass, Saturation) == 1);
GG_STATIC_ASSERT(offsetof(HSVClass, Value) == 2);
GG_STATIC_ASSERT(sizeof(HSVClass) == 3);

#endif
