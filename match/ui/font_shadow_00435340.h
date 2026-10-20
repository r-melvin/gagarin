// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | original
// 0x435361 reads +0x26. Setter entries 0x433C70 and 0x434110 confirm
// +0x24 as a short and +0x20 as an int. This is a used prefix, not full size.
#ifndef GG_FONT_SHADOW_00435340_H
#define GG_FONT_SHADOW_00435340_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct Font_00435340 {
    char unknown_00[0x20];
    int unknown_20;
    short unknown_24;
    short unknown_26;
    // FUNCTION: GAMEMD 0x434110 (declaration)
    void SetValue(int value);
    // FUNCTION: GAMEMD 0x433C70 (declaration)
    short SwapColor(short color);
};
GG_STATIC_ASSERT(offsetof(Font_00435340, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Font_00435340, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Font_00435340, unknown_26) == 0x26);
GG_STATIC_ASSERT(sizeof(Font_00435340) == 0x28);
struct TextEngine_00435340 {
    // FUNCTION: GAMEMD 0x434CD0 (declaration)
    bool Print(Font_00435340*, int, const unsigned short*, int, int, int, int, int, int, int);
    bool FUN_00435340(Font_00435340*, int, const unsigned short*, int, int, int, int, int, int, int);
};
#endif
