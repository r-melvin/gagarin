// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   Two 256-byte colour remap table builders from the Egos.CPP block (see Egos.cpp): each
//   entry maps a palette colour to the palette entry nearest to it after blending towards
//   a chosen palette colour by a ratio. The palette and colour views repeat the
//   declarations in Egos.cpp (bodies 0x626200 and 0x6612C0 live elsewhere).
//
// Ordered ascending by retail address.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/colortable_00626070.h"

// FUNCTION: GAMEMD 0x4C37D0
// Fills a 256-byte table for the 16 remappable colours: entries 1..240 are blended
// towards one palette colour and mapped to the nearest of palette entries 240..254;
// entry 0 and entries above 240 map to themselves. Returns the table.
unsigned char* __fastcall FUN_004C37D0(const ColorTable_00626070& palette, unsigned char* table,
                                       int color, int ratio)
{
    if (table != 0) {
        unsigned char* out = table;
        for (int i = 0; i < 256; i++) {
            if (i <= 240 && i != 0) {
                ColorRGB_00661350 blended = palette[i];
                blended.Blend(ratio, palette[color]);
                int best = -1;
                int bestDiff = 0;
                for (int k = 240; k < 255; k++) {
                    int diff = palette[k].Difference(blended);
                    if (best == -1 || diff < bestDiff) {
                        best = k;
                        bestDiff = diff;
                    }
                }
                *out++ = (unsigned char)best;
            } else {
                *out++ = (unsigned char)i;
            }
        }
    }
    return table;
}

// FUNCTION: GAMEMD 0x4C3AD0
// Fills a 256-byte table: every palette colour blended towards one palette colour,
// then mapped to its nearest palette entry. Returns the table (null when none was given).
unsigned char* __fastcall FUN_004C3AD0(const ColorTable_00626070& palette, unsigned char* table,
                                       int color, int ratio)
{
    if (table != 0) {
        for (int i = 0; i < 256; i++) {
            ColorRGB_00661350 blended = palette[i];
            blended.Blend(ratio, palette[color]);
            table[i] = (unsigned char)palette.Nearest(blended);
        }
    }
    return table;
}

// FUNCTION: GAMEMD 0x4C3B60
// The same table with entry 0 pinned to 0 (colour 0 stays transparent).
unsigned char* __fastcall FUN_004C3B60(const ColorTable_00626070& palette, unsigned char* table,
                                       int color, int ratio)
{
    ColorRGB_00661350 target = palette[color];
    table[0] = 0;
    for (int i = 1; i < 256; i++) {
        ColorRGB_00661350 blended = palette[i];
        blended.Blend(ratio, target);
        table[i] = (unsigned char)palette.Nearest(blended);
    }
    return table;
}
