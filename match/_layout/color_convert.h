// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#ifndef GG_MATCH_LAYOUT_COLOR_CONVERT_H
#define GG_MATCH_LAYOUT_COLOR_CONVERT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Shared access prefix; complete object size and RTTI identity are unproved.
// Palette-to-pixel lookup: [0x87F6C4], every scheme's +0x30C and ShapeButton's draw context (+0x50, stored
// from [0x87F6C4] by 0x69DD64 and passed to the shape blitter). +0x04 is the bytes per pixel (1: byte table,
// else word table) and +0x174 points at the table. (Was PixelFormat in lists, ControlsColorLookup in controls.)
struct ColorConvert
{
    int   unknown_00;
    int   BytesPerPixel;           // +0x04
    char  unknown_08[0x174 - 0x08];
    void* ColorTable;              // +0x174

    // The table is indexed by colour number; the entry is a byte when BytesPerPixel is 1.
    unsigned Lookup(int index) const
    {
        if (BytesPerPixel == 1)
            return ((const unsigned char*)ColorTable)[index];
        return ((const unsigned short*)ColorTable)[index];
    }
};
GG_STATIC_ASSERT(offsetof(ColorConvert, BytesPerPixel) == 0x04);
GG_STATIC_ASSERT(offsetof(ColorConvert, ColorTable) == 0x174);
GG_STATIC_ASSERT(sizeof(((ColorConvert*)0)->BytesPerPixel) == 4);
GG_STATIC_ASSERT(sizeof(((ColorConvert*)0)->ColorTable) == 4);

#endif
