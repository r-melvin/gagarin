// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x4346C0 / 0x434990),
//   cross-checked against YRpp (every offset/slot reconfirmed from the disasm).
//
// BitFont — the engine's bitmap-font renderer. Only the two matched methods and
// the members/struct they touch are modelled (the full layout is P2).
#ifndef GG_MATCH_RENDERER_BIT_FONT_H
#define GG_MATCH_RENDERER_BIT_FONT_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "surface_class.h"

// ---------------------------------------------------------------------------
// BitFont::InternalData — the loaded font's glyph table. Offsets confirmed from
// GetCharacterBitmap's [ECX+0x14]/[ECX+0x18]/[ECX+0x1c] (where ECX == the
// InternalData* at BitFont+0x4). SymbolTable is loaded with a zero-extending
// 16-bit read (XOR/MOV DX), so it is typed unsigned short*.
// ---------------------------------------------------------------------------
struct BitFontInternalData
{
    char            pad_00[0x14];     // +0x00 (FontWidth..Count, unused here)
    int             SymbolDataSize;   // +0x14
    unsigned short* SymbolTable;      // +0x18
    char*           Bitmaps;          // +0x1C
};
GG_STATIC_ASSERT(offsetof(BitFontInternalData, SymbolDataSize) == 0x14);
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BitFontInternalData, SymbolTable) == 0x18);  // ptr-width-sensitive
GG_STATIC_ASSERT(offsetof(BitFontInternalData, Bitmaps)     == 0x1C);
#endif

// ---------------------------------------------------------------------------
// BitFont  (NOVTABLE — retail has its own vtable at +0x00; modelled here as an
// opaque pointer placeholder so the touched members land at their retail
// offsets). Members confirmed numerically:
//   +0x04 InternalPTR    (GetCharacterBitmap MOV ECX,[ECX+0x4])
//   +0x0C pGraphBuffer   (UnLock MOV [ESI+0xC], 0)
//   +0x10 PitchDiv2      (UnLock MOV [ESI+0x10], 0)
// ---------------------------------------------------------------------------
// The clip rectangle 0x433CA0 copies into +0x30..+0x3C: edges, not extents
// (0x621040 takes the width as right - left).
struct BitFontBounds
{
    int Left;     // +0x00
    int Top;      // +0x04
    int Right;    // +0x08
    int Bottom;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(BitFontBounds) == 0x10);

class BitFont
{
public:
    short         FUN_00433C70(short color);          // GAMEMD 0x433C70: swaps +0x24, returns the old
    unsigned char FUN_00433C90(unsigned char value);  // GAMEMD 0x433C90: swaps +0x41, returns the old
    void          FUN_00433CA0(const BitFontBounds* bounds);  // GAMEMD 0x433CA0: +0x30..+0x3C, 0 clears
    void          FUN_00433CF0(const unsigned short* text, int* width, int* height,
                               int wrapWidth);         // GAMEMD 0x433CF0: measure text
    unsigned char* GetCharacterBitmap(wchar_t wch);  // GAMEMD 0x4346C0
    int            UnLock(Surface* pSurface);        // GAMEMD 0x434990

    void Lock(Surface* pSurface);                    // GAMEMD 0x4348F0
    void FUN_00434110(int value);                    // GAMEMD 0x434110
    int  FUN_00434120(unsigned short glyph, int x, int y, int color);  // GAMEMD 0x434120

    void*                __vtable;     // +0x00 (retail vtable pointer)
    BitFontInternalData* InternalPTR;  // +0x04
    void*                Pointer_8;    // +0x08
    short*               pGraphBuffer; // +0x0C
    int                  PitchDiv2;    // +0x10
    char                 unknown_14[0x08];  // +0x14
    int                  unknown_1C;   // +0x1C  line advance, added to the pen y per text line (0x434CD0)
    int                  unknown_20;   // +0x20  written by 0x434110
    unsigned short       unknown_24;   // +0x24  text colour, 0x434CD0 reads it as the draw colour
    short                unknown_26;   // +0x26
    int                  unknown_28;   // +0x28  tab width (0x434CD0 rounds the line width to it)
    int                  unknown_2C;   // +0x2C  glyph spacing added to every advance
    char                 unknown_30[0x10];  // +0x30
    unsigned char        unknown_40;   // +0x40  nonzero: 0x4353F0 draws twice for a doubled stroke
    char                 unknown_41[3];  // +0x41
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BitFont, InternalPTR)  == 0x04);  // ptr-width-sensitive
GG_STATIC_ASSERT(offsetof(BitFont, pGraphBuffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(BitFont, PitchDiv2)    == 0x10);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_1C)   == 0x1C);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_24)   == 0x24);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_28)   == 0x28);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_2C)   == 0x2C);
GG_STATIC_ASSERT(offsetof(BitFont, unknown_40)   == 0x40);
GG_STATIC_ASSERT(sizeof(BitFont)                 == 0x44);
#endif

#endif  // GG_MATCH_RENDERER_BIT_FONT_H
