// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail gamemd.exe v1.001 entries 0x433CE0/0x434100.
// BitFont RTTI: vtable 0x7E3A78, COL 0x7FBF40, descriptor 0x818B68.
// Constructor 0x433880 writes +0x28 and +0x40; allocation 0x4354D0 is 0x44.
// TAB handler 0x434EE9 uses +0x28 as its horizontal tab interval.
#ifndef GG_BIT_FONT_STATE_EXCHANGE_METHODS_H
#define GG_BIT_FONT_STATE_EXCHANGE_METHODS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct BitFontStateView {
    char unknown_00[0x28];
    int TabWidth;
    char unknown_2C[0x14];
    unsigned char Flag;
    char unknown_41[3];
    // FUNCTION: GAMEMD 0x433CE0
    unsigned char SwapFlag(unsigned char value);
    // FUNCTION: GAMEMD 0x434100
    int SwapTabWidth(int value);
};
GG_STATIC_ASSERT(offsetof(BitFontStateView, TabWidth) == 0x28);
GG_STATIC_ASSERT(offsetof(BitFontStateView, Flag) == 0x40);
GG_STATIC_ASSERT(sizeof(BitFontStateView) == 0x44);
#endif
