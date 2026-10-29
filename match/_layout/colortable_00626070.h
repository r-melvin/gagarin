// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_COLORTABLE_00626070_H_H
#define GG_MATCH__LAYOUT_COLORTABLE_00626070_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "colorrgb_00661350.h"

struct ColorTable_00626070
{
    ColorRGB_00661350 Colors[256];   // +0x000

    ColorTable_00626070(const ColorTable_00626070& other);

    const ColorRGB_00661350& operator[](int index) const { return Colors[index % 256]; }

    void FUN_006260F0(int ratio);
    void FUN_00626120(int ratio, const ColorTable_00626070& target);
    void FUN_00626170(int ratio, const char* marks);
    void FUN_006261B0(int ratio, const ColorTable_00626070& target, const char* marks);
    int Nearest(const ColorRGB_00661350& color) const;          // 0x626200
};

GG_STATIC_ASSERT(offsetof(ColorTable_00626070, Colors) == 0x000);

#endif
