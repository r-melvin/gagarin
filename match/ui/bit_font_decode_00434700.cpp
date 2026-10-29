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

GG_STATIC_ASSERT(offsetof(BitFont, InternalPTR) == 0x04);
GG_STATIC_ASSERT(offsetof(BitFont, Pointer_8) == 0x08);

// FUNCTION: GAMEMD 0x434700
void BitFont::FUN_00434700()
{
    unsigned char* output = (unsigned char*)malloc(this->InternalPTR->unknown_08 * this->InternalPTR->Width + 2);
    this->Pointer_8 = output;

    if (this->InternalPTR != 0) {
        unsigned int glyph = this->InternalPTR->SymbolTable[0x58];
        if (glyph != 0) {
            unsigned char* source = reinterpret_cast<unsigned char*>(this->InternalPTR->Bitmaps) + this->InternalPTR->SymbolDataSize * (glyph - 1);
            if (source != 0) {
                unsigned char* sourceRow = source + 1;
                *output = *source;
                output = (unsigned char*)this->Pointer_8;
                output++;

                int y = 0;
                if ((unsigned int)this->InternalPTR->unknown_08 > 0) {
                    do {
                        int x = 0;
                        if ((unsigned int)this->InternalPTR->Width > 0) {
                            do {
                                *output = (unsigned char)~*sourceRow;
                                ++output;
                                ++sourceRow;
                                ++x;
                            } while ((unsigned int)x < (unsigned int)this->InternalPTR->Width);
                        }
                        ++y;
                    } while ((unsigned int)y < (unsigned int)this->InternalPTR->unknown_08);
                }
            }
        }
    }
}
