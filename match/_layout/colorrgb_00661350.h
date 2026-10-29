// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_COLORRGB_00661350_H_H
#define GG_MATCH__LAYOUT_COLORRGB_00661350_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ColorRGB_00661350
{
    unsigned char unknown_00;   // +0x00
    unsigned char unknown_01;   // +0x01
    unsigned char unknown_02;   // +0x02

    ColorRGB_00661350() : unknown_00(0), unknown_01(0), unknown_02(0) {}

    // retail thiscall helper, matched elsewhere in main as a separate view.
    void Blend(int ratio, const ColorRGB_00661350& target);   // 0x6612C0
    int Difference(const ColorRGB_00661350& other) const;
};

GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_01) == 0x01);
GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_02) == 0x02);
GG_STATIC_ASSERT(sizeof(ColorRGB_00661350) == 0x03);

#endif
