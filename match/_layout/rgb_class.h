// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail RTTI at 0x81C140/0x81C170/0x81C198 identifies RGBClass as a class.
// Channel loads at 0x6613A6/0x6613AF/0x6613B4 and element copies at
// 0x477968/0x477975/0x47797C pin the three-byte layout. Constructors at
// 0x478850/0x645A70 zero each channel; comparisons at 0x4782E0/0x478470
// compare all three channels.
#ifndef GG_MATCH_LAYOUT_RGB_CLASS_H
#define GG_MATCH_LAYOUT_RGB_CLASS_H
#include "../_rt/gg_static_assert.h"
#include <stddef.h>
struct HSVClass;
class RGBClass
{
public:
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
    RGBClass() : Red(0), Green(0), Blue(0) {}
    bool operator==(const RGBClass& other) const
    { return Red == other.Red && Green == other.Green && Blue == other.Blue; }
    bool operator!=(const RGBClass& other) const { return !(*this == other); }
    HSVClass FUN_006613A0() const;
};
GG_STATIC_ASSERT(offsetof(RGBClass, Red) == 0);
GG_STATIC_ASSERT(offsetof(RGBClass, Green) == 1);
GG_STATIC_ASSERT(offsetof(RGBClass, Blue) == 2);
GG_STATIC_ASSERT(sizeof(RGBClass) == 3);
#endif
