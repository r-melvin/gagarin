// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entries, extents, and conventions were revalidated with the local Ghidra
//   CLI against retail gamemd.exe v1.001. The constructor at 0x433895 stores
//   the vptr at +0; 0x434700 stores an allocated buffer at +8; the entries at
//   0x4347B0/0x4347E0 load +4 and increment +0x1C. These entries also establish
//   the nested BitFontInternalData accesses at +0x14/+0x18/+0x1C.
#ifndef GG_MATCH_UI_BIT_FONT_PIXEL_METHODS_00434790_H
#define GG_MATCH_UI_BIT_FONT_PIXEL_METHODS_00434790_H

#include <stddef.h>
#include "../renderer/bit_font.h"
#include "../_rt/gg_static_assert.h"

struct BitFontPixelMethods_00434790
{
    void* unknown_00;
    BitFontInternalData* unknown_04;
    unsigned int unknown_08;
    char unknown_0C[0x10];
    int unknown_1C;

    // FUNCTION: GAMEMD 0x434790 — ECX=this, one unsigned-short pointer on
    // stack, callee cleanup RET 4.
    unsigned int FUN_00434790(unsigned short* value);
};
GG_STATIC_ASSERT(offsetof(BitFontPixelMethods_00434790, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(BitFontPixelMethods_00434790, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BitFontPixelMethods_00434790, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(BitFontPixelMethods_00434790, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(sizeof(BitFontPixelMethods_00434790) == 0x20);
GG_STATIC_ASSERT(offsetof(BitFontInternalData, pad_00) == 0x00);
GG_STATIC_ASSERT(sizeof(BitFontInternalData) == 0x20);

// FUNCTION: GAMEMD 0x4347B0 — __fastcall, receiver in ECX, no stack args.
void FUN_004347B0(BitFontPixelMethods_00434790* font);

// FUNCTION: GAMEMD 0x4347E0 — __fastcall, receiver in ECX, no stack args.
void FUN_004347E0(BitFontPixelMethods_00434790* font);

#endif
