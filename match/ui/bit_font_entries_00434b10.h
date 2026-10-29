// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   0x434B10 stores the BitText vptr at 0x7E3A80; the preceding COL at
//   0x7E3A7C resolves through 0x7FBF88 to the type descriptor at 0x818B80,
//   which spells .?AVBitText@@. It compares/resets the singleton at 0x89C4D0.
//   Retail constructor entry 0x434AD0 allocates 0x44
//   bytes and calls BitFont constructor 0x433880 before assigning that global;
//   RTTI identifies the object's class as BitFont. 0x434B40 uses five stack
//   arguments and direct calls to 0x4348F0/0x434110/0x434120/0x434990, RET 14h.
//   Constructor stores at 0x433880 confirm BitFont offsets +0x2C, +0x40/+0x41;
//   the deletion sequence at 0x434B21 calls vtable slot 0 with flag 1.
#ifndef GG_MATCH_UI_BIT_FONT_ENTRIES_00434B10_H
#define GG_MATCH_UI_BIT_FONT_ENTRIES_00434B10_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class Surface;
struct BitFont_00434B40
{
    char unknown_000[0x2C];
    int At_02C;
    char unknown_030[0x10];
    unsigned char At_040;
    char unknown_041[0x03];

    // FUNCTION: GAMEMD 0x4348F0
    void Lock(Surface* surface);
    // FUNCTION: GAMEMD 0x434110
    void FUN_00434110(int value);
    // FUNCTION: GAMEMD 0x434120
    int FUN_00434120(int glyph, int x, int y, int color);
    // FUNCTION: GAMEMD 0x434500
    int FUN_00434500(int first, int second, int third, int fourth, int fifth);
    // FUNCTION: GAMEMD 0x434990
    int UnLock(Surface* surface);
};
GG_STATIC_ASSERT(offsetof(BitFont_00434B40, At_02C) == 0x2C);
GG_STATIC_ASSERT(offsetof(BitFont_00434B40, At_040) == 0x40);
GG_STATIC_ASSERT(offsetof(BitFont_00434B40, unknown_041) == 0x41);
GG_STATIC_ASSERT(sizeof(BitFont_00434B40) == 0x44);

// FUNCTION: GAMEMD 0x434B40
int __stdcall FUN_00434B40(BitFont_00434B40* font,
    Surface* surface, int glyph, int x, int y);

// FUNCTION: GAMEMD 0x434BF0
int __stdcall FUN_00434BF0(BitFont_00434B40* font,
    Surface* surface, int first, int second, int third, int fourth);

#endif  // GG_MATCH_UI_BIT_FONT_ENTRIES_00434B10_H
