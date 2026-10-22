// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The member convention, allocation, buffer writes, loop bounds and data
//   offsets follow retail 0x434700. Extended data fields at +0x14/+0x18/+0x1C
//   are confirmed by this body and the 0x433990 resolver; the resolver stores
//   the glyph count at +0x20. Evidence: /tmp/gagarin_bitfont_convert_00434700.json.
#include "surface_desc_ctor_methods.h"
#include <stddef.h>
#include <stdlib.h>

// LIBRARY: GAMEMD 0x7C9430
// The retail call targets the CRT allocator; its body is out of scope.
extern "C" void* __cdecl malloc(size_t size);

struct BitFontDecodeData_00434700
{
    int unknown_00;
    int Width;
    int Height;
    int unknown_0C;
    int unknown_10;
    int SymbolDataSize;
    unsigned short* SymbolTable;
    unsigned char* Bitmaps;
    int GlyphCount;
};
GG_STATIC_ASSERT(offsetof(BitFontDecodeData_00434700, Width) == 0x04);
GG_STATIC_ASSERT(offsetof(BitFontDecodeData_00434700, Height) == 0x08);
GG_STATIC_ASSERT(offsetof(BitFontDecodeData_00434700, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BitFontDecodeData_00434700, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(BitFontDecodeData_00434700, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(BitFontDecodeData_00434700, SymbolDataSize) == 0x14);
GG_STATIC_ASSERT(offsetof(BitFontDecodeData_00434700, SymbolTable) == 0x18);
GG_STATIC_ASSERT(offsetof(BitFontDecodeData_00434700, Bitmaps) == 0x1C);
GG_STATIC_ASSERT(offsetof(BitFontDecodeData_00434700, GlyphCount) == 0x20);
GG_STATIC_ASSERT(sizeof(BitFontDecodeData_00434700) == 0x24);
GG_STATIC_ASSERT(offsetof(BitFont, Info) == 0x04);
GG_STATIC_ASSERT(offsetof(BitFont, At_08) == 0x08);

// FUNCTION: GAMEMD 0x434700
void BitFont::FUN_00434700()
{
    unsigned char* output = (unsigned char*)malloc(((BitFontDecodeData_00434700*)this->Info)->Height * ((BitFontDecodeData_00434700*)this->Info)->Width + 2);
    this->At_08 = (int)output;

    if (this->Info != 0) {
        unsigned int glyph = ((BitFontDecodeData_00434700*)this->Info)->SymbolTable[0x58];
        if (glyph != 0) {
            unsigned char* source = ((BitFontDecodeData_00434700*)this->Info)->Bitmaps + ((BitFontDecodeData_00434700*)this->Info)->SymbolDataSize * (glyph - 1);
            if (source != 0) {
                unsigned char* sourceRow = source + 1;
                *output = *source;
                output = (unsigned char*)this->At_08;
                output++;

                int y = 0;
                if ((unsigned int)((BitFontDecodeData_00434700*)this->Info)->Height > 0) {
                    do {
                        int x = 0;
                        if ((unsigned int)((BitFontDecodeData_00434700*)this->Info)->Width > 0) {
                            do {
                                *output = (unsigned char)~*sourceRow;
                                ++output;
                                ++sourceRow;
                                ++x;
                            } while ((unsigned int)x < (unsigned int)((BitFontDecodeData_00434700*)this->Info)->Width);
                        }
                        ++y;
                    } while ((unsigned int)y < (unsigned int)((BitFontDecodeData_00434700*)this->Info)->Height);
                }
            }
        }
    }
}
