// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   This source follows the retail instruction flow at 0x434790 (19 bytes),
//   0x4347B0 (44 bytes), and 0x4347E0 (85 bytes). The symbol-table indices,
//   null branches, byte operations, and member offsets are taken from those
//   entry-bounded disassemblies; no semantic names are inferred.
#include "bit_font_pixel_methods_00434790.h"

// FUNCTION: GAMEMD 0x434790
unsigned int BitFontPixelMethods_00434790::FUN_00434790(unsigned short* value)
{
    if (value != 0) {
        *value ^= 0x5555;
    }
    return this->unknown_08;
}

// FUNCTION: GAMEMD 0x4347B0
void FUN_004347B0(BitFontPixelMethods_00434790* font)
{
    BitFontInternalData* data = font->unknown_04;
    if (data != 0) {
        ++font->unknown_1C;

        unsigned char* pixel = 0;
        unsigned short* symbols = data->SymbolTable;
        unsigned int symbol = 0;
        symbol = symbols[0x20];
        if (symbol != 0) {
            int symbolIndex = symbol;
            --symbolIndex;
            int stride = font->unknown_04->SymbolDataSize;
            unsigned int pixelOffset = symbolIndex * stride;
            unsigned char* bitmaps = (unsigned char*)font->unknown_04->Bitmaps;
            pixel = bitmaps + pixelOffset;
        }
        ++*pixel;
    }
}

// FUNCTION: GAMEMD 0x4347E0
void FUN_004347E0(BitFontPixelMethods_00434790* font)
{
    BitFontInternalData* data = font->unknown_04;
    if (data != 0) {
        ++font->unknown_1C;

        unsigned char* firstPixel = 0;
        unsigned short* symbols = data->SymbolTable;
        unsigned int firstSymbol = 0;
        firstSymbol = symbols[0x20];
        if (firstSymbol != 0) {
            int firstIndex = firstSymbol;
            --firstIndex;
            int firstStride = font->unknown_04->SymbolDataSize;
            unsigned int firstOffset = firstIndex * firstStride;
            unsigned char* bitmaps = (unsigned char*)font->unknown_04->Bitmaps;
            firstPixel = bitmaps + firstOffset;
        }

        unsigned char* targetPixel = 0;
        unsigned int targetSymbol = 0;
        targetSymbol = symbols[0x3000];
        if (targetSymbol != 0) {
            int targetIndex = targetSymbol - 1;
            int targetStride = font->unknown_04->SymbolDataSize;
            unsigned int targetOffset = targetIndex * targetStride;
            unsigned char* bitmaps = (unsigned char*)font->unknown_04->Bitmaps;
            targetPixel = bitmaps + targetOffset;
        }

        if (targetPixel != 0) {
            if (firstPixel != 0) {
                *targetPixel = (unsigned char)(*firstPixel << 1);
                return;
            }
            *targetPixel = *((unsigned char*)font->unknown_04);
        }
    }
}
